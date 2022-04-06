-- require/include
gameObject = require('script/gameObject')

Powerup = gameObject:New()

local types = 
{
	[1] = "Money",
	[2] = "Attack",
	[3] = "Speed",
	[4] = "Health"
}

local RESPAWN_TIME = 5.0

function Powerup:Initiate()

	return types[math.random(4)]

end

function Powerup:New()
	local g = gameObject:New()
	g.type = self:Initiate()

	g.respawntimer = 0.0
	g.RandomizePos(g)
	g.id = LoadModel("clue_knife.obj")
	g.reach = 1.5
	g.shouldrespawn = false
	SetModelScale(g.id, 0.1)
	
	self.__index = Powerup
	setmetatable(g, self)
	return g
end

function Powerup:Gain(player)
	
	if self.type == "Money" then
		player.gold = player.gold + 15
	end
	if self.type == "Attack" then
		player.damage = player.damage + 5.0
	end
	if self.type == "Speed" then
		player.speed = player.speed + 2.5
	end
	if self.type == "Health" then
		player.health = player.health + 15.0
	end

	-- Hide from player.
	self.position.x = 100000

	self.respawntimer = RESPAWN_TIME
	self.shouldrespawn = true

end

function Powerup:Update(player, dt)
	
	-- player is close enough to the powerup
	local x = math.abs(player.position.x - self.position.x)
	local z = math.abs(player.position.z - self.position.z)
	if x <= self.reach and z <= self.reach and self.shouldrespawn == false then
		self:Gain(player)
	end
	
	self:GUpdate()

	if self.shouldrespawn == true then
		self.respawntimer = self.respawntimer - dt

		if self.respawntimer < 0 then
			self.shouldrespawn = false
			self.RandomizePos(self)
		end
	end

end

return Powerup