local gameObject = require('script/gameObject')

local Monster = gameObject:New()

function Monster:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 5
	g.speed = 0.5
	g.type = "Basic"
	g.randomizePos(g)
	self.__index = Monster
	setmetatable(g, self)

	return g
end

function Monster:OnDeath(playerGold)
	playerGold = playerGold + self.worth
	return playerGold
end

function Monster:OnHit(playerHp)
	playerHp = playerHp - self.damage
	return playerHp
end

return Monster