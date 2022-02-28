local gameObject = {}
vector = require("script/vector")

function gameObject:randomizePos()
	self.position.x = math.random(600) - math.random(600)
	self.position.y = math.random(600) - math.random(600)
end

function gameObject:New(g)
	g = g or {}
	g.id = 0
	g.position = vector:new()
	self.__index = self
	setmetatable(g, self)

	-- Add effects here.
	--g:randomizePos()

	return g
end

function gameObject:move(x, y)
	if type(x) == "number" and type(y) == "number" then
		self.position.x = self.position.x + x
		self.position.y = self.position.y + y
		--print("x:" .." ".. self.position.x .. " y: " .. self.position.y)
	else
		error("Either both or one of the intakes were not a number!")
	end
end

function gameObject:setPosition(x, y)
	if type(x) == "number" and type(y) == "number" then
		self.position.x = x
		self.position.y = y
	else
		error("Either both or one of the intakes were not a number!")
	end
end

function gameObject:getPosition()
	return self.position.x, self.position.y
end

gameObject.__index = gameObject

setmetatable(gameObject, gameObject)

return gameObject