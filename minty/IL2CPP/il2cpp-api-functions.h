DO_API(0x0092E1F0, void*, il2cpp_string_new, (const char* str));
DO_API(0x009156E0, void*, il2cpp_value_box, (void* klass, void* data)); // --- aki my beloved chu chu
//DO_API(0x8D6460, void*, il2cpp_array_new, (void* elementTypeInfo, uintptr_t length));
DO_API(0x000000, void**, il2cpp__vm__MetadataCache__GetTypeInfoFromTypeDefinitionIndex, (uint32_t index));
//DO_API(0x000000, std::string, il2cpp__vm__Type__GetName, (LPVOID type, uint32_t format));
DO_API(0x000000, std::string, il2cpp__vm__Type__GetName, (LPVOID klass, uint32_t format));
DO_API(0x000000, std::string, il2cpp__Class__Type__GetName, (void** klass));
DO_API(0x000000, LPVOID, il2cpp__vm__Class__GetMethods, (LPVOID klass, LPVOID iter));
DO_API(0x000000, std::string, il2cpp__vm__Method__GetNameWithGenericTypes, (LPVOID method));