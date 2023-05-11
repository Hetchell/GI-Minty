#include "../../includes.h"
#include <map>
#include <optional>
#include "../../GUI/GuiDefinitions.h"

ID3D11Device* pDevice;

class ImageLoader
{
public:
	struct ImageData
	{
		ImTextureID textureID;
		ImVec2 size;
	};

	static std::optional<ImageData> GetImage(const std::string& imageName, const char* imageType = "PNG");

private:
	inline static std::map<std::string, ImageData> s_Textures{};
};

bool LoadEx(const char* name, const char* type, LPBYTE& pDest, DWORD& size)
{
	HMODULE s_Handle = GetModuleHandle("minty.dll");
	if (s_Handle == nullptr)
		return false;

	HRSRC hResource = FindResource(s_Handle, name, type);
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

bool LoadTextureFromMemory(LPBYTE image_data, int image_width, int image_height, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
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
