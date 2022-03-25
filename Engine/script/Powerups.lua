-- require/include
gameObject = require('script/gameObject')

Powerup = gameObject:New()

function Powerup:New()
	local g = gameObject:New()
	g.type = "Money"

	self.__index = Powerup
	setmetatable(g, self)
	return g
end
