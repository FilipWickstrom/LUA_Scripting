local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local BasicBoss = gameObject:New()
local COOLDOWN_TIME = 3.0

function BasicBoss:New()
	local g = gameObject:New()
	g.hp = 100
	g.worth = 30
	g.xp = 25
	g.damage = 25
	g.speed = 5
	g.type = "bouncy"
	g.name = "enemy"
	g.direction = {x = 1, z = 1}
	g.cooldown = 0

	g.gid = C_AddHealthbar(0.0, 0.0, 100.0, 50.0)

	self.__index = BasicBoss
	setmetatable(g, self)
	return g
end

function BasicBoss:OnDeath(playerGold)
	playerGold = playerGold + self.worth
end

function BasicBoss:Chase()
	local dir = vector:New()
	if self.position.x > 18 or self.position.x < -22 then
		self.direction.x = self.direction.x * -1
	end
	
	if self.position.z > 11 or self.position.z < -11 then
		self.direction.z = self.direction.z * -1
	end

	dir.x = self.direction.x
	dir.z = self.direction.z

	self:Move(dir)
end

function BasicBoss:Attack(player)

	local x = math.abs(player.position.x - self.position.x)
	local z = math.abs(player.position.z - self.position.z)

	self.cooldown = self.cooldown - deltatime

	if C_CheckSpriteCollision(player.id, self.id) and self.cooldown <= 0.0 then
		player.hp = player.hp - self.damage
		self.cooldown = COOLDOWN_TIME
	end

end

function BasicBoss:Update(player)
	self:Chase()
	self:Attack(player)
	self:GUpdate()
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 100.0, 50.0)
	C_UpdateUI(self.gid, self.hp)
end


return BasicBoss