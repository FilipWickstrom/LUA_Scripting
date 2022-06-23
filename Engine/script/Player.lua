-- require/include
gameObject = require('script/gameObject')

Player = gameObject:New()

function Player:New()
	local g = gameObject:New()
	
	g.hp = 100.0
	g.gold = 0
	g.xp = 0
	g.weapon = "Hands"
	g.name = "Player"
	g.damage = 5
	g.speed = 12
	-- Add effects here.
	g.position.x = 0
	g.position.y = 0
	g.lastpickup = "None"

	g.id = C_LoadSprite('knight.png')
	g.gid = C_AddHealthbar(0.0, 0.0, 250.0, 50.0)

	self.__index = Player
	setmetatable(g, self)
	return g
end

function Player:Update()
	self:GUpdate()

	if self.hp > 100.0 then
		self.hp = 100.0
	end

	-- GOD MODE!!
	--self.hp = 100
	C_UpdateUI(self.gid, self.hp)

end

function Player:IsAlive()
	if(self.hp > 0) then
		return true
	end

	return false
end

function Player:TakeDamage(hurt)
	if type(hurt) == "number" then
		self.hp = self.hp - hurt
		--print(self.hp)
	else
		error("Input value was not a number!")
	end
end

function Player:ReceiveHealth(health)
	if type(health) == "number" then
		self.hp = self.hp + health
		print(self.hp)
	else
		error("Input value was not a number!")
	end
end

function Player:ReceiveGold(wealth)
	if type(wealth) == "number" then
		self.gold = self.gold + wealth
		print(self.gold)
	else
		error("Input value was not a number!")
	end
end

function Player:ReceiveExperience(xp)
	if type(xp) == "number" then
		self.xp = self.xp + xp
		print(self.xp)
	else
		error("Input value was not a number!")
	end
end

function Player:GetWeapon()
	print("Weapon is" .. " " .. self.weapon .. ".")
	return self.weapon
end

return (Player)