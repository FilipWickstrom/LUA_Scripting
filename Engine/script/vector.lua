local vector = 
{
	x = 0, y = 0, z = 0
}

function vector:new(origin)

	local vector = origin or { x = 0, y = 0, z = 0 }

	self.__index = self
	setmetatable(vector, self)

	return vector
end

function vector:length()
	return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
end

function vector:__sub(other)
	if(getmetatable(self) ~= vector or getmetatable(other) ~= vector) then
		error("Error: not a vector")
	end

	local rv = vector:new()

	rv.x = self.x - other.x
	rv.y = self.y - other.y
	rv.z = self.z - other.z

	return rv
end

function vector:__add(other)
	if(getmetatable(self) ~= vector or getmetatable(other) ~= vector) then
		error("Error: not a vector")
		return
	end

	local rv = vector:new()

	rv.x = self.x + other.x
	rv.y = self.y + other.y
	rv.z = self.z + other.z

	return rv
end

function vector:__mul(other)
	if(getmetatable(self) == vector and getmetatable(other) == vector) then
		return self.x * other.x + self.y * other.y + self.z * other.z
	elseif(type(other) == "number" and getmetatable(self) == vector) then
		local rv = vector:new()
		rv.x = self.x * other
		rv.y = self.y * other
		rv.z = self.z * other
		return rv
	else
		error("Error: vector multiplication failed")
	end
end

function vector:normalize()
	local length = self.length

	if(length == 0) then
		return
	end

	self.x = self.x / length
	self.y = self.y / length
	self.z = self.z / length
end

function vector:__tostring()
	return "Position: " .. self.x .. " " .. self.y .. " " .. self.z
end

return vector