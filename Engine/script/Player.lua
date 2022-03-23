-- require/include
gameObject = require('script/gameObject')

PlayerTable = {hp = 10000, gold = 0, xp = 0, weapon = "Hands", damage = 5, speed = 12}
Player = gameObject:New(PlayerTable)

function PlayerTable:New(g)
	g = g or {}
	setmetatable(g, self)
	self.__index = self

	-- Add effects here.
	g.position.x = 0
	g.position.y = 0

	g.id = LoadModel('clue_mask.obj')

	return self
end

function PlayerTable:Update()
	self:GUpdate()
	--print('x: ' .. self.position.x .. 'y: ' .. self.position.y)
end

function PlayerTable:IsAlive()
	if(self.hp > 0) then
		return true
	end

	return false
end

function PlayerTable:TakeDamage(hurt)
	if type(hurt) == "number" then
		self.hp = self.hp - hurt
		--print(self.hp)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:ReceiveHealth(health)
	if type(health) == "number" then
		self.hp = self.hp + health
		print(self.hp)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:ReceiveGold(wealth)
	if type(wealth) == "number" then
		self.gold = self.gold + wealth
		print(self.gold)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:ReceiveExperience(xp)
	if type(xp) == "number" then
		self.xp = self.xp + xp
		print(self.xp)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:GetWeapon()
	print("Weapon is" .. " " .. self.weapon .. ".")
	return self.weapon
end

return (Player)