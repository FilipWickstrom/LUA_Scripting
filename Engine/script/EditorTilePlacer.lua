-- Avoid recreating objects by using new
local wallTile = require('script/WallTile'):New()
local doorTile = require('script/DoorTile'):New()
local monster = require('script/Monster'):New()
local monkey = require('script/ThrowingEnemy'):New()
local bouncy = require('script/BasicBossEnemy'):New()
local shooter = require('script/ThrowingBoss'):New()
local powerup = require('script/Powerups'):New()
local spawnpoint = require('script/spawnpoint'):New()
local goalpoint = require('script/goalpoint'):New()
local floorTile = require('script/FloorTile'):New()

-- Cleanup when creating this objects
C_RemoveSprite(doorTile.key.id)

local tilePlacer = {} 

function tilePlacer:Initialize()

	-- start with the wall tile
	self:SetBlock(wallTile)

end

function tilePlacer:SetBlock(block)
	self.selected = block
	self.sprite = block.defaultsprite

	C_SetGridHoverSprite(self.sprite)
end

function tilePlacer:Update()


	if (C_IsKeyDown(keys.ONE)) then
		self:SetBlock(wallTile)

	elseif (C_IsKeyDown(keys.TWO)) then
		self:SetBlock(doorTile)
	
	elseif (C_IsKeyDown(keys.THREE)) then
		monster:RandomSprite()
		self:SetBlock(monster)
		
	elseif (C_IsKeyDown(keys.FOUR)) then
		self:SetBlock(monkey)

	elseif (C_IsKeyDown(keys.FIVE)) then
		self:SetBlock(bouncy)
	
	elseif (C_IsKeyDown(keys.SIX)) then
		self:SetBlock(shooter)
	
	elseif (C_IsKeyDown(keys.SEVEN)) then
		self:SetBlock(powerup)
	
	elseif (C_IsKeyDown(keys.EIGHT)) then
		self:SetBlock(spawnpoint)
	
	elseif (C_IsKeyDown(keys.NINE)) then
		self:SetBlock(goalpoint)

	elseif (C_IsKeyDown(keys.ZERO)) then
		floorTile:RandomSprite()
		self:SetBlock(floorTile)
	end

end


return tilePlacer
