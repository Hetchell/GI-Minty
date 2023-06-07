#pragma once

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

const char* char_bub_initiate = R"MY_DELIMITER(
local function findHierarchyPath(child)
	local path = "/" .. child.name
	while child.transform.parent ~= nil do
	   child = child.transform.parent.gameObject
	   path = "/" .. child.name .. path
	end
	return path
 end

local function FindOffsetDummy()
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
	if avatarRoot.transform.childCount == 0 then
	   return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
	   local getCurrAvatar = avatarRoot.transform:GetChild(i)
	   if getCurrAvatar.gameObject.activeInHierarchy then
		  for j = 0, getCurrAvatar.transform.childCount - 1 do
			 local getOffsetDummy = getCurrAvatar.transform:GetChild(j)
			 if getOffsetDummy.name:find("OffsetDummy") then
				for k = 0, getOffsetDummy.transform.childCount - 1 do
				   local avatarModel = getOffsetDummy.transform:GetChild(k)
				   if avatarModel.name:find("Avatar") then
					  return findHierarchyPath(avatarModel.gameObject)
				   end
				end
			 end
		  end
	   end
	end
 end

local targetscale = CS.UnityEngine.Vector3(1,1,1)
local spine2 = "/Bip001/Bip001 Pelvis/Bip001 Spine/Bip001 Spine1/Bip001 Spine2"
local findboba = CS.UnityEngine.GameObject.Find(FindOffsetDummy() .. spine2 .. "/boba")
local left = CS.UnityEngine.GameObject.Find(FindOffsetDummy() .. spine2 .. "/+Breast L A01")
local right = CS.UnityEngine.GameObject.Find(FindOffsetDummy() .. spine2 .. "/+Breast R A01")

local function booba()    
    if CS.UnityEngine.GameObject.Find(FindOffsetDummy() .. spine2 .. "/boba") == nil then
        if right and left ~= nil then
            spineidk = CS.UnityEngine.GameObject.Find(FindOffsetDummy() .. spine2)
            bobaOBJ = CS.UnityEngine.GameObject("boba")
            bobaOBJ.transform.parent = spineidk.transform
            bobaOBJ.transform.localPosition = CS.UnityEngine.Vector3(0,0,0)
            bobaOBJ.transform.localRotation = CS.UnityEngine.Quaternion.Euler(0,0,0)
            right.transform.parent = bobaOBJ.transform
            left.transform.parent = bobaOBJ.transform
            bobaOBJ.transform.localScale = targetscale
            CS.MoleMole.ActorUtils.ShowMessage("Initiated")
        else
            CS.MoleMole.ActorUtils.ShowMessage("No boob found")
        end
    else
        bobaOBJ.transform.localScale = CS.UnityEngine.Vector3(1,1,1)
        CS.MoleMole.ActorUtils.ShowMessage("Initiated")
    end
 end

 local function onError(error)
    CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
end

xpcall(booba, onError)
)MY_DELIMITER";

const char* char_bub_resize = R"MY_DELIMITER(

local function findHierarchyPath(child)
	local path = "/" .. child.name
	while child.transform.parent ~= nil do
	   child = child.transform.parent.gameObject
	   path = "/" .. child.name .. path
	end
	return path
 end

local function FindOffsetDummy()
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
	if avatarRoot.transform.childCount == 0 then
	   return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
	   local getCurrAvatar = avatarRoot.transform:GetChild(i)
	   if getCurrAvatar.gameObject.activeInHierarchy then
		  for j = 0, getCurrAvatar.transform.childCount - 1 do
			 local getOffsetDummy = getCurrAvatar.transform:GetChild(j)
			 if getOffsetDummy.name:find("OffsetDummy") then
				for k = 0, getOffsetDummy.transform.childCount - 1 do
				   local avatarModel = getOffsetDummy.transform:GetChild(k)
				   if avatarModel.name:find("Avatar") then
					  return findHierarchyPath(avatarModel.gameObject) .. "/Bip001/Bip001 Pelvis/Bip001 Spine/Bip001 Spine1/Bip001 Spine2/boba"
				   end
				end
			 end
		  end
	   end
	end
 end

CS.UnityEngine.GameObject.Find(FindOffsetDummy()).transform.localScale = CS.UnityEngine.Vector3()MY_DELIMITER";

const char* char_modelswap_clone = R"MY_DELIMITER(
    local function findBodyPartWithName(model,queryName)
	for i = 0, model.transform.childCount - 1 do
		local child = model.transform:GetChild(i)
		if child.name:find(queryName) then
			return child.gameObject
		end
	end
end

local function getOtherAvatarBipLocalRotation(avatar)
	for i = 0, avatar.transform.childCount - 1 do
		local checkbip = avatar.transform:GetChild(i)
		if checkbip.name == "Bip001" then
			return checkbip.gameObject.transform.localRotation
		end
	end
end

local function getOtherAvatarBipRotation(avatar)
	for i = 0, avatar.transform.childCount - 1 do
		local checkbip = avatar.transform:GetChild(i)
		if checkbip.name == "Bip001" then
			return checkbip.gameObject.transform.rotation
		end
	end
end

local function findActiveCharacter() --get parent of offsetdummy
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
    if avatarRoot.transform.childCount == 0 then
		return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
        local getCurrAvatar = avatarRoot.transform:GetChild(i)
        if getCurrAvatar.gameObject.activeInHierarchy then --ensure that is active avatar rn
			return getCurrAvatar.gameObject
		end
    end	
end

local function findActiveCharacterBody(avatar)
	for i = 0, avatar.transform.childCount - 1 do
		local checkbody = avatar.transform:GetChild(i)
		if checkbody.name == "Body" then
			return checkbody.gameObject
		end
	end
end

local function findActiveCharacterModel() --get child of offsetdummy
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
    if avatarRoot.transform.childCount == 0 then
		return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
        local getCurrAvatar = avatarRoot.transform:GetChild(i)
        if getCurrAvatar.gameObject.activeInHierarchy then --ensure that is active avatar rn
			for j = 0, getCurrAvatar.transform.childCount - 1 do
				local getOffsetDummy = getCurrAvatar.transform:GetChild(j)
				if getOffsetDummy.name:find("OffsetDummy") then
					for k = 0, getOffsetDummy.transform.childCount - 1 do
						local avatarModel = getOffsetDummy.transform:GetChild(k)
						if avatarModel.name:find("Avatar") then
							return avatarModel.gameObject
						end
					end
				end
			end
		end
    end	
end

local function findHierarchyPath(child)
	local path = "/" .. child.name
	while child.transform.parent ~= nil do
		child = child.transform.parent.gameObject
		path = "/" .. child.name .. path
	end
	return path
end
		
local function swap()
	local currAvatarModel = findActiveCharacterModel()
		
	--clone
	local clonedModel = CS.UnityEngine.GameObject.Instantiate(currAvatarModel)
	clonedModel.transform.position = currAvatarModel.transform.position
	--clonedModel.transform.position.x = clonedModel.transform.position.x + 2
	
	--cloneroot for later reference
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
	local cloneAvatarRoot = CS.UnityEngine.GameObject.Instantiate(avatarRoot)
	for i = 0, cloneAvatarRoot.transform.childCount - 1 do
		local avatars = cloneAvatarRoot.transform:GetChild(i).gameObject
		avatars:SetActive(false)
	end
	cloneAvatarRoot.transform.parent = CS.UnityEngine.GameObject.Find("/EntityRoot").transform
	
	--destroy if exist
	local checkIfCloneRootExist = CS.UnityEngine.GameObject.Find("/EntityRoot/CloneRoot")
	if checkIfCloneRootExist ~= nil then
		CS.UnityEngine.Object.Destroy(checkIfCloneRootExist.gameObject)
	end
	
	cloneAvatarRoot.name = "CloneRoot"
	
	--set parent to this clone root
	clonedModel.transform.parent = cloneAvatarRoot.transform
	CS.MoleMole.ActorUtils.ShowMessage("cloned at" .. findHierarchyPath(clonedModel))
end

local function onError(error)
	CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
end

xpcall(swap, onError)
)MY_DELIMITER";

const char* char_modelswap_paste = R"MY_DELIMITER(
    local function findBodyPartWithName(model,queryName)
	for i = 0, model.transform.childCount - 1 do
		local child = model.transform:GetChild(i)
		if child.name:find(queryName) then
			return child.gameObject
		end
	end
end

local function getOtherAvatarBipLocalRotation(avatar)
	for i = 0, avatar.transform.childCount - 1 do
		local checkbip = avatar.transform:GetChild(i)
		if checkbip.name == "Bip001" then
			return checkbip.gameObject.transform.localRotation
		end
	end
end

local function getOtherAvatarBipRotation(avatar)
	for i = 0, avatar.transform.childCount - 1 do
		local checkbip = avatar.transform:GetChild(i)
		if checkbip.name == "Bip001" then
			return checkbip.gameObject.transform.rotation
		end
	end
end

local function findActiveCharacterBody(avatar)
	for i = 0, avatar.transform.childCount - 1 do
		local checkbody = avatar.transform:GetChild(i)
		if checkbody.name == "Body" then
			return checkbody.gameObject
		end
	end
end

local function findActiveCharacter(path) --get parent of offsetdummy
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/" .. path);
    if avatarRoot.transform.childCount == 0 then
		return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
        local getCurrAvatar = avatarRoot.transform:GetChild(i)
        if getCurrAvatar.gameObject.activeInHierarchy then --ensure that is active avatar rn
			return getCurrAvatar.gameObject
		end
    end	
end

local function findActiveCharacterModel() --get child of offsetdummy
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot");
    if avatarRoot.transform.childCount == 0 then
		return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
        local getCurrAvatar = avatarRoot.transform:GetChild(i)
        if getCurrAvatar.gameObject.activeInHierarchy then --ensure that is active avatar rn
			for j = 0, getCurrAvatar.transform.childCount - 1 do
				local getOffsetDummy = getCurrAvatar.transform:GetChild(j)
				if getOffsetDummy.name:find("OffsetDummy") then
					for k = 0, getOffsetDummy.transform.childCount - 1 do
						local avatarModel = getOffsetDummy.transform:GetChild(k)
						if avatarModel.name:find("Avatar") then
							return avatarModel.gameObject
						end
					end
				end
			end
		end
    end	
end

local function findCharacterObj(path , part_name) --get child of offsetdummy
	local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/" .. path);
    if avatarRoot.transform.childCount == 0 then
		return
	end
	for i = 0, avatarRoot.transform.childCount - 1 do
        local getCurrAvatar = avatarRoot.transform:GetChild(i)
        if getCurrAvatar.gameObject.activeInHierarchy then --ensure that is active avatar rn
			local components = getCurrAvatar.gameObject:GetComponentsInChildren(typeof(CS.UnityEngine.Transform))
			for j = 0, components.Length - 1 do
				local component = components[j]
				if component.name:find(part_name) then
					return component.gameObject
				end
			end
		end
    end	
end

local function swap()
	--get current and destroy?
	local currAvatarModel = findActiveCharacterModel()
	
	--now get other onfield
	local clonedAvatarModel = findActiveCharacter("CloneRoot")
	
	--get weaponroot of chars
	local currAvatarWeaponRoot = findCharacterObj("AvatarRoot", "WeaponRoot")
	local currAvatarWeaponL = findCharacterObj("AvatarRoot", "WeaponL")
	local currAvatarWeaponR = findCharacterObj("AvatarRoot", "WeaponR")
	
	local clonedAvatarWeaponRoot = findCharacterObj("CloneRoot","Bip001 Spine1")
	local clonedAvatarWeaponL = findCharacterObj("CloneRoot","Bip001 L Hand")
	local clonedAvatarWeaponR = findCharacterObj("CloneRoot","Bip001 R Hand")
	
	--eye fix finding
	local currAvatarEyeL = findCharacterObj("AvatarRoot", "+EyeBone L A01")
	local currAvatarEyeR = findCharacterObj("AvatarRoot", "+EyeBone R A01")
	local currAvatarToothD = findCharacterObj("AvatarRoot", "+ToothBone D A01")
	local currAvatarToothU = findCharacterObj("AvatarRoot", "+ToothBone U A01")
	local currAvatarFlyCloak = findCharacterObj("AvatarRoot", "+FlycloakRootB CB A01")
	
	local clonedAvatarHeadBone = findCharacterObj("CloneRoot","Bip001 Head")
	local clonedAvatarGlider = findCharacterObj("CloneRoot","Bip001 Spine2")
	
	if clonedAvatarModel == nil then
		CS.MoleMole.ActorUtils.ShowMessage("no cloned avatar found")
		return
	end

	--animator get for now later swap
	--local active_char_anim = currAvatarModel:GetComponent(typeof(CS.UnityEngine.Animator))
	--local cloned_char_anim = clonedAvatarModel:GetComponent(typeof(CS.UnityEngine.Animator))
	--active_char_anim:SetAvatar(cloned_char_anim.avatar)
	
		
	--destroy current avatar parts coz why not
	for index = 0, currAvatarModel.transform.childCount - 1 do
		local currBodyPart = currAvatarModel.transform:GetChild(index).transform
		if currBodyPart.name == "Brow" then
			CS.UnityEngine.Object.Destroy(currBodyPart.gameObject)
			--currBodyPart.gameObject:SetActive(false)
		elseif currBodyPart.name == "Face" then
			CS.UnityEngine.Object.Destroy(currBodyPart.gameObject)
			--currBodyPart.gameObject:SetActive(false)
		elseif currBodyPart.name == "Face_Eye" then
			CS.UnityEngine.Object.Destroy(currBodyPart.gameObject)
			--currBodyPart.gameObject:SetActive(false)
		elseif currBodyPart.name == "Root" then
			--donothing but i want keep this active
		elseif currBodyPart.name == "Bip001" then
			--currBodyPart:AddComponent(RotationController)
			--currBodyPart.localRotation = CS.UnityEngine.Quaternion.Euler(CS.UnityEngine.Vector3(90.0,getOtherAvatarBipLocalRotation(clonedAvatarModel).y,getOtherAvatarBipLocalRotation(clonedAvatarModel).z))
			--currBodyPart.rotation = CS.UnityEngine.Quaternion.Euler(CS.UnityEngine.Vector3(90.0,getOtherAvatarBipRotation(clonedAvatarModel).y,getOtherAvatarBipRotation(clonedAvatarModel).z))
		else
			currBodyPart.gameObject:SetActive(false) --default setinactive
		end
	end
			
	--clone and replace
	for i = 0, clonedAvatarModel.transform.childCount - 1 do
		local originalPart = clonedAvatarModel.transform:GetChild(0).gameObject
		--refixes roots for weaps TODO CYNO AND YAE SEX
		if originalPart.name:find("Root") then
			originalPart.name = "Root_OLD"
		end
		originalPart.transform:SetParent(currAvatarModel.transform)
		originalPart.transform:SetSiblingIndex(0)
	end

	--swap weapon root
	currAvatarWeaponRoot.transform.parent = clonedAvatarWeaponRoot.transform
	currAvatarWeaponL.transform.parent = clonedAvatarWeaponL.transform
	currAvatarWeaponR.transform.parent = clonedAvatarWeaponR.transform
	currAvatarWeaponRoot.transform:SetSiblingIndex(0)
	currAvatarWeaponL.transform:SetSiblingIndex(0)
	currAvatarWeaponR.transform:SetSiblingIndex(0)
	
	--setclip this will fix no blink
	local originClip = clonedAvatarModel:GetComponent(typeof(CS.miHoYoEmotion.ClipShapeManager))
    local targetClip = currAvatarModel:GetComponent(typeof(CS.miHoYoEmotion.ClipShapeManager))
    targetClip.currModelBindingList = originClip.currModelBindingList
    targetClip.faceMaterial = originClip.faceMaterial
	
	--set eyekey
	local originEyeKey = clonedAvatarModel:GetComponent(typeof(CS.miHoYoEmotion.EyeKey))
    local targetEyeKey = currAvatarModel:GetComponent(typeof(CS.miHoYoEmotion.EyeKey))
	targetEyeKey._leftEyeBoneHash = originEyeKey._leftEyeBoneHash;
    targetEyeKey._leftEyeBallScaleTarget = originEyeKey._leftEyeBallScaleTarget;
    targetEyeKey._leftEyeBoneHash = originEyeKey._leftEyeBoneHash;
    targetEyeKey._leftEyeRotTarget = originEyeKey._leftEyeRotTarget;
    targetEyeKey._originDownTeethPos = originEyeKey._originDownTeethPos;
    targetEyeKey._originDownTeethRot = originEyeKey._originDownTeethRot;
    targetEyeKey._originDownTeethScale = originEyeKey._originDownTeethScale;
    targetEyeKey._originLeftEyeBallRot = originEyeKey._originLeftEyeBallRot;
    targetEyeKey._originLeftEyeBallScale = originEyeKey._originLeftEyeBallScale;
    targetEyeKey._originLeftEyeRot = originEyeKey._originLeftEyeRot;
    targetEyeKey._originLeftEyeScale = originEyeKey._originLeftEyeScale;
    targetEyeKey._originRightEyeBallRot = originEyeKey._originRightEyeBallRot;
    targetEyeKey._originRightEyeBallScale = originEyeKey._originRightEyeBallScale;
    targetEyeKey._originRightEyeRot = originEyeKey._originRightEyeRot;
    targetEyeKey._originRightEyeScale = originEyeKey._originRightEyeScale;
    targetEyeKey._originUpTeethRot = originEyeKey._originUpTeethRot;
    targetEyeKey._originUpTeethScale = originEyeKey._originUpTeethScale;
    targetEyeKey._rightEyeBallBoneHash = originEyeKey._rightEyeBallBoneHash;
    targetEyeKey._rightEyeBallScaleTarget = originEyeKey._rightEyeBallScaleTarget;
    targetEyeKey._rightEyeBoneHash = originEyeKey._rightEyeBoneHash;
    targetEyeKey._rightEyeRotTarget = originEyeKey._rightEyeRotTarget;
    targetEyeKey._rotDuration = originEyeKey._rotDuration;
    targetEyeKey._rotTargetCurrtime = originEyeKey._rotTargetCurrtime;
    targetEyeKey._scaleDuration = originEyeKey._scaleDuration;
    targetEyeKey._scaleTargetCurrtime = originEyeKey._scaleTargetCurrtime;
    targetEyeKey._teethDownHash = originEyeKey._teethDownHash;
    targetEyeKey._teethUpHash = originEyeKey._teethUpHash;
    targetEyeKey.currentController = originEyeKey.currentController;
    targetEyeKey.leftEyeBallBone = originEyeKey.leftEyeBallBone;
    targetEyeKey.leftEyeBallRot = originEyeKey.leftEyeBallRot;
    targetEyeKey.leftEyeBallScale = originEyeKey.leftEyeBallScale;
    targetEyeKey.leftEyeBone = originEyeKey.leftEyeBone;
    targetEyeKey.leftEyeRot = originEyeKey.leftEyeRot;
    targetEyeKey.leftEyeScale = originEyeKey.leftEyeScale;
    targetEyeKey.rightEyeBallBone = originEyeKey.rightEyeBallBone;
    targetEyeKey.rightEyeBallRot = originEyeKey.rightEyeBallRot;
    targetEyeKey.rightEyeBallScale = originEyeKey.rightEyeBallScale;
    targetEyeKey.rightEyeBone = originEyeKey.rightEyeBone;
    targetEyeKey.rightEyeRot = originEyeKey.rightEyeRot;
    targetEyeKey.rightEyeScale = originEyeKey.rightEyeScale;
    targetEyeKey.teethDownBone = originEyeKey.teethDownBone;
    targetEyeKey.teethDownPos = originEyeKey.teethDownPos;
    targetEyeKey.teethDownRot = originEyeKey.teethDownRot;
    targetEyeKey.teethDownScale = originEyeKey.teethDownScale;
    targetEyeKey.teethUpBone = originEyeKey.teethUpBone;
    targetEyeKey.teethUpRot = originEyeKey.teethUpRot;
    targetEyeKey.teethUpScale = originEyeKey.teethUpScale;
	
	--eye tooth and glider fix
	currAvatarEyeL.transform.parent = clonedAvatarHeadBone.transform
	currAvatarEyeR.transform.parent = clonedAvatarHeadBone.transform
	currAvatarToothD.transform.parent = clonedAvatarHeadBone.transform
	currAvatarToothU.transform.parent = clonedAvatarHeadBone.transform
	currAvatarFlyCloak.transform.parent = clonedAvatarGlider.transform
	currAvatarEyeL.transform:SetSiblingIndex(0)
	currAvatarEyeR.transform:SetSiblingIndex(0)
	currAvatarToothD.transform:SetSiblingIndex(0)
	currAvatarToothU.transform:SetSiblingIndex(0)
	currAvatarFlyCloak.transform:SetSiblingIndex(0)
	
	--toggle on off refresh?
	local activeAvatar = findActiveCharacter("AvatarRoot")
	local activeAvatarBody = findActiveCharacterBody(currAvatarModel)
	activeAvatar:SetActive(false)
	activeAvatar:SetActive(true)
	--activeAvatarBody:SetActive(false)
	
	CS.MoleMole.ActorUtils.ShowMessage("Swapped!")
end

local function onError(error)
	CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
end

xpcall(swap, onError)
)MY_DELIMITER";


        const char* animation_options[] = {
        "ActivitySkill_ElectricCoreFly",
        "Akimbo02AS",
        "Akimbo02BS",
        "Akimbo02Loop",
        "Attack01",
        "Attack02",
        "Attack03",
        "Attack04",
        "Attack05",
        "ChannelAS",
        "ChannelBS",
        "ChannelLoop",
        "ClimbDownToGround",
        "ClimbIdle",
        "ClimbJump",
        "ClimbMove0",
        "ClimbMove1",
        "CrouchDrop",
        "CrouchIdle",
        "CrouchMove",
        "CrouchRoll",
        "CrouchToStandby",
        "DropDown",
        "ExtraAttack",
        "ExtraAttack_AS",
        "FallDie",
        "FallDie_AS",
        "FallOnGround",
        "FallOnGroundLit",
        "FallToGroundRun",
        "FallToGroundRunHard",
        "FallToGroundSprint",
        "FallingAnthem_AS_1",
        "FallingAnthem_AS_2",
        "FallingAnthem_BS_1",
        "FallingAnthem_BS_2",
        "FallingAnthem_Loop",
        "FallingAnthem_Loop_Low",
        "Fly",
        "FlyStart",
        "FrozenWindmill",
        "FrozenWindmill_AS",
        "HitGroundDie",
        "Hit_H",
        "Hit_L",
        "Hit_Throw",
        "Hit_ThrowAir",
        "Hit_Throw_Ground",
        "Icespine",
        "Icespine_Out",
        "Jump",
        "JumpForRun",
        "JumpForSprint",
        "JumpForWalk",
        "JumpOffWall",
        "JumpUpWallForStandby",
        "JumpUpWallReady",
        "LiquidStrike_AS",
        "LiquidStrike_AS_OnWater",
        "LiquidStrike_BS",
        "LiquidStrike_BS1",
        "LiquidStrike_BS_0",
        "LiquidStrike_FatalMove",
        "LiquidStrike_FatalStandby",
        "LiquidStrike_Move",
        "LiquidStrike_MoveStandby",
        "LiquidStrike_Strike",
        "NormalDie",
        "PlayMusic_Lyre_AS",
        "PlayMusic_Lyre_BS",
        "PlayMusic_Lyre_Loop",
        "PlayMusic_Qin_AS",
        "PlayMusic_Qin_BS",
        "PlayMusic_Qin_Loop",
        "Run",
        "RunToIdle",
        "RunToWalk",
        "ShowUp",
        "SitBDown",
        "SitBLoop",
        "SitBUp",
        "SitDown",
        "SitLoop",
        "SitUp",
        "SkiffNormal",
        "SlipBackWall",
        "SlipFaceWall",
        "Sprint",
        "SprintBS",
        "SprintToIdle",
        "SprintToRun",
        "Standby",
        "Standby2ClimbA",
        "Standby2ClimbB",
        "StandbyPutaway",
        "StandbyPutawayOver",
        "StandbyShow_01",
        "StandbyShow_02",
        "StandbyVoice",
        "StandbyWeapon",
        "Struggle",
        "SwimDash",
        "SwimDie",
        "SwimIdle",
        "SwimJump",
        "SwimJumpDrop",
        "SwimJumpToWater",
        "SwimMove",
        "Think01AS",
        "Think01BS",
        "Think01Loop",
        "TurnDir",
        "Upstairs",
        "Walk",
        "WalkToIdle",
        "WalkToRun"
        };

        const char* emo_options[] = {
            "Angry05",
            "Angry06",
            "Closed01",
            "Closed02",
            "Closed03",
            "Closed04",
            "Closed05",
            "Happy01",
            "Happy02",
            "Happy03",
            "Happy04",
            "Happy05",
            "Normal01",
            "Normal02",
            "Normal03",
            "Normal04",
            "Normal05",
            "Normal06",
            "Sad01",
            "Sad02",
            "Sad03",
            "Sad04",
            "Sad05",
            "Surprise01",
            "Surprise02",
            "Surprise03",
            "Surprise04",
            "Surprise05",
            "Sweat01",
            "Sweat02",
            "Sweat03",
            "Sweat04",
            "Sweat05",
            "Tired01",
            "Tired02",
            "Tired03",
            "Tired04",
            "Tired05",
            "Default",
            "Angry_01",
            "Angry_02",
            "Angry_03",
            "Angry_04",
            "Default_01",
            "Doubt_01",
            "Doubt_02",
            "Doubt_03",
            "Doubt_04",
            "Gentle_01",
            "Gentle_02",
            "Gentle_03",
            "Gentle_04",
            "HiClosed_01",
            "HiClosed_02",
            "HiClosed_03",
            "HiClosed_04",
            "HiClosed_05",
            "HiClosed_06",
            "HiClosed_07",
            "LowClosed_01",
            "LowClosed_02",
            "LowClosed_03",
            "LowClosed_04",
            "LowClosed_05",
            "LowClosed_06",
            "LowClosed_07",
            "MidClosed_01",
            "MidClosed_02",
            "MidClosed_03",
            "MidClosed_04",
            "MidClosed_05",
            "MidClosed_06",
            "MidClosed_07",
            "Normal_01",
            "Normal_02",
            "Normal_03",
            "Normal_04",
            "Normal_05",
            "Surprise_01",
            "Surprise_02",
            "Sweat_01",
            "Sweat_02",
            "Sweat_03",
            "Sweat_04"
        };

        const char* pho_options[] = {
            "P_None",
            "P_A",
            "P_O",
            "P_E",
            "P_I",
            "P_U",
            "P_N",
            "P_Smile01",
            "P_Smile02",
            "P_Smile03",
            "P_Smile04",
            "P_Smile05",
            "P_Smile06",
            "P_Angry01",
            "P_Angry02",
            "P_Angry03",
            "P_Angry04",
            "P_Doya01",
            "P_Doya02",
            "P_Pero01",
            "P_Pero02",
            "P_Neko01",
            "P_Neko02",
            "P_Delta01",
            "P_Delta02",
            "P_Square01",
            "P_Line01",
            "P_TalkNone01",
            "P_TalkNone02",
            "P_TalkNone03",
            "P_TalkSmile01",
            "P_TalkSmile02",
            "P_TalkSmile03",
            "P_TalkAngry01",
            "P_TalkAngry02",
            "P_TalkAngry03",
            "P_TalkNone04",
            "P_TalkDoya01",
            "P_TalkSquare01",
            "P_TalkDelta01",
            "P_TalkSmile04",
            "P_Default",
            "P_Default01",
            "P_Normal01",
            "P_Doya03",
            "P_Angry05",
            "P_Fury01",
            "P_A01",
            "P_I01",
            "P_U01",
            "P_E01",
            "P_O01",
            "P_N01",
            "P_TalkNormal121",
            "P_TalkNormal122",
            "P_TalkNormal131",
            "P_TalkNormal132",
            "P_TalkNormal221",
            "P_TalkNormal222",
            "P_TalkNormal231",
            "P_TalkNormal232",
            "P_TalkNormal321",
            "P_TalkNormal322",
            "P_TalkNormal331",
            "P_TalkSmile121",
            "P_TalkSmile122",
            "P_TalkSmile131",
            "P_TalkSmile132",
            "P_TalkSmile221",
            "P_TalkSmile222",
            "P_TalkSmile231",
            "P_TalkSmile232",
            "P_TalkSmile321",
            "P_TalkSmile322",
            "P_TalkSmile331",
            "P_TalkAngry121",
            "P_TalkAngry122",
            "P_TalkAngry131",
            "P_TalkAngry132",
            "P_TalkAngry221",
            "P_TalkAngry222",
            "P_TalkAngry231",
            "P_TalkAngry232",
            "P_TalkAngry321",
            "P_TalkAngry322",
            "P_TalkAngry331",
            "P_Default_01",
            "P_A_01",
            "P_I_01",
            "P_U_01",
            "P_E_01",
            "P_O_01",
            "P_N_01",
            "P_Angry_01",
            "P_Angry_02",
            "P_Angry_03",
            "P_Angry_04",
            "P_Angry_05",
            "P_Doya_01",
            "P_Doya_02",
            "P_Doya_03",
            "P_Fury_01",
            "P_Neko_01",
            "P_Neko_02",
            "P_Normal_01",
            "P_Smile_01",
            "P_Smile_02",
            "P_Smile_03",
            "P_Smile_04",
            "P_Smile_05",
            "P_Talk_Angry_121",
            "P_Talk_Angry_122",
            "P_Talk_Angry_131",
            "P_Talk_Angry_132",
            "P_Talk_Angry_221",
            "P_Talk_Angry_222",
            "P_Talk_Angry_231",
            "P_Talk_Angry_232",
            "P_Talk_Angry_321",
            "P_Talk_Angry_322",
            "P_Talk_Angry_331",
            "P_Talk_Normal_121",
            "P_Talk_Normal_122",
            "P_Talk_Normal_131",
            "P_Talk_Normal_132",
            "P_Talk_Normal_221",
            "P_Talk_Normal_222",
            "P_Talk_Normal_231",
            "P_Talk_Normal_232",
            "P_Talk_Normal_321",
            "P_Talk_Normal_322",
            "P_Talk_Normal_331",
            "P_Talk_Smile_121",
            "P_Talk_Smile_122",
            "P_Talk_Smile_131",
            "P_Talk_Smile_132",
            "P_Talk_Smile_221",
            "P_Talk_Smile_222",
            "P_Talk_Smile_231",
            "P_Talk_Smile_232",
            "P_Talk_Smile_321",
            "P_Talk_Smile_322",
            "P_Talk_Smile_331",
            "P_Pero_01",
            "P_Pero_02"
        };


        const char* animchangerreturn = R"MY_DELIMITER(
local function find_active_char()
    local avatarroot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
    for i = 0, avatarroot.transform.childCount - 1 do
        local child = avatarroot.transform:GetChild(i)
        if child.gameObject.activeInHierarchy then
            return child.gameObject
        end
    end
end

local function find_body(avatar)
    for i = 0, avatar.transform.childCount - 1 do
        local transform = avatar.transform:GetChild(i)

        if transform.name == "OffsetDummy" then
            return transform
        end
    end
end

local function AnimChanger()
	local avatar = find_active_char()
	CS.MoleMole.ActorUtils.ShowMessage(find_body(avatar):GetChild(0).name)
	local obj = find_body(avatar):GetChild(0)
	local ac = obj:GetComponent("Animator")
	ac:Rebind()
end

local function onError(error)
    CS.UnityEngine.GameObject.Find("/BetaWatermarkCanvas(Clone)/Panel/TxtUID"):GetComponent("Text").text = tostring(error)
	CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
end

xpcall(AnimChanger, onError)
)MY_DELIMITER";

        const char* animchanger = R"MY_DELIMITER(
local function find_active_char()
    local avatarroot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
    for i = 0, avatarroot.transform.childCount - 1 do
        local child = avatarroot.transform:GetChild(i)
        if child.gameObject.activeInHierarchy then
            return child.gameObject
        end
    end
end

local function find_body(avatar)
    for i = 0, avatar.transform.childCount - 1 do
        local transform = avatar.transform:GetChild(i)

        if transform.name == "OffsetDummy" then
            return transform
        end
    end
end

local function AnimChanger()
	local avatar = find_active_char()
	CS.MoleMole.ActorUtils.ShowMessage(find_body(avatar):GetChild(0).name)
	local obj = find_body(avatar):GetChild(0)
	local ac = obj:GetComponent("Animator")
	ac:Play(")MY_DELIMITER";

        const char* animchanger2 = R"MY_DELIMITER(", 0) -- turn on
	--ac:Rebind() -- turn off
end

local function onError(error)
	CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
end

xpcall(AnimChanger, onError)
)MY_DELIMITER";

        const char* emochengemo1 = R"MY_DELIMITER(
local function find_active_char()
    local avatarroot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
    for i = 0, avatarroot.transform.childCount - 1 do
        local child = avatarroot.transform:GetChild(i)
        if child.gameObject.activeInHierarchy then
            return child.gameObject
        end
    end
end

local function find_body(avatar)
    for i = 0, avatar.transform.childCount - 1 do
        local transform = avatar.transform:GetChild(i)

        if transform.name == "OffsetDummy" then
            return transform
        end
    end
end

local function EmoChanger()
	local avatar = find_active_char()
	CS.MoleMole.ActorUtils.ShowMessage(find_body(avatar):GetChild(0).name)
	local obj = find_body(avatar):GetChild(0)
	local emo = obj:GetComponent("EmoSync")
	emo:SetEmotion(")MY_DELIMITER";

        const char* emochengemo2 = R"MY_DELIMITER(",0)
	emo:SetPhoneme(")MY_DELIMITER";

        const char* emochengpho2 = R"MY_DELIMITER(",0)
	emo:EmoFinish()
end

local function onError(error)
	CS.MoleMole.ActorUtils.ShowMessage(tostring(error))
end

xpcall(EmoChanger, onError)
)MY_DELIMITER";

        const char* char_uicamera_on = R"MY_DELIMITER(CS.UnityEngine.GameObject.Find("/UICamera"):GetComponent("Camera").enabled = true)MY_DELIMITER";

        const char* char_uicamera_off = R"MY_DELIMITER(CS.UnityEngine.GameObject.Find("/UICamera"):GetComponent("Camera").enabled = false)MY_DELIMITER";

        const char* char_browser_on = R"MY_DELIMITER(

local function findActiveAvatar()
    local avatarRoot = CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot")
    if avatarRoot.transform.childCount == 0 then
        return
    end
    for i = 0, avatarRoot.transform.childCount - 1 do
        local avatar = avatarRoot.transform:GetChild(i)
        if avatar.gameObject.activeInHierarchy then
            return avatar.gameObject
        end
    end
end

local function findAvatarBody(avatar)
    for i = 0, avatar.transform.childCount - 1 do
        local transform = avatar.transform:GetChild(i)
        if transform.name == "OffsetDummy" then
            for j = 0, transform.childCount - 1 do
                local child = transform:GetChild(j)
                for k = 0, child.transform.childCount - 1 do
                    local body = child.transform:GetChild(k)
                    if body.name == "Body" then
                        return body.gameObject
                    end
                end
            end
        end
    end
end
local function createPrimitive()
    local nowAvatar = findActiveAvatar()
    local nowBody = findAvatarBody(nowAvatar)
    local primitive = CS.UnityEngine.GameObject.CreatePrimitive(CS.UnityEngine.PrimitiveType.Plane);
    primitive.transform.localScale = CS.UnityEngine.Vector3(3.2,1,1.8);
    primitive.transform.localRotation = CS.UnityEngine.Quaternion(0.5, 0.5,-0.5, 0.5);
	primitive.name = "BrowserObject"
    local position = nowBody.transform.position
    primitive.transform.position = CS.UnityEngine.Vector3(position.x, position.y + 5, position.z);
    local browser = primitive:AddComponent(typeof(CS.ZenFulcrum.EmbeddedBrowser.Browser));
	browser._width = 1920;
    browser._height = 1080;
    browser._url = "https://google.com";

end
function start()
    createPrimitive()
end

start()

)MY_DELIMITER";
        const char* char_browser_off = R"MY_DELIMITER(
CS.UnityEngine.Object.Destroy(CS.UnityEngine.GameObject.Find("/BrowserObject"))
)MY_DELIMITER";

        const char* char_avatarresize = R"MY_DELIMITER(
CS.UnityEngine.GameObject.Find("/EntityRoot/AvatarRoot").transform.localScale = CS.UnityEngine.Vector3()MY_DELIMITER";
}