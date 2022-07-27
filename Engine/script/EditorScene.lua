require('script/AllScenes')
local vector = require('script/Vector')
local Camera = require('script/Camera')
local selectedBlock = require('script/WallTile')
require('script/File')
local Window = require('script/Options')

-- Placing tiles 'requires'
local selector	= require('script/EditorTilePlacer')
local wallTile	= require('script/WallTile')
local doorTile	= require('script/DoorTile')
local monster	= require('script/Monster')
local monkey	= require('script/ThrowingEnemy')
local bouncy	= require('script/BasicBossEnemy')
local shooter	= require('script/ThrowingBoss')
local powerup	= require('script/Powerups')
local player	= require('script/Player'):New()

-- "Globals" in this scope
local objects = {}
local loaded = false
local created = false
local saved = false
local GUI = {}
local pointerDummy = {id = 0}

function Start()
	local window = { X = C_WinWidth(), Y = C_WinHeight() }

	GUI["Title"] = C_AddText("Level editor", "roboto_28.xml", window.X/2, 25, 250, 75)

	-- Buttons: Create, Load, Save
	local editBtn = { X = 100, Y = 50 }
	local xSpace = 0;
	GUI["New"] = C_AddButton("New", "roboto_12.xml", editBtn.X/2, editBtn.Y/2, editBtn.X, editBtn.Y)
	xSpace = xSpace + editBtn.X
	GUI["Load"] = C_AddButton("Load", "roboto_12.xml", editBtn.X/2 + xSpace, editBtn.Y/2, editBtn.X, editBtn.Y)
	xSpace = xSpace + editBtn.X
	GUI["Save"] = C_AddButton("Save", "roboto_12.xml", editBtn.X/2 + xSpace, editBtn.Y/2, editBtn.X, editBtn.Y)

	-- Buttons: Back to menu
	local menuBtn = { X = 150, Y = 50 }
	GUI["Menu"] = C_AddButton("Back to menu", "roboto_12.xml", window.X-(menuBtn.X/2), menuBtn.Y/2, menuBtn.X, menuBtn.Y)

	-- Layers
	local ySpace = 75
	GUI["LayerText"] = C_AddText("Layer: Ground", "roboto_12.xml", window.X-75, ySpace, 150, 50)
	C_SetTextAlignment(GUI["LayerText"], "left")
	ySpace = ySpace + editBtn.Y
	GUI["Layer0"] = C_AddButton("Ground", "roboto_12.xml", window.X-(menuBtn.X/2), ySpace, menuBtn.X, menuBtn.Y)
	ySpace = ySpace + editBtn.Y
	GUI["Layer1"] = C_AddButton("Items", "roboto_12.xml", window.X-(menuBtn.X/2), ySpace, menuBtn.X, menuBtn.Y)
	ySpace = ySpace + editBtn.Y
	GUI["Layer2"] = C_AddButton("Entities", "roboto_12.xml", window.X-(menuBtn.X/2), ySpace, menuBtn.X, menuBtn.Y)

	-- Create a camera
	camera = Camera:New()
	camera:SetPosition(0,0)
	camera:SetZoom(5)

	C_ToggleRenderUI(false)

	C_AddGrid(100,100)

	selector:Initialize()

	pointerDummy.id = C_AddImage2D('knight_sword.png', 900, 500)

end


function Update(dt)
	deltatime = dt

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["New"])) then

		if (not created) then
			loaded = false
			for num, obj in pairs(objects) do
				obj:OnEnd()
			end

			-- reset objects
			objects = {}
			C_ResetGrid()
		end

	elseif(C_IsButtonPressed(GUI["Load"])) then
		
		if (not loaded) then

			-- Reset scene before loading.
			for num, obj in pairs(objects) do
				obj:OnEnd()
			end
			objects = {}
			C_ResetGrid()

			-- Load in the new scene
			objects = Load_File('maps/test1.txt')
			loaded = true
			created = false

			-- Add all the objects to the grid
			for num, obj in pairs(objects) do
				C_AddTile(num, obj.position.x, obj.position.y, obj.position.z)
			end
		end


	elseif(C_IsButtonPressed(GUI["Save"])) then
		
		if (not saved) then
			Write_To_File(objects, 'maps/test1.txt')
			saved = false
		end

	elseif(C_IsButtonPressed(GUI["Menu"])) then
		C_ChangeScene(Scenes.MENU)

	-- Change what layer we want to place on
	elseif (C_IsButtonPressed(GUI["Layer0"])) then
		C_SetGridLayer(0)
		C_UpdateText(GUI["LayerText"], "Layer: Ground")
	elseif (C_IsButtonPressed(GUI["Layer1"])) then
		C_SetGridLayer(1)
		C_UpdateText(GUI["LayerText"], "Layer: Items")
	elseif (C_IsButtonPressed(GUI["Layer2"])) then
		C_SetGridLayer(2)
		C_UpdateText(GUI["LayerText"], "Layer: Entities")

	else
		-- place tile
		if (C_IsKeyDown(keys.LBUTTON)) then
			
			if (selector.selected ~= nil) then

				if (not C_IsTileOccupied()) then
					local obj = selector.selected:New()
					selector:UpdateBlock(obj)
					obj:LoadSprite(selector.sprite)
					C_AddTile(#objects + 1)

					local vec = vector:New()			
					vec.x, vec.y, vec.z = C_GetTilePos(#objects + 1)
					obj:SetPosition(vec.x, vec.y, vec.z)

					objects[#objects + 1] = obj

					if obj.type == 'spawnpoint' then
						player:SetPosition(vec.x, vec.y, vec.z)
					end
				end
			end		
		
		-- remove tile
		elseif (C_IsKeyDown(keys.RBUTTON)) then
			
			if (C_IsTileOccupied()) then
				local id = C_RemoveTile()
				if (id ~= -1 and objects[id] ~= nil) then
					objects[id]:OnEnd()
					objects[id] = nil
				end
			end
		end

	end

	camera:UpdateMovement()
	camera:UpdateZoom()
	selector:Update()

	
	-- Update Indicator to be above player dummy image
	local x, y = C_ObjectToScreen(player.id)

	if x < 0 then
		x = 0
	elseif x > Window.width then
		x = Window.width - 8.0
	end
	if y < 0 then
		y = 0
	elseif y > Window.height then
		y = Window.height - 32.0
	end

	if pointerDummy ~= nil then
		C_UpdateImage2D(pointerDummy.id, x, y)
	end
	

end