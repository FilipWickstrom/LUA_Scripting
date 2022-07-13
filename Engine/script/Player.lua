-- Includes
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
	g:SetPosition(0,0.2,0)
	-- Add effects here.
	g.lastpickup = "None"

	g.id = C_LoadSprite('knight.png')

	-- Healthbar for health
	g.gid = C_AddHealthbar(0.0, 0.0, 250.0, 50.0, g.hp)

	-- Healthbar for fireTimer.
	g.sid = C_AddHealthbar(265.0, 0.0, 515.0, 50.0, g.weapon.fireRate)
	C_SetHealthbarBackgroundColor(g.sid, 0.0, 0.0, 255.0)
	C_SetHealthbarForegroundColor(g.sid, 0.0, 0.0, 0.0);

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
	camera:Move(dir * self.speed * deltatime)

	for i = 1, #walls do

		--Check if player and wall is colliding
		if (C_CheckSpriteCollision(self.id, walls[i].id)) then
			-- Move back the player when colliding
			dir.x = dir.x * -1
			dir.z = dir.z * -1
			self:Move(dir)
			camera:Move(dir * self.speed * deltatime)

			-- Found collision - dont need to keep going
			break
		end
	end

end

function Player:Shoot()
	if C_IsKeyDown(keys.LBUTTON) then
		local mousepoint = vector:New()
		mousepoint.x, mousepoint.y, mousepoint.z = C_GetWorldFromScreen()
		local dir = mousepoint - self.position
		dir:Normalize()
		self.weapon:Fire(self.position, dir)
	end
end

function Player:Update(camera, enemies)
	self:HandleMovement(camera)
	self:Shoot()
	self.weapon:Update(enemies)
	

	if self.hp > 100.0 then
		self.hp = 100.0
	end

	-- GOD MODE!!
	--self.hp = 100
	C_UpdateUI(self.gid, self.hp)
	C_UpdateUI(self.sid, self.weapon.fireTimer)
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