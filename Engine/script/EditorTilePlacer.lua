local wallTile = require('script/WallTile')
local doorTile = require('script/DoorTile')
local monster = require('script/Monster')
local monkey = require('script/ThrowingEnemy')
local bouncy = require('script/BasicBossEnemy')
local shooter = require('script/ThrowingBoss')
local powerup = require('script/Powerups')


local tilePlacer = {} 

function tilePlacer:Initialize()

	-- start with the wall tile
	self.selected = wallTile:New()
	self.sprite = self.selected.defaultsprite
	self.selected.spritename = self.sprite

end

function tilePlacer:SetBlock(block)
	self.selected = block
end

function tilePlacer:UpdateBlock(block)
	self.sprite = block.defaultsprite
	block.spritename = self.sprite
end

function tilePlacer:Update()


	if (C_IsKeyDown(keys.ONE)) then

		self:SetBlock(wallTile)

	elseif (C_IsKeyDown(keys.TWO)) then

		self:SetBlock(doorTile)

	elseif (C_IsKeyDown(keys.THREE)) then

		self:SetBlock(monster)

	elseif (C_IsKeyDown(keys.FOUR)) then

		self:SetBlock(monkey)

	elseif (C_IsKeyDown(keys.FIVE)) then

		self:SetBlock(bouncy)

	elseif (C_IsKeyDown(keys.SIX)) then

		self:SetBlock(shooter)

	elseif (C_IsKeyDown(keys.SEVEN)) then

		self:SetBlock(powerup)

	end


end


return tilePlacer
