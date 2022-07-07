-- require/include
require('script/vector')
gameObject = require('script/gameObject')
Player = gameObject:New()
require('script/Weapon')

function Player:New()
	local g = gameObject:New()
	
	g.hp = 100.0
	g.gold = 0
	g.xp = 0
	g.weapon = Weapon.new("default")
	g.name = "Player"
	g.speed = 12
	g.position = vector:New()
	-- Add effects here.
	g.lastpickup = "None"

	g.id = C_LoadSprite('knight.png')
	g.gid = C_AddHealthbar(0.0, 0.0, 250.0, 50.0)
	g:GUpdate()

	self.__index = Player
	setmetatable(g, self)
	return g
end

function Player:HandleMovement(camera)
	local x = 0
	local y = 0

	if C_IsKeyDown(keys.W) then
		y = 1
	end
	if C_IsKeyDown(keys.S) then
		y = -1
	end
	if C_IsKeyDown(keys.A) then
		x = -1
		self:RotateLeft()
	end
	if C_IsKeyDown(keys.D) then
		x = 1
		self:RotateRight()
	end
	
	local dir = vector:New()
	dir.x = x
	dir.z = y

	self:Move(dir)
	camera:Move(dir * self.speed * deltatime)
end

function Player:Shoot()
	if C_IsKeyDown(keys.LBUTTON) then
		self.weapon:Fire(self.position)
	end
end

function Player:Update(camera, enemies)
	self:GUpdate()
	self:HandleMovement(camera)
	self:Shoot()
	self.weapon:Update(enemies)

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

	self:OnEnd()

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
	print("Weapon is" .. " " .. self.weapon.type .. ".")
	return self.weapon
end

return (Player)