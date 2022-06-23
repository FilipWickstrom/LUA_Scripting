local vector = require("script/vector")

local Camera = {}


function Camera:New()
	local cam = {}
	self.__index = self
	setmetatable(cam,self)

	cam.position = vector:New()
	cam.target   = vector:New()
	C_CreateCamera()

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

function Camera:SetFOV(fov)
	C_SetCameraFOV(fov)
end

function Camera:Move(vec)
    local pos = self.position + vec
	local tar = self.target + vec
	self:SetPosition(pos.x, pos.y, pos.z)
	self:SetTarget(tar.x, tar.y, tar.z)
end


return Camera