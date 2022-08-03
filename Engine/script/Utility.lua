deltatime = 0.0
mousePos = { x = 0.0, y = 0.0 }
bossWeaponDropChance = 100

keys = { 
	W = 0x57, 
	A = 0x41, 
	D = 0x44, 
	S = 0x53, 
	SPACE = 0x20, 
	ESCAPE = 0x1B,	
	LSHIFT = 0xA0,
	RSHIFT = 0xA1,
	LBUTTON = 0x01, 
	RBUTTON = 0x02,
	PLUS = 0xBB,
	MINUS = 0xBD,
	ONE = 0x31,
	TWO = 0x32,
	THREE = 0x33,
	FOUR = 0x34,
	FIVE = 0x35,
	SIX = 0x36,
	SEVEN = 0x37,
	EIGHT = 0x38,
	NINE = 0x39,
	ZERO = 0x30
}

weapons = { 
	["default"] = { 
		name = "Sword", 
		sprite = "sword.png", 
		fireRate = 1.1, 
		damage = 6.0, 
		speed = 45, 
		lifetime = 3.0 
	},
	["Heart"] = {
		name = "Heart Magic", 
		sprite = "ui_heart_full.png", 
		fireRate = 0.9, 
		damage = 25.0, 
		speed = 55, 
		lifetime = 3.5 
	},
	["Bomb"] = {
		name = "Bombs", 
		sprite = "bomb.png", 
		fireRate = 1.8, 
		damage = 15.0, 
		speed = 30, 
		lifetime = 6.0 
	},
	["Arrow"] = {
		name = "Arrows", 
		sprite = "arrow.png", 
		fireRate = 0.75, 
		damage = 4.5, 
		speed = 75, 
		lifetime = 4.0 
	}
}


-- Check the length of a map
function MapLength(map)
	local count = 0
	for _ in pairs(map) do 
		count = count + 1
	end
	return count
end

-- Shallow copy all the values from one table to another
function MapShallowCopy(map)
	local copy = {}
	for k,v in pairs(map) do
		copy[k] = v
	end
	return copy
end

-- Check if 2 maps have the same keys
function HasSameKeys(m1, m2)
	local m1size = MapLength(m1)
	local m2size = MapLength(m2)

	-- One of the tables is empty, not worth testing more
	if (m1size == 0 or m2size == 0) then
		return false
	end

	-- Maps can't be the same, different sizes
	if (m1size ~= m2size) then
		return false
	else
		-- Go through all the values
		for i, v in pairs(m1) do
			-- Some of the tiles are different
			if (m2[i] == nil) then
				return false
			end
		end	
	end

	-- The map are the same
	return true
end
