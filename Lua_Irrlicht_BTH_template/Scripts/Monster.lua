local gameObject = require('gameObject')

local Monster = gameObject:New()

function Monster:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 5
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
	print("yo tengo un gato y perro en mi pantaloneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeees amigoooooooooooooooo ppoooooooooorrr favoooooooooorrrrrrrrrrr")
	return playerHp
end

return Monster