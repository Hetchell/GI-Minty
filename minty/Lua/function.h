#include "../Lua/luahook.h"

const char* char_eleminf = R"MY_DELIMITER(
local function normalattack()
local effectpool = CS.UnityEngine.GameObject.Find("/EffectPool")
--loop through all the children of the effectpool
for i = 0, effectpool.transform.childCount - 1 do
local child = effectpool.transform:GetChild(i)
if string.match(child.gameObject.name, "Attack") then
for k = 0, child.transform.childCount - 1 do
local bladechild = child.transform : GetChild(k)
if string.match(bladechild.gameObject.name, "e") then
local success, result = pcall(function()
    bladechild.gameObject:GetComponent(typeof(CS.UnityEngine.ParticleSystem)).main.startColor = CS.UnityEngine.ParticleSystem.MinMaxGradient(CS.UnityEngine.Color()MY_DELIMITER";

const char* char_eleminf_end = R"MY_DELIMITER(
))
    end)
    if not success then
        end
        end
        end
        end
        end
        end
        function onError(error)
        CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
        end
        xpcall(normalattack, onError)
)MY_DELIMITER";

void lua_runstr(const char* charLuaScript) {

    auto compiled = compile(gi_LL, charLuaScript);
    if (!compiled)
        return;
    auto copy = new std::string(compiled.value());
    auto execute = [](ULONG_PTR compiled)
    {
        auto str = (const std::string*)compiled;
        exec(*str);
        delete str;
    };
    QueueUserAPC(execute, main_thread, (ULONG_PTR)copy);
};