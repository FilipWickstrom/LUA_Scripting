local gameObject = require('script/gameObject')

local WallTile = gameObject:New()

function WallTile:New()
	local g = gameObject:New()
	g.hp = 100
	g.type = "wall"

	self.__index = WallTile
	setmetatable(g, self)

	return g

end

function WallTile:Update(player)

end

return WallTile
