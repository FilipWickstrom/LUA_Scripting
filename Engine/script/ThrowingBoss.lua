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
	g.type = "shooter"
	g.name = "enemy"

	g.direction = Vector:New()
	g.gid = C_AddHealthbar(0.0, 0.0, 145.0, 50.0, g.hp)

	--g.id = C_LoadSprite('ogre.png')
	g.weapon = Weapon.new("default")
	g.weapon.fireRate = 1.2
	g.projectile = gameObject:New()

	--g.projectile.id = C_LoadSprite('sword_huge.png')
	--g.projectile.position = Vector:New()
	--g.projectile.target = Vector:New()
	--g.projectile.speed = 20
	--C_SetSpriteVisible(g.projectile.id, false)

	self.__index = ThrowBoss
	setmetatable(g, self)

	return g
end

function ThrowBoss:OnDeath()	
	if random(100) < bossWeaponDropChance then
		weaponDrops:CreateWeapon(self.position)
	end

	self.projectile:OnEnd()
	self:OnEnd()
end

function ThrowBoss:Throw()
	local dir = player.position - self.position
	dir:Normalize()
	self.weapon:Fire(self.position, dir)
	self.weapon:Update(enemies)
end

function ThrowBoss:Chase()

	-- loop through all objects, any collision?
	for num, obj in pairs(objects) do

		if C_CheckSpriteCollision(self.id, obj.id) and self.id ~= obj.id then
			if self.position.x < obj.position.x then
				self.direction.x = -1 
			else
				self.direction.x = 1
			end

			if self.position.z > obj.position.z then
				self.direction.z = -1
			else
				self.direction.z = 1
			end

		end

	end

	self:Move(self.direction)
	
end

function ThrowBoss:Update()
	self:Throw()
	self:Chase()
	self:GUpdate()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 145.0, 50.0)
	C_UpdateUI(self.gid, self.hp)
end

return ThrowBoss