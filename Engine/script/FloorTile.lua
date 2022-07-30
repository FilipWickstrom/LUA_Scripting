local gameObject = require('script/gameObject')

local FloorTile = gameObject:New()

function FloorTile:New()
	local g = gameObject:New()
	g.hp = 100000000
	g.type = "floor"
	g.defaultsprite = 'floor_1.png'

	self.__index = FloorTile
	setmetatable(g, self)

	return g

end

function FloorTile:OnEnd()
	C_RemoveSprite(self.id)
end

function FloorTile:Update(player)

end

return FloorTile