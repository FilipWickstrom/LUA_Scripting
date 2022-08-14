local gameObject = require('script/gameObject')

local spawnPoint = gameObject:New()

function spawnPoint:New()

	local g = gameObject:New()
	g.type = 'spawnpoint'
	g.defaultsprite = 'wall_banner_yellow.png'
	g.image2d = -1

	self.__index = spawnPoint
	setmetatable(g, self)

	return g

end

function spawnPoint:AddIcon()
	self.image2d = C_AddImage2d('knight.png')
	C_SetImage2dPosition(self.image2d, 0, 0)
	C_SetImage2dScale(self.image2d, 3)
end

function spawnPoint:Update()
	if (self.image2d ~= -1) then

		local window = { X = C_WinWidth(), Y = C_WinHeight() }

		local x, y = C_ObjectToScreen(self.id)
		if x < 0 then
			x = 0
		elseif x > window.X then
			x = window.X - 15
		end
	
		if y < 0 then
			y = 0
		elseif y > window.Y then
			y = window.Y - 20
		end

		C_SetImage2dPosition(self.image2d, x, y)
	end
end

function spawnPoint:OnEnd()
	if (self.id ~= -1) then
		C_RemoveSprite(self.id)
	end
	if (self.gid ~= -1) then
		C_RemoveUI(self.gid)
	end
	if (self.image2d) then
		C_RemoveImage2d(self.image2d)
	end
end

return spawnPoint