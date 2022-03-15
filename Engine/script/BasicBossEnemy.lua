local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local BasicBoss = gameObject:New()

function BasicBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 25
	g.speed = 5
	g.type = "Boss"
	g.direction = {x = 1, y = 1}
	g.position.x = 10

	g.id = LoadModel('clue_toy.obj')

	self.__index = BasicBoss
	setmetatable(g, self)
	return g
end

function BasicBoss:Chase(dt)
	

	if self.position.x > 18 or self.position.x < -22 then
		self.direction.x = -self.direction.x
	end
	
	if self.position.y > 11 or self.position.y < -11 then
		self.direction.y = -self.direction.y
	end
	
	self.position.x = self.position.x + self.direction.x * dt * self.speed
	self.position.y = self.position.y + self.direction.y * dt * self.speed
	
end

return BasicBoss