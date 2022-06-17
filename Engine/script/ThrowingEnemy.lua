local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local ThrowMonkey = gameObject:New()

local COOLDOWN = 1.5

function ThrowMonkey:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 5
	g.speed = math.random(3) + 1
	g.type = "Basic"
	g.inhand = true
	g.cooldown = 1
	g.RandomizePos(g)
	self.__index = ThrowMonkey
	setmetatable(g, self)

	g.id = C_LoadSprite('necromancer.png')
	g.gid = C_AddHealthbar(0.0, 0.0, 75.0, 25.0)

	g.projectile = gameObject:New()

	g.projectile.id = C_LoadSprite('sword.png')
	g.projectile.position.x = 1000
	g.projectile.target = Vector:New()
	g.projectile.speed = 2
	--C_SetSpriteScale(g.projectile.id, 0.1)

	return g
end

function ThrowMonkey:Throw(point)
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

function ThrowMonkey:UpdateThrow(dt)
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
			self.projectile.position.z = 10000000
			self.projectile.position.x = 10000000
			self.inhand = true
			self.cooldown = COOLDOWN
		end

	end
end

function ThrowMonkey:Update(player, dt)
	self:Throw(player.position)
	self:UpdateThrow(dt)
	self:GUpdate()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 75.0, 25.0)
	C_UpdateUI(self.gid, self.hp)
	self.projectile:GUpdate()
end


return ThrowMonkey