local gameObject = require('script/gameObject')

local spawnPoint = gameObject:New()

function spawnPoint:New()

	local g = gameObject:New()
	g.type = 'spawnpoint'
	g.defaultsprite = 'column_top.png'

	self.__index = spawnPoint
	setmetatable(g, self)

	return g

end

function spawnPoint:Update()

end


return spawnPoint