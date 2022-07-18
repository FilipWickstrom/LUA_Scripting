local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local BasicBoss = gameObject:New()
local COOLDOWN_TIME = 3.0

function BasicBoss:New()
	local g = gameObject:New()
	g.hp = 150
	g.worth = 30
	g.xp = 25
	g.damage = 25
	g.speed = 5
	g.type = "bouncy"
	g.name = "enemy"
	g.defaultsprite = 'ogre.png'
	g.direction = Vector:New()
	g.direction.x = 0.5
	g.direction.z = 1
	g.cooldown = 0

	g.gid = C_AddHealthbar(0.0, 0.0, 100.0, 50.0, g.hp)

	self.__index = BasicBoss
	setmetatable(g, self)
	return g
end

function BasicBoss:OnDeath()

	if random(100) < bossWeaponDropChance then
		weaponDrops:CreateWeapon(self.position)
	end

	self:OnEnd()
end

function BasicBoss:Chase()

	--[[
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
	]]

	-- temporary bounce that works better than the one above.

	-- loop through all objects, any collision?
	for num, obj in pairs(objects) do

		if C_CheckSpriteCollision(self.id, obj.id) and self.id ~= obj.id then
			if self.position.x < obj.position.x then
				self.direction.x = -1 
			else
				self.direction.x = 1
			end

			if self.position.z < obj.position.z then
				self.direction.z = -1
			else
				self.direction.z = 1
			end

		end

	end

	self:Move(self.direction)
end

function BasicBoss:Attack()

	self.cooldown = self.cooldown - deltatime

	if C_CheckSpriteCollision(player.id, self.id) and self.cooldown <= 0.0 then
		player.hp = player.hp - self.damage
		self.cooldown = COOLDOWN_TIME
	end

end

function BasicBoss:Update()
	self:Chase()
	self:Attack()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 100.0, 50.0)
	C_UpdateUI(self.gid, self.hp)
end


return BasicBoss