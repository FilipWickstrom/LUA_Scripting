local gameObject = {}

function gameObject:randomizePos()
	self.position.x = math.random(600) - math.random(600)
	self.position.y = math.random(600) - math.random(600)
end

function gameObject:New(g)
	g = g or {}
	g.position = {x = 0, y = 0}
	self.__index = self
	setmetatable(g, self)

	-- Add effects here.
	g:randomizePos()

	return g
end

function gameObject:distance(other)
	if type(other) == "table" then
		local x = other.position.x - self.position.x
		local y = other.position.y - self.position.y
		return math.sqrt(math.pow(x, 2) + math.pow(y, 2))
	end
end

function gameObject:newPosition(x, y)
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

function gameObject:__tostring()
	return self.position.x .. " " .. self.position.y
end

function gameObject:getPosition()
	return self.position.x, self.position.y
end

gameObject.__index = gameObject

setmetatable(gameObject, gameObject)

return gameObject