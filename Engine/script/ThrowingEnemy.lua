local gameObject = require('script/gameObject')
local Vector = require('script/vector')

local ThrowMonkey = gameObject:New()

function ThrowMonkey:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 50
	g.xp = 25
	g.damage = 5
	g.speed = math.random(3) + 1
	g.type = "Basic"
	g.reach = 2
	g.cooldown = 0.0
	g.RandomizePos(g)
	self.__index = ThrowMonkey
	setmetatable(g, self)

	g:LoadGModel('cube.obj')

	g.projectile = gameObject:New()

	g.projectile:LoadGModel('clue_mask.obj')
	g.projectile.position.x = 1000

	return g
end


return ThrowMonkey