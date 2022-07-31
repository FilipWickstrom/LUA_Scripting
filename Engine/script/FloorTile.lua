local gameObject = require('script/gameObject')

local FloorTile = gameObject:New()

local floors = {
	[1] = 'floor_1.png',
	[2] = 'floor_2.png',
	[3] = 'floor_3.png',
	[4] = 'floor_4.png',
	[5] = 'floor_5.png',
	[6] = 'floor_6.png',
	[7] = 'floor_7.png',
	[8] = 'floor_8.png'
}

function FloorTile:New()
	local g = gameObject:New()
	g.hp = 100000000
	g.type = "floor"
	g.defaultsprite = floors[math.random(#floors)]

	self.__index = FloorTile
	setmetatable(g, self)

	return g

end

function FloorTile:OnEnd()
	C_RemoveSprite(self.id)
end

function FloorTile:RandomSprite()
	self.defaultsprite = floors[math.random(#floors)]
end

function FloorTile:Update(player)

end

return FloorTile