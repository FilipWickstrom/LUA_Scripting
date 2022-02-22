player = require('Player')
monsters = {}

function addMonster()
	local monster = BasicMonster.new()
	table.insert(monsters, monster)

	--print(#monsters)
end

-- Returns all variables from the monsters table, in this case userdata.
function getMonsters()
	return table.unpack(monsters)
end

-- Update function for lua. return 0 if nothing happend, 1 if player died.
function Update()
	if player:getHealth() <= 0 then
		return 1
	end
	return 0
end