// 40 53 48 83 ec 50 48 c7 44 24 20 fe ff ff ff 48 83 c8 ff 48 ff c0 80 3c 01 00 75 f7 44 8b c0 48
DO_API(0x92E1F0, void*, il2cpp_string_new, (const char* str));
DO_API(0x9F7080, void*, il2cpp_value_box, (void* klass, void* data)); // aki was here :>
//DO_API(0x8D6460, void*, il2cpp_array_new, (void* elementTypeInfo, uintptr_t length));
DO_API(0x000000, void**, il2cpp__vm__MetadataCache__GetTypeInfoFromTypeDefinitionIndex, (uint32_t index));
//DO_API(0x000000, std::string, il2cpp__vm__Type__GetName, (LPVOID type, uint32_t format));
DO_API(0x000000, std::string, il2cpp__vm__Type__GetName, (LPVOID klass, uint32_t format));
DO_API(0x000000, std::string, il2cpp__Class__Type__GetName, (void** klass));
DO_API(0x000000, LPVOID, il2cpp__vm__Class__GetMethods, (LPVOID klass, LPVOID iter));
DO_API(0x000000, std::string, il2cpp__vm__Method__GetNameWithGenericTypes, (LPVOID method));
