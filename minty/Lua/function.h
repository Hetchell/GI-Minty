//#include "../Lua/luahook.h"

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
namespace {
const char* xluaHotFix = R"MY_DELIMITER(local import_type = xlua.import_type
local pool = CS.XLua.ObjectTranslatorPool.Instance
local test = pool.lastTranslator.assemblies.Count
local metatable = getmetatable(CS)

local function import_type_mhy(t)
    local translator = pool.lastTranslator
    local orig_asm = translator.assembly
    local asms = translator.assemblies
    for i=0, asms.Count-1 do
        local obj = import_type(t)
        if obj == true then
            translator.assembly = orig_asm
            return obj
        end
        translator.assembly = asms[i]
    end

    translator.assembly = orig_asm
    return nil
end

-- https://github.com/Tencent/xLua/blob/master/Assets/XLua/Src/LuaEnv.cs#L472
metatable.__index = function(self, key)
    local fqn = rawget(self,'.fqn')
    fqn = ((fqn and fqn .. '.') or '') .. key

    local obj = import_type_mhy(fqn)

    if obj == nil then
        -- It might be an assembly, so we load it too.
        obj = { ['.fqn'] = fqn }
        setmetatable(obj, metatable)
    elseif obj == true then
        return rawget(self, key)
    end

    -- Cache this lookup
    rawset(self, key, obj)
    return obj
end)MY_DELIMITER";
}