local gameObject = {}
vector = require("script/vector")

function gameObject:RandomizePos()
	self.position.x = math.random(10)
	self.position.y = 0
	self.position.z = math.random(10)
end

function gameObject:New(g)
	g = g or {}
	g.id = 0
	g.gid = 0
	g.position = vector:New()
	self.__index = self
	setmetatable(g, self)

	return g
end

function gameObject:OnEnd()
	RemoveUI(self.gid)
	RemoveModel(self.id)
end

function gameObject:GUpdate()
	UpdatePos(self.id, self.position.x, self.position.z)
end

function gameObject:Move(vec)
	self.position = self.position + vec
	--print(self.position)
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

gameObject.__index = gameObject

setmetatable(gameObject, gameObject)

return gameObject