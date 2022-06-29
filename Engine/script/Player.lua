-- require/include
require('script/vector')
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
	g.fireRate = 0.2
	g.fireTimer = 0.0
	g.canShoot = true
	g.bullets = {}

	g.id = C_LoadSprite('knight.png')
	g.gid = C_AddHealthbar(0.0, 0.0, 250.0, 50.0)

	self.__index = Player
	setmetatable(g, self)
	return g
end

function Player:AddBullet(pos, dir)
	g = gameObject:New()
	g.id = C_LoadSprite('sword.png')
	g.position = pos
	g.dir = dir
	g.speed = 50
	g.lifetime = 4
	C_SetSpriteVisible(g.id, true)
	table.insert(self.bullets, g)
end

function Player:UpdateBullets()
	for i, obj in ipairs(self.bullets) do
		removed = false
		if obj.lifetime <= 0 then
			obj:OnEnd()
			table.remove(self.bullets, i)
			removed = true
		end
		if not removed then
			obj:Move(obj.dir)
			obj:GUpdate()
			obj.lifetime = obj.lifetime - deltatime
		end
	end
end

function Player:HandleMovement(camera)
	x = 0
	y = 0

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
	if self.fireTimer <= 0 then
		if C_IsKeyDown(keys.LBUTTON) then
			mousepoint = vector:New()
			mousepoint.x, mousepoint.y, mousepoint.z = C_GetWorldFromScreen()
			dir = mousepoint - self.position
			dir:Normalize()
			self:AddBullet(self.position, dir)
			self.fireTimer = self.fireRate
		end
	end

	self.fireTimer = self.fireTimer - deltatime

	self:UpdateBullets()
end

function Player:Update(camera)
	self:HandleMovement(camera)
	self:Shoot()

	if self.hp > 100.0 then
		self.hp = 100.0
	end

	-- GOD MODE!!
	--self.hp = 100
	C_UpdateUI(self.gid, self.hp)
	self:GUpdate()
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