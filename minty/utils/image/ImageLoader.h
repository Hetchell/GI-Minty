#include <map>
#include <optional>

#include "../../gui/GuiDefinitions.h"
#include "../../includes.h"

extern ID3D11Device* pDevice;

class ImageLoader {
   public:
    struct ImageData {
        ImTextureID textureID;
        ImVec2 size;
    };

    static std::optional<ImageData> GetImage(const std::string& imageName, const char* imageType = "PNG");

   private:
    inline static std::map<std::string, ImageData> s_Textures{};
};

bool LoadEx(const char* name, const char* type, LPBYTE& pDest, DWORD& size);
bool LoadTextureFromMemory(LPBYTE image_data, int image_width, int image_height, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
