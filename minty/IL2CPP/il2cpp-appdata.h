#define DO_API(a, r, n, p) extern r(*n) p
#include "il2cpp-api-functions.h"
#include <Windows.h>
#include <string>
#undef DO_API

#define DO_APP_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "il2cpp-functions.h"
#include <Windows.h>
#include <string>
}
#undef DO_APP_FUNC

#define DO_UP_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "il2cpp-unityplayer-functions.h"
#include <Windows.h>
#include <string>
}
#undef DO_UP_FUNC
