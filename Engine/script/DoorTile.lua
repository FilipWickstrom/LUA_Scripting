local gameObject = require('script/gameObject')

local DoorTile = gameObject:New()

function DoorTile:New()
	local g = gameObject:New()
	g.hp = 10000000000
	g.type = "door"
	g.defaultsprite = 'doors_leaf_closed.png'
	g.key = gameObject:New()
	g.key.id = C_LoadSprite('key.png')
	--C_SetSpriteVisible(g.key.id, false)

	-- test position
	g.key:SetPosition(35,0.1,0)

	self.__index = DoorTile
	setmetatable(g, self)

	return g

end

function DoorTile:OnEnd()
	C_RemoveSprite(self.id)
	C_RemoveSprite(self.key.id)
end

function DoorTile:SetPosition(x, y, z)

	self.key:SetPosition(x, y, z + 32.0)
	self.position.x = x
	self.position.y = y + 1
	self.position.z = z
	C_SetSpritePosition(self.id, self.position.x, self.position.y, self.position.z)
end

--[[ Check if player collides with the key, if so, 
	 set itself and the key to invisible, or remove itself.
]]
function DoorTile:Update()

	if C_CheckSpriteCollision(player.id, self.key.id) then
		C_SetSpriteVisible(self.key.id, false)
		C_SetSpriteVisible(self.id, false)
		C_RemoveSprite(self.id)
		C_RemoveSprite(self.key.id)
	end

end

return DoorTile
