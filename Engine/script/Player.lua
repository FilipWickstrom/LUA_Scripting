-- Includes
--require('script/vector')
require('script/Weapon')
local gameObject = require('script/gameObject')


Player = gameObject:New()

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
	local dir = vector:New()

	if C_IsKeyDown(keys.W) then
		dir.z = dir.z + 1
	end
	if C_IsKeyDown(keys.S) then
		dir.z = dir.z - 1
	end
	if C_IsKeyDown(keys.A) then
		dir.x = dir.x - 1
		self:RotateLeft()
	end
	if C_IsKeyDown(keys.D) then
		dir.x = dir.x + 1
		self:RotateRight()
	end

	-- Move everything
	self:Move(dir)
	self:GUpdate()
	camera:Move(dir * self.speed * deltatime)

	-- Check if player collided with walls

	for i = 1, #walls do

		-- Move back the player when colliding
		if (C_CheckSpriteCollision(self.id, walls[i].id)) then
			
			dir.x = dir.x * -1
			dir.z = dir.z * -1
			self:Move(dir)
			self:GUpdate()
			camera:Move(dir * self.speed * deltatime)

			-- Found collision - dont need to keep going
			break
		end
	end

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