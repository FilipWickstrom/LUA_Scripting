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

	local window = { X = C_WinWidth(), Y = C_WinHeight() }
	local textField = { X = 150, Y = 50 }
	local yPos = 275


	-- start with the wall tile
	self.selected = wallTile:New()
	self.sprite = self.selected.defaultsprite
	self.selected.spritename = self.sprite
	self.indicator = C_AddImage2d(self.selected.spritename)
	C_SetImage2dPosition(self.indicator, window.X-(textField.X/2), yPos)
	C_SetImage2dScale(self.indicator, 1.5)

	self.indicatorText = C_AddText('Block: ', "roboto_12.xml", window.X-(textField.X/2), yPos, textField.X, textField.Y)
	C_SetTextAlignment(self.indicatorText, "left")

end

function tilePlacer:SetBlock(block)
	self.selected = block
	self.sprite = block.defaultsprite

	C_ChangeImage2d(self.indicator, self.sprite)
	C_SetImage2dScale(self.indicator, 1.5)
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
