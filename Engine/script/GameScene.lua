Player = require('script/Player')
player = Player:New()
refMonster = require('script/Monster')
refMonkey = require('script/ThrowingEnemy')
boss = require('script/BasicBossEnemy'):New()
refThrowBoss = require('script/ThrowingBoss')
powerup = require('script/Powerups')

-- Collect separate types in different tables
monsters = {}

local deltatime = 0

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
	AddMonster('skeleton.png')
	AddMonster('skeleton.png')

	local newMonkey = refMonkey:New()
	local throwBoss = refThrowBoss:New()

	powerup = require('script/Powerups'):New()
	
	table.insert(monsters, newMonkey)
	table.insert(monsters, boss)
	table.insert(monsters, throwBoss)
end

-- Destroying everything
function Clean()
	print("### Removing player ###")
	player:OnEnd()

	print("### Removing monsters ###")
	for k, v in pairs(monsters) do
		v:OnEnd()
	end

	--print("### Removing powerups ###")
	--for k, v in pairs(powerups) do
	--	v:OnEnd()
	--end
end

function OnInput(x, y)
	assert(type(x) == "number", "OnInput: Value is not a number")
	assert(type(y) == "number", "OnInput: Value is not a number")
	
	
	if x == -1 then
		player:RotateLeft()
	elseif x == 1 then
		player:RotateRight()
	end

	local vec = vector:New()
	vec.x = x * deltatime * player.speed
	vec.z = y * deltatime * player.speed

	player:Move(vec)
end

-- Update function for lua. return true if nothing happend, false if player died.
function Update(dt)
	deltatime = dt

	-- Loop through all enemies
	for k, v in pairs(monsters) do
		v:Update(player, dt)
	end

	if powerup ~= nil then
		powerup:Update(player, dt)
	end

	if(player:IsAlive() == false) then
		return false
	end

	player:Update()

	return true
end




-- Communication between lua and c++

-- Find the indexed object and return its position
function GetObjectPosition(ind)

	if player.id == ind then
		return player.position.x, player.position.z
	end

	if boss.id == ind then
		return boss.position.x, boss.position.z
	end

	for k, v in pairs(monsters) do
		if v.id == ind then
			return v.position.x, v.position.z
		end
	end

	return 'err', 'err'
end
