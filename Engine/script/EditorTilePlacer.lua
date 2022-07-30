local wallTile = require('script/WallTile')
local doorTile = require('script/DoorTile')
local monster = require('script/Monster')
local monkey = require('script/ThrowingEnemy')
local bouncy = require('script/BasicBossEnemy')
local shooter = require('script/ThrowingBoss')
local powerup = require('script/Powerups')
local spawnpoint = require('script/spawnpoint')
local goalpoint = require('script/goalpoint')
local floorTile = require('script/FloorTile')


local tilePlacer = {} 

function tilePlacer:Initialize()

	local window = { X = C_WinWidth(), Y = C_WinHeight() }
	local menuBtn = { X = 150, Y = 50 }
	local ySpace = 300

	-- start with the wall tile
	self.selected = wallTile:New()
	self.sprite = self.selected.defaultsprite
	self.selected.spritename = self.sprite
	self.indicator = C_AddImage2D(self.selected.spritename, window.X-(menuBtn.X/2), ySpace - 10)
	self.indicatorText = C_AddText('Block: ', "roboto_12.xml", window.X-(menuBtn.X), ySpace, 150, 50)

end

function tilePlacer:SetBlock(block)
	self.selected = block

	local temp = block:New()
	C_ChangeImage2D(self.indicator, temp.defaultsprite)
	temp:OnEnd()
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
	elseif (C_IsKeyDown(keys.EIGHT)) then

		self:SetBlock(spawnpoint)
	elseif (C_IsKeyDown(keys.NINE)) then

		self:SetBlock(goalpoint)
	elseif (C_IsKeyDown(keys.ZERO)) then
		self:SetBlock(floorTile)
	end




end


return tilePlacer
