local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local ThrowBoss = gameObject:New()

local COOLDOWN = 1.5

function ThrowBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 30
	g.xp = 25
	g.damage = 5
	g.speed = math.random(5) + 1
	g.type = "shooty"
	g.name = "enemy"
	g.inhand = true
	g.cooldown = 1
	g.RandomizePos(g)
	g.direction = {x = 1, y = 1}
	g.gid = C_AddHealthbar(0.0, 0.0, 145.0, 50.0)

	g.id = C_LoadSprite('ogre.png')

	g.projectile = gameObject:New()

	g.projectile.id = C_LoadSprite('sword_huge.png')
	g.projectile.position = Vector:New()
	g.projectile.target = Vector:New()
	g.projectile.speed = 2
	C_SetSpriteVisible(g.projectile.id, false)

	self.__index = ThrowBoss
	setmetatable(g, self)

	return g
end

function ThrowBoss:OnDeath(playerGold)
	playerGold = playerGold + self.worth
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

		C_SetSpriteVisible(g.projectile.id, true)
	end
end

function ThrowBoss:UpdateThrow()
	-- update only when thrown
	if self.inhand == false then

		local x = math.abs(self.projectile.position.x - self.projectile.target.x)
		local y = math.abs(self.projectile.position.z - self.projectile.target.z)

		if self.projectile.position.x > self.projectile.target.x then
			self.projectile.position.x = self.projectile.position.x - x * deltatime * self.projectile.speed
		else
			self.projectile.position.x = self.projectile.position.x + x * deltatime * self.projectile.speed
		end

		if self.projectile.position.z > self.projectile.target.z then
			self.projectile.position.z = self.projectile.position.z - y * deltatime * self.projectile.speed
		else
			self.projectile.position.z = self.projectile.position.z + y * deltatime * self.projectile.speed
		end

		self.cooldown = self.cooldown - deltatime

		if x < 1.5 and y < 1.5 and self.cooldown < 0 then
			-- hide the projectile from the screen
			C_SetSpriteVisible(self.projectile.id, false)
			self.inhand = true
			self.cooldown = COOLDOWN
		end

	end
end

function ThrowBoss:Chase()
	local vec = vector:New()
	if self.position.x > 18 or self.position.x < -22 then
		self.direction.x = self.direction.x * -1
	end
	
	if self.position.z > 11 or self.position.z < -11 then
		self.direction.y = self.direction.y * -1
	end

	vec.x = self.direction.x;
	vec.z = self.direction.y
	
	self:Move(vec)
	
end

function ThrowBoss:Update(player)
	
	self:Throw(player.position)
	self:UpdateThrow()

	self:Chase()
	self:GUpdate()
	self.projectile:GUpdate()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 145.0, 50.0)
	C_UpdateUI(self.gid, self.hp)
end

return ThrowBoss