local vector = require("script/vector")

local Camera = {}


function Camera:New()
	cam = {}

	cam.position = vector:New()
	cam.target   = vector:New()
	cam.speed	 = 20
	cam.zoomSpeed = 15
	cam.zoomValue = 1
	C_CreateCamera()

	self.__index = self
	setmetatable(cam, self)
	return cam
end

function Camera:SetPosition(x, y, z)
	self.position.x = x
	self.position.y = y
	self.position.z = z
	C_SetCameraPosition(self.position.x, self.position.y, self.position.z)
end

function Camera:SetTarget(x, y, z)
	self.target.x = x
	self.target.y = y
	self.target.z = z
	C_SetCameraTarget(self.target.x, self.target.y, self.target.z)
end

function Camera:SetZoom(zoom)
	if (tonumber(zoom)) then

		-- Zoom only between 1 and 100
		if (zoom >= 1 and zoom <= 100) then
			self.zoomValue = tonumber(zoom)
			C_SetCameraZoom(self.zoomValue)
		end
	end
end

function Camera:Move(vec)
    local pos = self.position + vec
	local tar = self.target + vec
	self:SetPosition(pos.x, pos.y, pos.z)
	self:SetTarget(tar.x, tar.y, tar.z)
end

function Camera:UpdateMovement()	

	-- Movement
	local dir = vector:New()
	local power = 1.0

	if (C_IsKeyDown(keys.SPACE)) then
		power = 5.0
	end

	if C_IsKeyDown(keys.W) then
		dir.z = dir.z + power
	end
	if C_IsKeyDown(keys.S) then
		dir.z = dir.z - power
	end
	if C_IsKeyDown(keys.A) then
		dir.x = dir.x - power
	end
	if C_IsKeyDown(keys.D) then
		dir.x = dir.x + power
	end

	self:Move(dir * self.speed * deltatime)	
end

function Camera:UpdateZoom()
	-- Zooming the camera
	if C_IsKeyDown(keys.PLUS) then
		self:SetZoom(self.zoomValue + (self.zoomSpeed * deltatime))
	
	elseif C_IsKeyDown(keys.MINUS) then
		self:SetZoom(self.zoomValue - (self.zoomSpeed * deltatime))
	end
end

return Camera