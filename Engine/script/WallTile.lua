local gameObject = require('script/gameObject')

local WallTile = gameObject:New()

local walltiles = {
	[1] = 'wall_mid.png',
	[2] = 'wall_hole_1.png',
	[3] = 'wall_hole_2.png'
}

function WallTile:New()
	local g = gameObject:New()
	g.hp = 100000000
	g.type = "wall"
	g.defaultsprite = walltiles[math.random(#walltiles)]

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
