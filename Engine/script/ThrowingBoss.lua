local gameObject = require('script/gameObject')
local Vector = require('script/vector')
require('script/Weapon')

local ThrowBoss = gameObject:New()

local COOLDOWN = 1.5

function ThrowBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 30
	g.xp = 25
	g.damage = 5
	g.speed = 25
	g.type = "shooter"
	g.name = "enemy"
	g.defaultsprite = 'zombie_big.png'

	g.direction = Vector:New()
	g.direction.x = 1
	g.gid = C_AddHealthbar(0.0, 0.0, 145.0, 50.0, g.hp)

	--g.id = C_LoadSprite('ogre.png')
	g.weapon = Weapon.new("default")
	g.weapon.fireRate = 1.2
	g.projectile = gameObject:New()

	self.__index = ThrowBoss
	setmetatable(g, self)

	return g
end

function ThrowBoss:OnDeath()	
	if (math.random(100) <= bossWeaponDropChance) then
		weaponDrops:CreateWeapon(self.position)
	end

	self.projectile:OnEnd()
	self:OnEnd()
end

function ThrowBoss:Throw()
	local dir = player.position - self.position
	dir:Normalize()
	self.weapon:Fire(self.position, dir, self.id)
	self.weapon:Update()
end

function ThrowBoss:Chase()

	-- Go through all the wall tiles
	for i = 1, #walls do

		-- Not the best collision :(
		if C_CheckSpriteCollision(self.id, walls[i].id) then
			self.direction.x = self.direction.x * -1
			self.direction.z = self.direction.z * -1
			break
		end
	end

	self:Move(self.direction)
	
end

function ThrowBoss:Update()
	self:Throw()
	self:Chase()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 145.0, 50.0)
	C_UpdateUI(self.gid, self.hp)
end

return ThrowBoss