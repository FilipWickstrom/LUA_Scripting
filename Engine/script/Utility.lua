deltatime = 0.0
mousePos = { x = 0.0, y = 0.0 }

keys = { 
	W = 0x57, 
	A = 0x41, 
	D = 0x44, 
	S = 0x53, 
	SPACE = 0x20, 
	ESCAPE = 0x1B,		
	LBUTTON = 0x01, 
	RBUTTON = 0x02,
	PLUS = 0xBB,
	MINUS = 0xBD
}

weapons = { 
	["default"] = { 
		name = "Sword", sprite = "sword.png", fireRate = 1.1, damage = 6.0, speed = 35, lifetime = 3.0 
	},
	["Heart"] = {
		name = "Heart Magic", sprite = "ui_heart_full.png", fireRate = 0.9, damage = 10.0, speed = 55, lifetime = 3.5 
	},
	["Bomb"] = {
		name = "Bombs", sprite = "bomb.png", fireRate = 1.8, damage = 15.0, speed = 12.25, lifetime = 6.0 
	},
	["Arrow"] = {
		name = "Arrows", sprite = "arrow.png", fireRate = 0.75, damage = 4.5, speed = 60, lifetime = 4.0 
	}
}

bossWeaponDropChance = 101

-- Why not use "#table"?
function tableLength(T)
	local count = 0
	for _ in pairs(T) do 
		count = count + 1
	end
	return count
end

-- randomize a number with a upper limit defined.
function random(limit)

	if limit == nil then
		limit = 100
	end

	return math.random(limit)

end