player = require('Player')
refMonster = require('Monster')
monsters = {}

function GetPlayerPos()
	return player:getPosition()
end

function addMonster()
	local monster = refMonster:New()
	--print(monster.id)
	table.insert(monsters, monster)

	for k, v in pairs(monsters) do
		--print(v.type)
	end
end

-- Returns all variables from the monsters table, in this case userdata.
--function getMonsters()
	--return table.unpack(monsters)
--end

-- Update function for lua. return 0 if nothing happend, 1 if player died.
function Update()



	if player:getHealth() <= 0 then
		return 1
	end
	return 0
end