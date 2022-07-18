local gameObject = {}
vector = require("script/vector")
require('script/Utility')

function gameObject:New(g)
	g = g or {}
	g.name = "default"
	g.spritename = ""
	g.type = "default"
	g.defaultsprite = ""
	g.id = -1 --model id? [rename]
	g.gid = -1 --id for ui? [rename]
	g.hasCollision = 1
	g.isVisible = 1
	
	--Transform
	g.position = vector:New()
	g.rotation = vector:New()
	g.scale	   = vector:New()
	g.scale = 1,1,1
	g.speed = 0
	
	self.__index = self
	setmetatable(g, self)

	return g
end

function gameObject:LoadSprite(spriteFile)

	self.id = C_LoadSprite(spriteFile)

end

function gameObject:OnEnd()
	C_RemoveUI(self.gid)
	C_RemoveSprite(self.id)
end

function gameObject:RandomizePos()
	self.position.x = math.random(10)
	--self.position.y = 0
	self.position.z = math.random(10)
end

-- Update position to the screen.
function gameObject:GUpdate()
	C_SetSpritePosition(self.id, self.position.x, self.position.y, self.position.z)
end

function gameObject:Move(vec)
	self.position = self.position + (vec * self.speed * deltatime)
	C_SetSpritePosition(self.id, self.position.x, self.position.y, self.position.z)
end

function gameObject:RotateLeft()
	if self.rotation.z ~= 180 then
		self.rotation.z = 180
		C_SetSpriteRotation(self.id, self.rotation.x, self.rotation.y, self.rotation.z)
	end
end

function gameObject:Rotate(vec)
	self.rotation = vec
	C_SetSpriteRotation(self.id, self.rotation.x, self.rotation.y, self.rotation.z)
end

function gameObject:RotateRight()
	if self.rotation.z ~= 0 then
		self.rotation.z = 0
		C_SetSpriteRotation(self.id, self.rotation.x, self.rotation.y, self.rotation.z)
	end
end

-- Set position: use table or x,y,z
function gameObject:SetPosition(pos)
	self.position = pos
	C_SetSpritePosition(self.id, pos.x, pos.y, pos.z)
end
function gameObject:SetPosition(x, y, z)
	self.position.x = x
	self.position.y = y
	self.position.z = z
	C_SetSpritePosition(self.id, x, y, z)
end

function gameObject:SetVisibility(set)

	if set == 0 then
		C_SetSpriteVisible(self.id, false)
		C_SetVisibleUI(self.gid, false)

		self.isVisible = 0
	else
		C_SetSpriteVisible(self.id, true)
		C_SetVisibleUI(self.gid, true)

		self.isVisible = 1
	end
end

function gameObject:SetCollision(set)

	if set == 0 then
		C_SetSpriteCollision(self.id, false)

		self.hasCollision = 0
	else
		C_SetSpriteCollision(self.id, true)

		self.hasCollision = 1
	end

end

function gameObject:GetPosition()
	return self.position.x, self.position.y, self.position.z
end

function gameObject:__tostring()
	return "Position: " .. self.position.x .. " " .. self.position.y .. " " .. self.position.z
end

function gameObject:ChangeSprite(sprite)
	C_ChangeSprite(self.id, sprite)
end

gameObject.__index = gameObject

setmetatable(gameObject, gameObject)

return gameObject