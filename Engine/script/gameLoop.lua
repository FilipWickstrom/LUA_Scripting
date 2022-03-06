player = require('script/Player')
refMonster = require('script/Monster')

-- Collect all monsters in this table
monsters = {}

-- Collect all other objects such as walls or floors in this table
objects = {}

deltatime = 0

function AddMonster(modelfilepath)
	local monster = refMonster:New()
	monster:LoadModel(modelfilepath)

	table.insert(monsters, monster)
end

-- Returns all variables from the monsters table, in this case userdata.
--function getMonsters()
	--return table.unpack(monsters)
--end

function Start()
	math.randomseed(os.time())
	AddMonster('cube.obj')

	player.position.x = 5
end

function OnInput(x, y)
	assert(type(x) == "number", "OnInput: Value is not a number")
	assert(type(y) == "number", "OnInput: Value is not a number")

	local vec = vector:New()
	vec.x = x * deltatime * player.speed
	vec.y = y * deltatime * player.speed

	if(player:IsAlive()) then
		player:Move(vec)
	end
end

-- Update function for lua. return 0 if nothing happend, 1 if player died.
function Update(dt)
	deltatime = dt
	--print(player.position)

	-- Chase player
	for k, v in pairs(monsters) do
		v:Chase(player.position, dt)
	end


	if(player:IsAlive() == false) then
		return 1
	end

	return 0
end




-- Communication between lua and c++

-- Find the indexed object and return its position
function GetObjectPosition(ind)
	for k, v in pairs(monsters) do
		if v.id == ind then
			return v.position.x, v.position.y
		end
	end

	return 'err', 'err'
end
