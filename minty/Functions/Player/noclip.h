#include "../il2cpp-appdata.h"
#include "../il2cpp-types.h"
#include "../il2cppUtils.h"
#include "../HookManager.h"
#include "../../Hotkeys/Hotkey.h"

namespace il2fns {
    inline Hotkey noClipHotkey = Hotkey("NoClip");
    void NoClipSpeed(float f);
    void noclipmod(int i);
    void NoClipInit(bool b);
    void OnNoclip();
    void colmod(int i);
}