local gameObject = require('script/gameObject')

local WallTile = gameObject:New()

function WallTile:New()
	local g = gameObject:New()
	g.hp = 100000000
	g.type = "wall"

	self.__index = WallTile
	setmetatable(g, self)

	return g

end

function WallTile:OnEnd()
	C_RemoveSprite(self.id)
end

function WallTile:Update(player)

end

return WallTile
