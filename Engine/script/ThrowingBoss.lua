local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local ThrowBoss = gameObject:New()

local COOLDOWN = 1.5

function ThrowBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 5
	g.speed = math.random(5) + 1
	g.type = "Basic"
	g.inhand = true
	g.cooldown = 1
	g.RandomizePos(g)
	g.direction = {x = 1, y = 1}
	g.gid = AddHealthbar(0.0, 0.0, 145.0, 50.0)

	g.id = LoadModel('cube.obj')

	g.projectile = gameObject:New()

	g.projectile.id = LoadModel('clue_mask.obj')
	g.projectile.position.x = 1000
	g.projectile.target = Vector:New()
	g.projectile.speed = 2

	self.__index = ThrowBoss
	setmetatable(g, self)

	return g
end

function ThrowBoss:Throw(point)
	-- if in hand then throw the projectile
	if self.inhand == true and self.cooldown > 0 then
		self.inhand = false

		-- player position as target
		self.projectile.target.x = point.x
		self.projectile.target.z = point.z

		-- set start position at enemy position
		self.projectile.position.x = self.position.x
		self.projectile.position.z = self.position.z
	end
end

function ThrowBoss:UpdateThrow(dt)
	-- update only when thrown
	if self.inhand == false then

		local x = math.abs(self.projectile.position.x - self.projectile.target.x)
		local y = math.abs(self.projectile.position.z - self.projectile.target.z)

		if self.projectile.position.x > self.projectile.target.x then
			self.projectile.position.x = self.projectile.position.x - x * dt * self.projectile.speed
		else
			self.projectile.position.x = self.projectile.position.x + x * dt * self.projectile.speed
		end

		if self.projectile.position.z > self.projectile.target.z then
			self.projectile.position.z = self.projectile.position.z - y * dt * self.projectile.speed
		else
			self.projectile.position.z = self.projectile.position.z + y * dt * self.projectile.speed
		end

		self.cooldown = self.cooldown - dt

		if x < 1.5 and y < 1.5 and self.cooldown < 0 then
			-- hide the projectile from the screen
			self.projectile.position.y = 10000000
			self.projectile.position.x = 10000000
			self.inhand = true
			self.cooldown = COOLDOWN
		end

	end
end

function ThrowBoss:Chase(dt)
	
	if self.position.x > 18 or self.position.x < -22 then
		self.direction.x = -self.direction.x
	end
	
	if self.position.y > 11 or self.position.y < -11 then
		self.direction.y = -self.direction.y
	end
	
	self.position.x = self.position.x + self.direction.x * dt * self.speed
	self.position.y = self.position.y + self.direction.y * dt * self.speed
	
end

function ThrowBoss:Update(player, dt)
	
	self:Throw(player.position)
	self:UpdateThrow(dt)

	self:Chase(dt)
	self:GUpdate()
	self.projectile:GUpdate()
	UpdateUI(self.gid, self.hp)
	UpdatePosUI(self.gid, self.position.x, self.position.z, 145.0, 50.0)
end

return ThrowBoss