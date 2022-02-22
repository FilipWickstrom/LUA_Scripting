local gameObject = require('gameObject')

local BasicBoss = gameObject:New()

function BasicBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 25
	g.speed = 0.5;
	self.__index = BasicBoss
	setmetatable(g, self)
	return g
end

function ChasePoint(x, y)
	if x > self.x then
		self.x += self.speed
	else
		self.x -= self.speed
	end

	if y > self.y then
		self.y += self.speed
	else
		self.y -= self.speed
	end
end
