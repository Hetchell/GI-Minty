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
#include "../IL2CPP/il2cpp-appdata.h"
#include "../IL2CPP/HookManager.h"
#include "../IL2CPP/il2cppUtils.h"

#pragma comment(lib,"ntdll.lib")

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

//#define LOG(fmtstr, ...) printf("[ DebuggerBypass ] - %s\n", std::format(fmtstr, ##__VA_ARGS__).c_str())

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

app::Byte__Array* OnRecordUserData(int32_t nType)
{
	if (m_CorrectSignatures.count(nType))
	{
		auto byteClass = app::GetIl2Classes()[0x25];

		auto& content = m_CorrectSignatures[nType];
		//auto newArrayNotByte = (app::Il2CppArray*)il2cpp_array_new(byteClass, content.size());
		//auto newArray = (app::Byte__Array*)newArrayNotByte;
		//memmove_s(newArray->vector, content.size(), content.data(), content.size());

		//return newArray;
	}

	app::Byte__Array* result = CALL_ORIGIN(RecordUserData_Hook, nType);
	auto resultArray = TO_UNI_ARRAY(result, byte);

	auto length = resultArray->length();
	if (length == 0)
		return result;

	auto stringValue = std::string((char*)result->vector, length);
	m_CorrectSignatures[nType] = stringValue;

	util::log(M_Info, "Sniffed correct signature for type %d value '%s'", nType, stringValue.c_str());

	return result;
}

static int RecordChecksumUserData_Hook(int type, char* out, int out_size)
{
	auto ret = CALL_ORIGIN(RecordChecksumUserData_Hook, type, out, out_size);
	while (true) {
		util::log(M_Info, "type %d\nret %d: %s", type, ret, out);
		Sleep(10);
	}
	const char* data[] = {
		"08126aeb28524e7b05d718826b6c5e4e",
		"6c86749942cd7201a2e77266e1a3977128",
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

void DisableLogReport()
{
	char szProcessPath[MAX_PATH]{};
	GetModuleFileNameA(nullptr, szProcessPath, MAX_PATH);

	auto path = std::filesystem::path(szProcessPath);
	auto ProcessName = path.filename().string();
	ProcessName = ProcessName.substr(0, ProcessName.find_last_of('.'));

	auto Astrolabe = path.parent_path() / (ProcessName + "_Data\\Plugins\\Astrolabe.dll");
	auto MiHoYoMTRSDK = path.parent_path() / (ProcessName + "_Data\\Plugins\\MiHoYoMTRSDK.dll");
	auto Telemetry = path.parent_path() / (ProcessName + "_Data\\Plugins\\Telemetry.dll");

	// open exclusive access to these two dlls
	// so they cannot be loaded
	auto h1 = CreateFileA(Astrolabe.string().c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	auto h2 = CreateFileA(MiHoYoMTRSDK.string().c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	auto h3 = CreateFileA(Telemetry.string().c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	/*
	auto t = thread([](HANDLE h1, HANDLE h2, HANDLE h3) -> void
		{
			this_thread::sleep_for(chrono::seconds(60));
			CloseHandle(h1);
			CloseHandle(h2);
			CloseHandle(h3);
		}, h1, h2, h3);
	t.detach();
	*/

	return;
}

void ProtectionBypass::Init()
{
	// need update
	//HookManager::install(app::Unity_RecordUserData, RecordUserData_Hook);
	for (int i = 0; i < 4; i++) {
		//app::Unity_RecordUserData(i);
		//std::string cscscs = std::string((char*)app::Application_RecordUserData(i, nullptr)->vector, app::Application_RecordUserData(i, nullptr)->max_length);
		//util::log(M_Info, "type %i checksum: %s", i, cscscs);
	}
	HookManager::install(app::RecordChecksumUserData, RecordChecksumUserData_Hook);
	util::log(M_Info, "Trying to close mhyprot.");

	if (CloseHandleByName(L"\\Device\\mhyprot2")) {
		util::log(M_Info, "mhyprot anticheat has been killed");
	}
	else {
		util::log(M_Error, "Failed to close mhyprot anticheat. Please report this issue in our Discord server.");
	}

	util::log(M_Info, "Disable the *stupid* hoyo log spam..");
	DisableLogReport();
	util::log(M_Info, "Initialized protection bypass");
	//util::log(M_Info, "sleeping");
	//Sleep(20000);
	//util::log(M_Info, "slept");

	//HookManager::install(app::CrashReporter, CrashReporter_Hook);

	//HookManager::install(app::Unity_RecordUserData, RecordUserData_Hook);
}
