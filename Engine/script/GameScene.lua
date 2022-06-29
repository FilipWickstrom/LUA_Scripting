Player			= require('script/Player')
player			= Player:New()
refMonster		= require('script/Monster')
refMonkey		= require('script/ThrowingEnemy')
boss			= require('script/BasicBossEnemy')
refThrowBoss	= require('script/ThrowingBoss')
powerup			= require('script/Powerups')
goldText		= require('script/GoldText')
refCamera		= require('script/Camera')
lastpickupText	= require('script/lastpickuptext')
require('script/AllScenes')
require('script/File')

-- Collect separate types in different tables
monsters = {}
objects = {}

function AddMonster(modelfilepath)
	local monster = refMonster:New()
	monster.id = C_LoadSprite(modelfilepath)
	table.insert(monsters, monster)
end

-- Returns all variables from the monsters table, in this case userdata.
--function getMonsters()
	--return table.unpack(monsters)
--end

function Start()
	math.randomseed(os.time())
	--AddMonster('skeleton.png')
	--AddMonster('skeleton.png')

	--local newMonkey = refMonkey:New()
	--local throwBoss = refThrowBoss:New()

	powerup = require('script/Powerups'):New()
	goldText:Initialize()
	lastpickupText:Initialize(player)

	--Camera setup
	camera = refCamera:New()
	camera:SetPosition(0,40,0)
	camera:SetTarget(0,0,0.1)
	camera:SetFOV(90)

	objects = Load_File('maps/test1.txt')

	-- write down file
	Write_To_File(objects, 'maps/test1.txt')

	--print("Num of objects: " .. #objects)
end

-- Destroying everything
function Clean()



	print("### Removing player ###")
	player:OnEnd()

	print("### Removing objects ###")
	for k, v in pairs(objects) do
		v:OnEnd()
	end

	--print("### Removing powerups ###")
	--for k, v in pairs(powerups) do
	--	v:OnEnd()
	--end
end

-- Game loop
function Update(dt)
	deltatime = dt

	-- Loop through all objects
	for num, obj in pairs(objects) do
		if obj ~= nil then 
			if obj.hp > 0 then
				obj:Update(player)
			else
				RemoveObject(num, obj)
			end
		end
	end

	-- Update powerup
	if powerup ~= nil then
		powerup:Update(player, objects, goldText, lastpickupText)
	end

	-- Go back to menu when player dies
	if(player:IsAlive() == false) then
		C_ChangeScene(Scenes.GAMEOVER)
	end

	-- Update player
	player:Update(camera)
end


function RemoveObject(num, obj)

	if obj.name == "enemy" then
		obj:OnDeath(player.gold)
	end

	table.remove(objects, num)
	C_RemoveSprite(obj.id)
	C_RemoveUI(obj.gid)

end