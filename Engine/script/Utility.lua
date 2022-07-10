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
	RBUTTON = 0x02 
}

weapons = { 
	["default"] = { 
		name = "Sword", sprite = "sword.png", fireRate = 1.2, damage = 5.0, speed = 35, lifetime = 4.0 
	}
}

function tableLength(T)
	local count = 0
	for _ in pairs(T) do 
		count = count + 1
	end
	return count
end
