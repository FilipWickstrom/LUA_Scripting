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
local GUI = {}

function tilePlacer:Initialize()

	-- start with the wall tile
	self:SetBlock(wallTile)

	local tiles = { 
		-- Ground
		{ name = wallTile.type,		image = wallTile.defaultsprite},
		{ name = doorTile.type,		image = doorTile.defaultsprite},
		{ name = floorTile.type,	image = floorTile.defaultsprite},
		{ name = spawnpoint.type,	image = spawnpoint.defaultsprite},
		{ name = goalpoint.type,	image = goalpoint.defaultsprite},

		-- Items
		{ name = powerup.type,		image = powerup.defaultsprite},

		-- Entities
		{ name = monster.type,		image = monster.defaultsprite},
		{ name = monkey.type,		image = monkey.defaultsprite},
		{ name = shooter.type,		image = shooter.defaultsprite},
		{ name = bouncy.type,		image = bouncy.defaultsprite}
	}
	
	local tilesPerRow = 10
	local offset = 10
	local btnSize = {X=C_WinWidth()/tilesPerRow-(offset*2), Y=C_WinWidth()/tilesPerRow-(offset*2)}
	local position = {X=offset, Y=C_WinHeight() - btnSize.Y - offset}
	 

	local nrOfTiles = MapLength(tiles)
	for i=1, nrOfTiles do
		local id = C_AddButton()
		local btnName = tiles[i].name
		local image   = tiles[i].image
		
		-- Edit the button
		GUI[btnName] = id
		C_SetButtonPosition(id, position.X, position.Y)
		C_SetButtonSize(id, btnSize.X, btnSize.Y)
		C_SetButtonText(id, btnName)
		C_SetButtonFont(id,	"small.xml")
		C_SetButtonImage(id, image)

		-- Step forward for the next
		position.X = position.X + btnSize.X + 2*offset
    end

end

function tilePlacer:SetBlock(block)
	self.selected = block
	self.sprite = block.defaultsprite

	C_SetGridHoverSprite(self.sprite)
end

function tilePlacer:Update()

	if (C_IsButtonPressed(GUI[wallTile.type])) then
		self:SetBlock(wallTile)
		return true

	elseif (C_IsButtonPressed(GUI[doorTile.type])) then
		self:SetBlock(doorTile)
		return true

	elseif (C_IsButtonPressed(GUI[floorTile.type])) then
		self:SetBlock(floorTile)
		return true

	elseif (C_IsButtonPressed(GUI[spawnpoint.type])) then
		self:SetBlock(spawnpoint)
		return true

	elseif (C_IsButtonPressed(GUI[goalpoint.type])) then
		self:SetBlock(goalpoint)
		return true

	elseif (C_IsButtonPressed(GUI[powerup.type])) then
		self:SetBlock(powerup)
		return true

	elseif (C_IsButtonPressed(GUI[monster.type])) then
		self:SetBlock(monster)
		return true

	elseif (C_IsButtonPressed(GUI[monkey.type])) then
		self:SetBlock(monkey)
		return true

	elseif (C_IsButtonPressed(GUI[shooter.type])) then
		self:SetBlock(shooter)
		return true

	elseif (C_IsButtonPressed(GUI[bouncy.type])) then
		self:SetBlock(bouncy)
		return true

	end

	return false
end


return tilePlacer
