require('script/AllScenes')
local vector = require('script/Vector')
local Camera = require('script/Camera')
local selectedBlock = require('script/WallTile')
require('script/File')

-- Placing tiles 'requires'
local selector	= require('script/EditorTilePlacer')
local wallTile	= require('script/WallTile')
local doorTile	= require('script/DoorTile')
local monster	= require('script/Monster')
local monkey	= require('script/ThrowingEnemy')
local bouncy	= require('script/BasicBossEnemy')
local shooter	= require('script/ThrowingBoss')
local powerup	= require('script/Powerups')

-- "Globals" in this scope
local objects = {}
local GUI = {}
local loadedMap = {}
local savedMap = {}
local camera = nil
local movedObjID = -1

-- Global so that it can be changed in the console if needed
currentMap = "Level1.map"

function Start()
	local window	= { X = C_WinWidth(),	 Y = C_WinHeight() }
	local titleSize = { X = window.X * 0.2,	 Y = window.Y * 0.07}
	local btnSize	= { X = 0.07 * window.X, Y = 0.05 * window.Y }
	local guiID

	-- Level editor textfield
	GUI["Title"] = C_AddText("Level Editor")
	guiID = GUI["Title"]
	C_SetTextSize(guiID, titleSize.X, titleSize.Y)
	C_SetTextPosition(guiID, (window.X - titleSize.X)/2, 0)

	-- New button
	GUI["New"] = C_AddButton()
	guiID = GUI["New"]
	C_SetButtonPosition(guiID, 0, 0)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "New")

	-- Load button
	GUI["Load"] = C_AddButton()
	guiID = GUI["Load"]
	C_SetButtonPosition(guiID, btnSize.X, 0)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Load")

	-- Save button
	GUI["Save"] = C_AddButton()
	guiID = GUI["Save"]
	C_SetButtonPosition(guiID, 2*btnSize.X, 0)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Save")


	-- Layers
	btnSize.X = 0.1 * window.X
	GUI["LayerText"] = C_AddText("Layer: Ground")
	guiID = GUI["LayerText"]
	C_SetTextSize(guiID, btnSize.X, btnSize.Y)
	C_SetTextPosition(guiID, (window.X - btnSize.X), 0)

	GUI["Layer0"] = C_AddButton()
	guiID = GUI["Layer0"]
	C_SetButtonPosition(guiID, window.X-btnSize.X, btnSize.Y)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Ground")

	GUI["Layer1"] = C_AddButton()
	guiID = GUI["Layer1"]
	C_SetButtonPosition(guiID, window.X-btnSize.X, btnSize.Y*2)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Items")

	GUI["Layer2"] = C_AddButton()
	guiID = GUI["Layer2"]
	C_SetButtonPosition(guiID, window.X-btnSize.X, btnSize.Y*3)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Entities")


	-- Create a camera
	camera = Camera:New()
	camera:SetPosition(0,0)
	camera:SetZoom(5)

	C_ToggleRenderUI(false)

	C_AddGrid(100,100)

	selector:Initialize()

end


function Update(dt)
	deltatime = dt

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["New"])) then
		for num, obj in pairs(objects) do
			obj:OnEnd()
		end

		-- reset objects
		objects = {}
		loadedMap = {}
		savedMap = {}
		C_ResetGrid()


	elseif(C_IsButtonPressed(GUI["Load"])) then
		
		-- Check if current map is the same as the loaded one
		if (not HasSameKeys(loadedMap, objects)) then

			-- Reset scene before loading.
			for num, obj in pairs(objects) do
				obj:OnEnd()
			end
			objects = {}
			C_ResetGrid()

			-- Load in the new scene
			objects = Load_Map(currentMap)
			loadedMap = MapShallowCopy(objects)

			-- Add all the objects to the grid
			for num, obj in pairs(objects) do
				C_AddTile(num, obj.position.x, obj.position.y, obj.position.z)

				if (obj.type == "spawnpoint") then
					obj:AddIcon()
				end
			end
		end


	elseif(C_IsButtonPressed(GUI["Save"])) then
		if (not HasSameKeys(savedMap, objects)) then
			Save_Map(objects, currentMap)
			savedMap = MapShallowCopy(objects)
		end

	-- Go back to menu by pressing escape
	elseif C_IsKeyDown(keys.ESCAPE) then
		C_ChangeScene(Scenes.MENU)
		return

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

	-- One of the buttons in selector has been updated
	elseif(selector:Update()) then
		--Should not go into else as it has "leftclick" inside of it

	else

		-- Drag/move a tile
		if (C_IsKeyPressedOnce(keys.SPACE)) then

			-- Select a tile
			if (movedObjID == -1) then
				
				movedObjID = C_GetTileObjectID()
				if (movedObjID ~= -1) then
					C_SetGridHoverSprite(objects[movedObjID].defaultsprite)
					C_SetSpriteBlinking(objects[movedObjID].id, true)
				end
			end
		
		-- Releasing the held tile
		elseif (C_IsKeyReleasedOnce(keys.SPACE)) then

			if (movedObjID ~= -1) then
				local vec = vector:New()
				C_UpdateTilePos(movedObjID)
				vec.x, vec.y, vec.z = C_GetTilePos(movedObjID)
				objects[movedObjID]:SetPosition(vec.x, vec.y, vec.z)
				C_SetSpriteBlinking(objects[movedObjID].id, false)

				-- Stop updating the selected object
				movedObjID = -1
				-- Change back to previous sprite
				C_SetGridHoverSprite(selector.sprite)
			end


		-- Place a tile
		elseif (C_IsKeyDown(keys.LBUTTON)) then
			
			--Check that a block is selected
			if (selector.selected) then

				if (not C_IsTileOccupied()) then
					local obj = selector.selected:New()
					obj:LoadSprite(obj.defaultsprite)

					C_AddTile(obj.id)

					local vec = vector:New()			
					vec.x, vec.y, vec.z = C_GetTilePos(obj.id)
					obj:SetPosition(vec.x, vec.y, vec.z)

					objects[obj.id] = obj

					if (obj.type == "spawnpoint") then
						obj:AddIcon()
					end
				end
			
			end
		
		-- Remove a tile
		elseif (C_IsKeyDown(keys.RBUTTON)) then
			
			if (C_IsTileOccupied()) then
				local id = C_RemoveTile()
				if (id ~= -1 and objects[id]) then
					objects[id]:OnEnd()
					objects[id] = nil
				end
			end
		end

	end

	camera:UpdateMovement()
	camera:UpdateZoom()
	C_GridUpdateHover()

	for num, obj in pairs(objects) do
		-- Update spawnpoint objects
		if (obj.type == "spawnpoint") then
			obj:Update()
		end
	end

end