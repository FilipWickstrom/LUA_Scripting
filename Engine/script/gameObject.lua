local gameObject = {}
vector = require("script/vector")
require('script/Utility')

function gameObject:RandomizePos()
	self.position.x = math.random(10)
	self.position.y = 0
	self.position.z = math.random(10)
end

function gameObject:New(g)
	g = g or {}
	g.name = "default"
	g.id = -1 --model id? [rename]
	g.gid = -1 --id for ui? [rename]
	
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

function gameObject:OnEnd()
	C_RemoveUI(self.gid)
	print("[LUA]: Removing model: " .. self.id)
	C_RemoveSprite(self.id)
end

function gameObject:GUpdate()
	C_SetSpritePosition(self.id, self.position.x, self.position.z)
end

function gameObject:Move(vec)
	self.position = self.position + (vec * self.speed * deltatime)
end

function gameObject:RotateLeft()
	if self.rotation.z ~= 180 then
		self.rotation.z = 180
		C_SetSpriteRotation(self.rotation.x, self.rotation.y, self.rotation.z)
	end
end

function gameObject:RotateRight()
	if self.rotation.z ~= 0 then
		self.rotation.z = 0
		C_SetSpriteRotation(self.rotation.x, self.rotation.y, self.rotation.z)
	end
end

function gameObject:SetPosition(x, y)
	if type(x) == "number" and type(y) == "number" then
		self.position.x = x
		self.position.y = y
	else
		error("Either both or one of the intakes were not a number!")
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