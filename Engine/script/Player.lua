-- require/include
gameObject = require('script/gameObject')

PlayerTable = {hp = 100, gold = 0, xp = 0, weapon = "Hands", damage = 5, speed = 12}
Player = gameObject:New(PlayerTable)

function PlayerTable:New(g)
	g = g or {}
	setmetatable(g, self)
	self.__index = self

	-- Add effects here.
	g.position.x = 0
	g.position.y = 0

	return self
end

function PlayerTable:takeDamage(hurt)
	if type(hurt) == "number" then
		self.hp = self.hp - hurt
		--print(self.hp)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:getHealth()
	return self.hp
end

function PlayerTable:recieveHealth(health)
	if type(health) == "number" then
		self.hp = self.hp + health
		print(self.hp)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:recieveGold(wealth)
	if type(wealth) == "number" then
		self.gold = self.gold + wealth
		print(self.gold)
	else
		error("Input value was not a number!")
	end
end

function PlayerTable:getWeapon()
	print("Weapon is" .. " " .. self.weapon .. ".")
	return self.weapon
end

function PlayerTable:move(x, y)
	assert(type(x) == "number", "Invalid input, requires numbers")
	assert(type(y) == "number", "Invalid input, requires numbers")

	self:newPosition(x * self.speed, y * self.speed)
end

return (Player)