local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local Monster = gameObject:New()

local COOLDOWN_TIME = 5.0


function Monster:New()
	local g = gameObject:New()
	g.hp = 15
	g.worth = 25
	g.xp = 25
	g.damage = 5
	g.speed = math.random(3) + 1
	g.type = "monster"
	g.name = "enemy"
	g.cooldown = 0.0
	g.RandomizePos(g)
	g.gid = C_AddHealthbar(0.0, 0.0, 75.0, 25.0)
	self.__index = Monster
	setmetatable(g, self)

	return g
end

function Monster:OnDeath(playerGold)
	playerGold = playerGold + self.worth
end

function Monster:Chase(point)

	-- Create a new vector.
	local vec = Vector:New()

	-- Manipulate vector so that it follows the player.
	if(self.position.x < point.x) then
		vec.x = 1
	else
		vec.x = -1
	end

	if(self.position.z < point.z) then
		vec.z = 1
	else
		vec.z = -1
	end

	self:Move(vec)
end

function Monster:OnHit(playerHp)
	playerHp = playerHp - self.damage
	return playerHp
end

function Monster:Hit(player)

	self.cooldown = self.cooldown - deltatime

	if C_CheckSpriteCollision(player.id, self.id) and self.cooldown <= 0.0 and self.isVisible == 1 then
		player.hp = player.hp - self.damage
		self.cooldown = COOLDOWN_TIME
	end
end

function Monster:Update(player)
	self:Chase(player.position)
	self:Hit(player)
	self:GUpdate()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 75.0, 25.0)
	C_UpdateUI(self.gid, self.hp)
end

return Monster