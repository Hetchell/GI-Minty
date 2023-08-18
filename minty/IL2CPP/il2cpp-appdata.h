//#include "il2cpp-types.h"
#include "../includes.h"
#include "../ImGui/ImGuiNotify/imgui_notify.h"

#define DO_API(OF_OFFSET, CN_OFFSET, r, n, p) extern r(*n) p
	#include "il2cpp-api-functions.h"
	#include <Windows.h>
	//#include "il2cpp-types.h"
	#include <string>
#undef DO_API

//#include "il2cpp-types.h"
#define DO_APP_FUNC(OS_OFFSET, CN_OFFSET, r, n, p) extern r(*n) p
#define DO_TYPEDEF(OS_OFFSET, n) extern n ## __Class** n ## __TypeInfo
#define DO_APP_FUNC_METHODINFO(OS_OFFSET, n) extern struct MethodInfo ** n
namespace app
{
	#include "il2cpp-functions.h"
	#include <Windows.h>
	#include <string>
}
#undef DO_APP_FUNC
#undef DO_TYPEDEF
#undef DO_APP_FUNC_METHODINFO

#define DO_UP_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "il2cpp-unityplayer-functions.h"
//#include "il2cpp-types.h"
#include <Windows.h>
#include <string>
}
#undef DO_UP_FUNC

#define DO_MD1_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "mDumper-funcs.h"
	//#include "il2cpp-types.h"
#include <Windows.h>
#include <string>
}
#undef DO_MD1_FUNC

#define DO_TYPEDEF(a, n) extern n ## __Class** n ## __TypeInfo
namespace app
{
	#include "il2cpp-types.h"
}
#undef DO_TYPEDEF
/*
#define DO_MD2_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "mDumper-funcs.h"
	//#include "il2cpp-types.h"
#include <Windows.h>
#include <string>
}
#undef DO_MD2_FUNC

#define DO_MD3_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "mDumper-funcs.h"
	//#include "il2cpp-types.h"
#include <Windows.h>
#include <string>
}
#undef DO_MD3_FUNC

#define DO_MD4_FUNC(a, r, n, p) extern r(*n) p
namespace app
{
#include "mDumper-funcs.h"
	//#include "il2cpp-types.h"
#include <Windows.h>
#include <string>
}
#undef DO_MD4_FUNC
*/
