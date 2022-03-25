local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local BasicBoss = gameObject:New()

local COOLDOWN_TIME = 3.0

function BasicBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 25
	g.speed = 5
	g.type = "Boss"
	g.direction = {x = 1, z = 1}
	g.position.x = 10
	g.cooldown = 0
	g.reach = 3.5

	g.id = LoadModel('clue_toy.obj')

	self.__index = BasicBoss
	setmetatable(g, self)
	return g
end

function BasicBoss:Chase(dt)
	
	if self.position.x > 18 or self.position.x < -22 then
		self.direction.x = -self.direction.x
	end
	
	if self.position.z > 11 or self.position.z < -11 then
		self.direction.z = -self.direction.z
	end
	
	self.position.x = self.position.x + self.direction.x * dt * self.speed
	self.position.z = self.position.z + self.direction.z * dt * self.speed
	
end

function BasicBoss:Attack(player, dt)

	local x = math.abs(player.position.x - self.position.x)
	local z = math.abs(player.position.z - self.position.z)

	self.cooldown = self.cooldown - dt

	if x < self.reach and z < self.reach and self.cooldown <= 0.0 then
		player.hp = player.hp - self.damage
		self.cooldown = COOLDOWN_TIME
		print('Hit!')
	end

end

function BasicBoss:Update(player, dt)
	self:Chase(dt)
	self:Attack(player, dt)
	self:GUpdate()
end


return BasicBoss