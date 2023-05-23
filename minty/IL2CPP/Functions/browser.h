#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"

namespace il2fns {
	void TurnBrowser(bool value, float scale, std::string url);
}
namespace {
	app::String* string_to_il2cppi(std::string input) {
		return app::Marshal_PtrToStringAnsi((void*)input.c_str());
	}
}