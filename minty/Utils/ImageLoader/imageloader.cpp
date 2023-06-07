#include "ImageLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ID3D11Device* pDevice;

std::optional<ImageLoader::ImageData> ImageLoader::GetImage(const std::string& imageName, const char* type) {
    if (s_Textures.count(imageName) > 0)
        return s_Textures[imageName];

    LPBYTE pDestination;
    DWORD size;

    bool loadResult = LoadEx(imageName.c_str(), type, pDestination, size);
    if (!loadResult) {
        // LOG_WARNING("Failed to load image: %s from resources", imageName);
        return {};
    }

    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory(pDestination, size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL) {
        // LOG_WARNING("Failed to convert image '%s' to RGBA by 'stb_image.h'", imageName.c_str());
        return {};
    }

    ImageLoader::ImageData imageData = {};

    ID3D11ShaderResourceView* new_texture = NULL;
    int width, height;
    bool textureResult = LoadTextureFromMemory(image_data, image_width, image_height,
                                               reinterpret_cast<ID3D11ShaderResourceView**>(&imageData.textureID), &width, &height);
    stbi_image_free(image_data);

    if (!textureResult) {
        // LOG_WARNING("Failed to load texture by DX11 for image: %s", imageName.c_str());
        return {};
    }

    imageData.size.x = static_cast<float>(width);
    imageData.size.y = static_cast<float>(height);
    s_Textures[imageName] = imageData;
    return imageData;
}

bool LoadEx(const char* name, const char* type, LPBYTE& pDest, DWORD& size) {
    HMODULE s_Handle = GetModuleHandleA("minty.dll");
    if (s_Handle == nullptr)
        return false;

    HRSRC hResource = FindResourceA(s_Handle, name, type);
    if (hResource) {
        HGLOBAL hGlob = LoadResource(s_Handle, hResource);
        if (hGlob) {
            size = SizeofResource(s_Handle, hResource);
            pDest = static_cast<LPBYTE>(LockResource(hGlob));
            if (size > 0 && pDest)
                return true;
        }
    }
    return false;
}

bool LoadTextureFromMemory(LPBYTE image_data, int image_width, int image_height, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height) {
    if (pDevice == nullptr)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;

    return true;
}
