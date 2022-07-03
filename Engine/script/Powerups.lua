-- require/include
gameObject = require('script/gameObject')

Powerup = gameObject:New()

local BOMB_RADIUS = 5.0
local BOMB_DAMAGE = 50.0

local types = 
{
	[1] = "Money",
	[2] = "Attack",
	[3] = "Speed",
	[4] = "Health",
	[5] = "Bomb"
}

local RESPAWN_TIME = 5.0

function Powerup:Initiate()
	
	return types[math.random(#types)]
	--return "Bomb"

end

function Powerup:New()
	local g = gameObject:New()
	g.type = self:Initiate()

	g.respawntimer = 0.0
	g.shouldrespawn = false
	g.id = C_LoadSprite("chest.png")
	g:RandomizePos()
	g.position.y = 1
	g:GUpdate()

	g.bomb = gameObject:New()
	g.bomb.id = C_LoadSprite('bomb.png')
	g.bomb.position = g.position
	g.bomb.countdown = 3.0
	g.bomb.active = false
	g.bomb:GUpdate()
	C_SetSpriteVisible(g.bomb.id, false)

	self.__index = Powerup
	setmetatable(g, self)
	return g
end

function Powerup:Gain(player, goldText)

	if self.type == "Money" then
		player.gold = player.gold + 5

		-- Update gold text
		goldText:Update(player)
	elseif self.type == "Attack" then
		player.damage = player.damage + 5.0
	elseif self.type == "Speed" then
		player.speed = player.speed + 2.5
	elseif self.type == "Health" then
		player.hp = player.hp + 15.0
	elseif self.type == "Bomb" then
		self.bomb.active = true

		self.bomb.position.x = self.position.x
		self.bomb.position.z = self.position.z
		self.bomb:GUpdate()
		C_SetSpriteVisible(self.bomb.id, true)

	end

	player.lastpickup = self.type

	-- Hide from player.
	C_SetSpriteVisible(self.id, false)
	--self.OnEnd()

	self.respawntimer = RESPAWN_TIME
	self.shouldrespawn = true

end

function Powerup:Update(player, enemies, goldText, lastpickupText)
	
	--Check if player and the powerup is colliding
	if C_CheckSpriteCollision(player.id, self.id) and self.shouldrespawn == false then
		
		self:Gain(player, goldText)

		-- Update last pickup text
		if lastpickupText ~= nil then
			lastpickupText:Update()
		end
	end
	
	self:GUpdate()

	-- Powerup respawns
	if self.shouldrespawn == true then
		self.respawntimer = self.respawntimer - deltatime

		if self.respawntimer < 0 then
			self.shouldrespawn = false
			self:RandomizePos()
			self:GUpdate()
			self.type = self:Initiate()
			C_SetSpriteVisible(self.id, true)
		end
	end


	-- Update bomb timer
	if(self.bomb.active == true) then
		self.bomb.countdown = self.bomb.countdown - deltatime
	end

	-- Bomb explodes
	if(self.bomb.countdown < 0) then
		self.bomb.active = false
		self.bomb.countdown = 3


		for k, v in pairs(enemies) do
			
			local x = math.abs(v.position.x - self.bomb.position.x)
			local z = math.abs(v.position.z - self.bomb.position.z)

			if(x < BOMB_RADIUS and z < BOMB_RADIUS) then
				v.hp = v.hp - BOMB_DAMAGE
			end

		end

		C_SetSpriteVisible(self.bomb.id, false)
	end

end

return Powerup