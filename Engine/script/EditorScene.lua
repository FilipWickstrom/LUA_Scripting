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
local selectedObject = -1

-- Global so that it can be changed in the console if needed
currentMap = "Level1.map"

function Start()
	local window = { X = C_WinWidth(), Y = C_WinHeight() }

	GUI["Title"] = C_AddText("Level editor", "roboto_28.xml", window.X/2, 25, 250, 75)

	-- Buttons: New, Load, Save
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
	ySpace = ySpace + editBtn.Y

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

		-- Drag tile
		if (C_IsKeyDown(keys.SPACE)) then

			if (selectedObject == -1) then
				selectedObject = C_GetTileObjectID()
				--print(selectedObject)
			end

		end

		-- place tile
		if (C_IsKeyDown(keys.LBUTTON)) then
			
			if (selector.selected ~= nil and selectedObject == -1) then

				if (not C_IsTileOccupied()) then
					local obj = selector.selected:New()
					obj:LoadSprite(selector.sprite)

					C_AddTile(obj.id)

					local vec = vector:New()			
					vec.x, vec.y, vec.z = C_GetTilePos(obj.id)
					obj:SetPosition(vec.x, vec.y, vec.z)

					objects[obj.id] = obj

					if (obj.type == "spawnpoint") then
						obj:AddIcon()
					end
				end
			else
				
				-- Stop updating the selected object
				selectedObject = -1

			end
		
		-- remove tile
		elseif (C_IsKeyDown(keys.RBUTTON)) then
			
			if (C_IsTileOccupied()) then
				local id = C_RemoveTile()
				if (id ~= -1 and objects[id] ~= nil) then
					objects[id]:OnEnd()
					objects[id] = nil
					selectedObject = -1
				end
			end
		end

	end

	camera:UpdateMovement()
	camera:UpdateZoom()
	selector:Update()
	C_GridUpdateHover()

	for num, obj in pairs(objects) do
		-- Update spawnpoint objects
		if (obj.type == "spawnpoint") then
			obj:Update()
		end
	end

	-- Update the position of the selected object
	if selectedObject ~= -1 and objects[selectedObject] ~= nil then

		local vec = vector:New()
		C_UpdateTilePos(selectedObject)
		vec.x, vec.y, vec.z = C_GetTilePos(selectedObject)
		--print(vec)
		objects[selectedObject]:SetPosition(vec.x, vec.y, vec.z)

	end

end