local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local BasicBoss = gameObject:New()
local COOLDOWN_TIME = 3.0

function BasicBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 30
	g.xp = 25
	g.damage = 25
	g.speed = 5
	g.type = "bouncy"
	g.name = "enemy"
	g.direction = Vector:New()
	g.direction.x = 0.5
	g.direction.z = 1
	g.cooldown = 0

	g.gid = C_AddHealthbar(0.0, 0.0, 100.0, 50.0)

	self.__index = BasicBoss
	setmetatable(g, self)
	return g
end

function BasicBoss:OnDeath(playerGold)
	playerGold = playerGold + self.worth
end

function BasicBoss:Chase()

	-- Go through all the wall tiles
	for num, obj in pairs(walls) do

		-- Not the best collision :(
		if C_CheckSpriteCollision(self.id, obj.id) then
			self.direction.x = self.direction.x * -1
			self.direction.z = self.direction.z * -1
		end
			
		--[[
		-- Not working correctly either...
		-- Checking horizontal direction
		if (C_CheckSpriteCollision(self.id, obj.id, "horizontal")) then
			self.direction.x = self.direction.x * -1
		end

		-- Checking vertical direction
		if (C_CheckSpriteCollision(self.id, obj.id, "vertical")) then
			self.direction.z = self.direction.z * -1
		end
		]]--

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
	self:GUpdate()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 100.0, 50.0)
	C_UpdateUI(self.gid, self.hp)
end


return BasicBoss