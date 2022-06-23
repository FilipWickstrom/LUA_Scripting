-- require/include
gameObject = require('script/gameObject')

Powerup = gameObject:New()

local BOMB_RADIUS = 5.0
local BOMB_DAMAGE = 10000.0
local POWERUP_REACH = 1.5

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
	g.RandomizePos(g)
	g.id = C_LoadSprite("chest.png")
	g.shouldrespawn = false

	g.bomb = gameObject:New()
	g.bomb.id = C_LoadSprite('bomb.png')
	g.bomb.position.x = 1000
	g.bomb.countdown = 3.0
	g.bomb.active = false
	C_SetSpritePosition(g.bomb.id, g.bomb.position.x, g.bomb.position.z)
	
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

		C_SetSpritePosition(self.bomb.id, self.bomb.position.x, self.bomb.position.z)
	end

	player.lastpickup = self.type

	-- Hide from player.
	self.position.x = 100000
	--self.OnEnd()

	self.respawntimer = RESPAWN_TIME
	self.shouldrespawn = true

end

function Powerup:Update(player, dt, enemies, goldText, lastpickupText)
	
	-- player is close enough to the powerup
	local x = math.abs(player.position.x - self.position.x)
	local z = math.abs(player.position.z - self.position.z)
	if x <= POWERUP_REACH and z <= POWERUP_REACH and self.shouldrespawn == false then
		self:Gain(player, goldText)

			-- Update last pickup text
		if lastpickupText ~= nil then
			lastpickupText:Update()
		end
	end
	
	self:GUpdate()

	-- Powerup respawns
	if self.shouldrespawn == true then
		self.respawntimer = self.respawntimer - dt

		if self.respawntimer < 0 then
			self.shouldrespawn = false
			self.RandomizePos(self)
			self.type = self:Initiate()
		end
	end


	-- Update bomb timer
	if(self.bomb.active == true) then
		self.bomb.countdown = self.bomb.countdown - dt
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

		-- Move away the bomb from the player
		self.bomb.position.x = player.position.x + 100000
		C_SetSpritePosition(self.bomb.id, self.bomb.position.x, self.bomb.position.z)
	end

end

return Powerup