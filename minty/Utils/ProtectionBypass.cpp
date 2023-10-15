// https://github.com/xTaiwanPingLord/GenshinDebuggerBypass
#ifndef UNICODE
#define UNICODE
#endif

#include "Utils.hpp"

#include "ProtectionBypass.h"

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <wchar.h>
#include <stdlib.h>
#include <format>
#include <intsafe.h>
#include <vector>
#include "../Functions/il2cpp-appdata.h"
#include "../Functions/HookManager.h"
#include "../Functions/il2cppUtils.h"

#pragma comment(lib,"ntdll.lib")

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

static int num = 0;

typedef NTSTATUS(NTAPI* _NtQuerySystemInformation)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);

typedef NTSTATUS(NTAPI* _NtDuplicateObject)(
	HANDLE SourceProcessHandle,
	HANDLE SourceHandle,
	HANDLE TargetProcessHandle,
	PHANDLE TargetHandle,
	ACCESS_MASK DesiredAccess,
	ULONG Attributes,
	ULONG Options
	);

typedef NTSTATUS(NTAPI* _NtQueryObject)(
	HANDLE ObjectHandle,
	ULONG ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _SYSTEM_HANDLE
{
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, * PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE
{
	NonPagedPool,
	PagedPool,
	NonPagedPoolMustSucceed,
	DontUseThisType,
	NonPagedPoolCacheAligned,
	PagedPoolCacheAligned,
	NonPagedPoolCacheAlignedMustS
} POOL_TYPE, * PPOOL_TYPE;

typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING Name;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccess;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	USHORT MaintainTypeList;
	POOL_TYPE PoolType;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, * POBJECT_TYPE_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFO
{
	ULONG                   NextEntryOffset;
	ULONG                   NumberOfThreads;
	LARGE_INTEGER           Reserved[3];
	LARGE_INTEGER           CreateTime;
	LARGE_INTEGER           UserTime;
	LARGE_INTEGER           KernelTime;
	UNICODE_STRING          ImageName;
	ULONG                   BasePriority;
	HANDLE                  ProcessId;
	HANDLE                  InheritedFromProcessId;
}SYSTEM_PROCESS_INFO, * PSYSTEM_PROCESS_INFO;

static PVOID GetLibraryProcAddress(LPCSTR LibraryName, LPCSTR ProcName)
{
	auto hModule = GetModuleHandleA(LibraryName);
	if (hModule == NULL)
		return nullptr;
	return GetProcAddress(hModule, ProcName);
}

bool CloseHandleByName(const wchar_t* name)
{
	auto pid = GetCurrentProcessId();

	while (true)
	{
		EnumWindows([](HWND hwnd, LPARAM lParam)->BOOL __stdcall
		{
			DWORD wndpid = 0;
			GetWindowThreadProcessId(hwnd, &wndpid);

			char szWindowClass[256]{};
			GetClassNameA(hwnd, szWindowClass, 256);
			if (!strcmp(szWindowClass, "UnityWndClass") && wndpid == *(DWORD*)lParam)
			{
				*(DWORD*)lParam = 0;
				return FALSE;
			}

			return TRUE;

		}, (LPARAM)&pid);

		if (!pid)
			break;

		Sleep(2000);
	}

	_NtQuerySystemInformation NtQuerySystemInformation =
		(_NtQuerySystemInformation)GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
	_NtDuplicateObject NtDuplicateObject =
		(_NtDuplicateObject)GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
	_NtQueryObject NtQueryObject =
		(_NtQueryObject)GetLibraryProcAddress("ntdll.dll", "NtQueryObject");
	NTSTATUS status;

	ULONG handleInfoSize = 0x10000;
	PSYSTEM_HANDLE_INFORMATION handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

	HANDLE processHandle = GetCurrentProcess();
	ULONG i;

	/* NtQuerySystemInformation won't give us the correct buffer size,
		so we guess by doubling the buffer size. */
	while ((status = NtQuerySystemInformation(
		SystemHandleInformation,
		handleInfo,
		handleInfoSize,
		NULL
	)) == STATUS_INFO_LENGTH_MISMATCH)
		handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

	/* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
	if (!NT_SUCCESS(status))
	{
		util::log(M_Error, "NtQuerySystemInformation failed!");
		return false;
	}

	bool closed = false;
	for (i = 0; i < handleInfo->HandleCount; i++)
	{
		if (closed)
			break;

		SYSTEM_HANDLE handle = handleInfo->Handles[i];
		HANDLE dupHandle = NULL;
		POBJECT_TYPE_INFORMATION objectTypeInfo;
		PVOID objectNameInfo;
		UNICODE_STRING objectName;
		ULONG returnLength;

		/* Duplicate the handle so we can query it. */
		if (!NT_SUCCESS(NtDuplicateObject(processHandle, (HANDLE)handle.Handle, GetCurrentProcess(), &dupHandle, 0, 0, 0)))
			continue;

		/* Query the object type. */
		objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);
		if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectTypeInformation, objectTypeInfo, 0x1000, NULL)))
		{
			CloseHandle(dupHandle);
			continue;
		}

		/* Query the object name (unless it has an access of
			0x0012019f, on which NtQueryObject could hang. */
		if (handle.GrantedAccess == 0x0012019f)
		{
			free(objectTypeInfo);
			CloseHandle(dupHandle);
			continue;
		}

		objectNameInfo = malloc(0x1000);
		if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectNameInformation, objectNameInfo, 0x1000, &returnLength)))
		{
			/* Reallocate the buffer and try again. */
			objectNameInfo = realloc(objectNameInfo, returnLength);
			if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectNameInformation, objectNameInfo, returnLength, NULL)))
			{
				free(objectTypeInfo);
				free(objectNameInfo);
				CloseHandle(dupHandle);
				continue;
			}
		}

		/* Cast our buffer into an UNICODE_STRING. */
		objectName = *(PUNICODE_STRING)objectNameInfo;

		/* Print the information! */
		if (objectName.Length && lstrcmpiW(objectName.Buffer, name) == 0)
		{
			CloseHandle((HANDLE)handle.Handle);
			closed = true;
		}

		free(objectTypeInfo);
		free(objectNameInfo);
		CloseHandle(dupHandle);

	}

	free(handleInfo);
	CloseHandle(processHandle);
	return closed;
}

typedef enum _SECTION_INFORMATION_CLASS {
	SectionBasicInformation,
	SectionImageInformation
} SECTION_INFORMATION_CLASS, *PSECTION_INFORMATION_CLASS;

EXTERN_C NTSTATUS __stdcall NtQuerySection(HANDLE SectionHandle, SECTION_INFORMATION_CLASS InformationClass, PVOID InformationBuffer, ULONG InformationBufferSize, PULONG ResultLength);
EXTERN_C NTSTATUS __stdcall NtProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PULONG NumberOfBytesToProtect, ULONG NewAccessProtection, PULONG OldAccessProtection);

void ProtectionBypass::DisableVMP() {
	DWORD old;
	VirtualProtect(NtProtectVirtualMemory, 1, PAGE_EXECUTE_READWRITE, &old);
	*(uintptr_t*)NtProtectVirtualMemory = *(uintptr_t*)NtQuerySection & ~(0xFFui64 << 32) | (uintptr_t)(*(uint32_t*)((uintptr_t)NtQuerySection + 4) - 1) << 32;
	VirtualProtect(NtProtectVirtualMemory, 1, old, &old);
}

std::map<int32_t, std::string> m_CorrectSignatures;
app::Byte__Array* OnRecordUserData(int32_t nType);

static app::Byte__Array* RecordUserData_Hook(int32_t nType)
{
	return OnRecordUserData(nType);
}

app::Byte__Array* OnRecordUserData(int32_t nType) {
	if (m_CorrectSignatures.count(nType)) {
		auto byteClass = app::GetIl2Classes()[0x25];
		auto& content = m_CorrectSignatures[nType];
		auto newArrayNotByte = (app::Il2CppArray*) il2cpp_array_new(byteClass, content.size());
		auto newArray = (app::Byte__Array*) newArrayNotByte;
		
		memmove_s(newArray->vector, content.size(), content.data(), content.size());
		return newArray;
	}

	app::Byte__Array* result = CALL_ORIGIN(RecordUserData_Hook, nType);
	auto resultArray = TO_UNI_ARRAY(result, byte);
	auto length = resultArray->length();

	if (length == 0)
		return result;

	auto stringValue = std::string((char*)result->vector, length);
	m_CorrectSignatures[nType] = stringValue;

	util::log(M_Debug, "Sniffed correct signature for type %d value '%s'", nType, stringValue.c_str());
	return result;
}

static int RecordChecksumUserData_Hook(int type, char* out, int out_size) {
	auto ret = CALL_ORIGIN(RecordChecksumUserData_Hook, type, out, out_size);

	while (true) {
		util::log(M_Debug, "type %d\nret %d: %s", type, ret, out);
		Sleep(10);
	}

	const char* data[] = {
		"b62db48c3c79e59b1d3f7a14afdf74e3",
		"160617b76cc7b25dd378308d7840cc1925",
		"",
		""
	};

	assert(type < sizeof(data) / sizeof(const char*));
	ret = strlen(data[type]);
	if (strcmp(data[type], out) != 0)
		util::log(M_Error, "Wrong checksum");

	strncpy(out, data[type], out_size);
	return ret;
}

static bool report_sent = false;
void OnReportLuaShell(void* __this, app::String* type, app::String* value);

static void LuaShellManager_ReportLuaShellResult_Hook(void* __this, app::String* type, app::String* value) {
	OnReportLuaShell(__this, type, value);
}

std::vector<uint8_t> from_hex(std::string string) {
	std::vector<uint8_t> ret;
	auto HexCharToByte = [](char ch) {
		if (ch <= 0x40)
			return ch - 48;
		else
			return ch - 55;
		};

	for (int i = 0; i < string.length(); i += 2)
	{
		char firstchar = HexCharToByte(string[i]);
		char secondchar = HexCharToByte(string[i + 1]);
		char result = (16 * firstchar) | secondchar;
		ret.push_back(result);
	}
	return ret;
}

void OnReportLuaShell(void* __this, app::String* type, app::String* value) {
	auto xor_payload = [](std::vector<uint8_t>& value_bytes) -> void
	{
		auto length = value_bytes.size() - 1;
		for (signed long long i = length; i >= 0; i -= 1)
		{
			if (i == length)
				value_bytes[i] ^= 0xA3;
			else
				value_bytes[i] ^= value_bytes[i + 1];
		}
	};

	auto value_bytes = from_hex(il2cppi_to_string(value));
	xor_payload(value_bytes);

	auto value_string = std::string((char*)value_bytes.data(), value_bytes.size());
	//util::log(M_Info, "ReportLuaShellResult: %s, %s", il2cppi_to_string(type).c_str(), value_string.c_str());

	auto json_report = nlohmann::json::parse(value_string);

	if (json_report.contains("1"))
	{
		util::log(M_Info, "Letting the first LuaShellResult pass, blocking the rest.");
		report_sent = false;
	}
	else
		report_sent = true;

	if (!report_sent)
		CALL_ORIGIN(LuaShellManager_ReportLuaShellResult_Hook, __this, type, value);
	return;
}

static int CrashReporter_Hook(__int64 a1, __int64 a2, const char* a3) {
	return 0;
}
void ProtectionBypass::Init() {
	HookManager::install(app::Unity_RecordUserData, RecordUserData_Hook);

	for (int i = 0; i < 4; i++) {
		app::Unity_RecordUserData(i);
		//std::string checksum = std::string((char*)app::Application_RecordUserData(i, nullptr)->vector, app::Application_RecordUserData(i, nullptr)->max_length);
		//std::cout << "checksum #" << i << ": " << checksum << "\n";
	}

	HookManager::install(app::RecordChecksumUserData, RecordChecksumUserData_Hook);
	HookManager::install(app::CrashReporter, CrashReporter_Hook);
	//util::log(M_Info, "Trying to close mhyprot.");

	if (CloseHandleByName(L"\\Device\\mhyprot2"))
		util::log(M_Info, "mhyprot anticheat has been killed");

	
	util::log(M_Info, "Initialized protection bypass");
	HookManager::install(app::MoleMole_LuaShellManager_ReportLuaShellResult, LuaShellManager_ReportLuaShellResult_Hook);
}
