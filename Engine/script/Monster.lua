local gameObject = require('script/gameObject')
local Vector = require('script/vector')
local Monster = gameObject:New()

local COOLDOWN_TIME = 5.0

local monsters = {
	[1] = 'skeleton.png',
	[2] = 'swampy.png',
	[3] = 'masked_goblin.png',
	[4] = 'imp.png'
}


function Monster:New()
	local g = gameObject:New()
	g.hp = 15
	g.worth = 25
	g.xp = 25
	g.damage = 5
	g.speed = math.random(10) + math.random(10)
	g.type = "monster"
	g.name = "enemy"
	g.defaultsprite = monsters[math.random(#monsters)]
	g.cooldown = 0.0
	g.gid = C_AddHealthbar(0.0, 0.0, 75.0, 25.0, g.hp)
	self.__index = Monster
	setmetatable(g, self)

	return g
end

function Monster:OnDeath()
	self:OnEnd()
end

function Monster:Chase(point)

	-- Create a new vector.
	local dir = Vector:New()

	-- Not worth to change direction when too close
	if (math.abs(self.position.x - point.x) > 0.01) then
		
		-- Manipulate vector so that it follows the player.
		if(self.position.x < point.x) then
			dir.x = 1
			self:RotateRight()
		else
			dir.x = -1
			self:RotateLeft()
		end

	end


	if(self.position.z < point.z) then
		dir.z = 1
	else
		dir.z = -1
	end

	self:Move(dir)

	for i = 1, #walls do

		-- Check collision with all walls
		if (C_CheckSpriteCollision(self.id, walls[i].id)) then
			-- Move back the enemy when colliding
			dir.x = dir.x * -1
			dir.z = dir.z * -1
			self:Move(dir)
			-- Found collision - dont need to keep going
			break
		end
	end
end

function Monster:OnHit(playerHp)
	playerHp = playerHp - self.damage
	return playerHp
end

function Monster:Hit(player)

	self.cooldown = self.cooldown - deltatime

	if C_CheckSpriteCollision(player.id, self.id) and self.cooldown <= 0.0 and self.isVisible == 1 then
		player.hp = player.hp - self.damage
		self.cooldown = COOLDOWN_TIME
	end
end

function Monster:RandomSprite()
	self.defaultsprite = monsters[math.random(#monsters)]
end

function Monster:Update()
	self:Chase(player.position)
	self:Hit(player)
	C_UpdatePosUI(self.gid, self.position.x, self.position.z, 75.0, 25.0)
	C_UpdateUI(self.gid, self.hp)
end

return Monster