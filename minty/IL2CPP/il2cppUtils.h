#pragma once

#include "il2cpp-appdata.h"
#include "il2cpp-types.h"

std::string il2cppi_to_string(app::Il2CppString* str);
std::string il2cppi_to_string(app::String* str);
app::String* string_to_il2cppi(std::string input);
app::String* string_to_il2cppi(const char* input);

app::Vector3 operator + (const app::Vector3& A, const app::Vector3& B);
app::Vector3 operator - (const app::Vector3& A, const app::Vector3& B);
app::Vector3 operator * (const app::Vector3& A, const float k);

template<typename ElementT>
struct UniArray {
    void* klass;
    app::MonitorData* monitor;
    app::Il2CppArrayBounds* bounds;
    app::il2cpp_array_size_t max_length;
    ElementT vector[32];

    typedef ElementT* iterator;
    typedef const ElementT* const_iterator;

    size_t length() const { return (bounds == nullptr) ? max_length : bounds->length; }

    iterator begin() { return &vector[0]; }
    const_iterator begin() const { return &vector[0]; }
    iterator end() { return &vector[length()]; }
    const_iterator end() const { return &vector[length()]; }
    ElementT* operator[](int i) { return &vector[i]; }

    std::vector<ElementT> vec()
    {
        auto result = std::vector<ElementT>(length());
        for (auto i = begin(); i < end(); i++)
            result.push_back(*i);
        return result;
    }
};

#define TO_UNI_COLLECTION(field, collection) reinterpret_cast<collection*>(field)
#define TO_UNI_ARRAY(field, type) TO_UNI_COLLECTION(field, UniArray<type>)