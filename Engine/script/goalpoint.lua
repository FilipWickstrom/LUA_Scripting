local gameObject = require('script/gameObject')

local goalPoint = gameObject:New()

function goalPoint:New()

	local g = gameObject:New()
	g.type = 'goalpoint'
	g.defaultsprite = 'hole.png'

	self.__index = goalPoint
	setmetatable(g, self)

	return g

end

function goalPoint:Update()

	-- Check if player is colliding with this tile, win game.
	if player ~= nil then

		if C_CheckSpriteCollision(self.id, player.id) then

			C_ChangeScene(Scenes.WIN)

		end

	end

end


return goalPoint