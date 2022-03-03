local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local Monster = gameObject:New()

function Monster:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 5
	g.speed = 0.5
	g.type = "Basic"
	g.RandomizePos(g)
	self.__index = Monster
	setmetatable(g, self)

	return g
end

function Monster:OnDeath(playerGold)
	playerGold = playerGold + self.worth
	return playerGold
end

function Monster:Chase(point, dt)

	-- Create a new vector.
	local vec = Vector:New()

	-- Manipulate vector so that it follows the player.
	if(self.position.x < point.x) then
		vec.x = 1 * dt
	else
		vec.x = -1 * dt
	end

	if(self.position.y < point.y) then
		vec.y = 1 * dt
	else
		vec.y = -1 * dt
	end

	-- Add vector to monster
	self.position = self.position + vec
		
end

function Monster:OnHit(playerHp)
	playerHp = playerHp - self.damage
	return playerHp
end

return Monster