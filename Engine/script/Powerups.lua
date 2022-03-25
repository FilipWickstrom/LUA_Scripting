-- require/include
gameObject = require('script/gameObject')

Powerup = gameObject:New()

local types = 
{
	[1] = "Money",
	[2] = "Attack",
	[3] = "Speed"
}

local RESPAWN_TIME = 5.0

function Powerup:Initiate()

	return types[math.random(3)]

end

function Powerup:New()
	local g = gameObject:New()
	g.type = self:Initiate()

	g.respawntimer = 0.0
	g.RandomizePos(g)
	g.id = LoadModel("clue_knife.obj")
	g.reach = 1.5
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
		player.damage = player.damage + 5
	end
	if self.type == "Speed" then
		player.speed = player.speed + 2.5
	end

	-- Hide from player.
	self.position.x = 100000

end

function Powerup:Update(player)
	
	-- player is close enough to the powerup
	local x = math.abs(player.position.x - self.position.x)
	local y = math.abs(player.position.y - self.position.y)
	if x <= self.reach and y <= self.reach then
		self:Gain(player)
	end
	
	self:GUpdate()

end

return Powerup