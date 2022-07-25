require('script/AllScenes')
local vector = require('script/Vector')
local Camera = require('script/Camera')
local selectedBlock = require('script/WallTile')
require('script/File')
Window = require('script/Options')

-- Placing tiles 'requires'
local selector = require('script/EditorTilePlacer')
local wallTile = require('script/WallTile')
local doorTile = require('script/DoorTile')
local monster = require('script/Monster')
local monkey = require('script/ThrowingEnemy')
local bouncy = require('script/BasicBossEnemy')
local shooter = require('script/ThrowingBoss')
local powerup = require('script/Powerups')

-- "Globals" in this scope
local objects = {}
local loaded = false
local created = false
local saved = false
local GUI = {}

-- player dummy
local playerDummy = gameObject:New()
local pointerDummy = {id = 0}

function Start()
	local window = { X = C_WinWidth(), Y = C_WinHeight() }

	GUI["Title"] = C_AddText("Level editor", "roboto_28.xml", window.X/2, 25, 400, 100)

	-- Buttons: Create, Load, Save
	local editBtn = { X = 100, Y = 50 }
	local xSpace = 0;
	GUI["Create"] = C_AddButton("Create", "roboto_12.xml", editBtn.X/2, editBtn.Y/2, editBtn.X, editBtn.Y)
	xSpace = xSpace + editBtn.X
	GUI["Load"] = C_AddButton("Load", "roboto_12.xml", editBtn.X/2 + xSpace, editBtn.Y/2, editBtn.X, editBtn.Y)
	xSpace = xSpace + editBtn.X
	GUI["Save"] = C_AddButton("Save", "roboto_12.xml", editBtn.X/2 + xSpace, editBtn.Y/2, editBtn.X, editBtn.Y)

	-- Buttons: Back to menu
	local menuBtn = { X = 150, Y = 50 }
	GUI["Menu"] = C_AddButton("Back to menu", "roboto_12.xml", window.X-(menuBtn.X/2), menuBtn.Y/2, menuBtn.X, menuBtn.Y)

	-- Create a camera
	camera = Camera:New()
	camera:SetPosition(0,40,0)
	camera:SetTarget(0,0,0.1)
	camera:SetZoom(5)

	C_ToggleRenderUI(false)

	C_AddGrid(100,100)

	selector:Initialize()


	playerDummy.id = C_LoadSprite('knight.png')
	playerDummy:SetPosition(1, 1, 1)
	pointerDummy.id = C_AddImage2D('knight_sword.png', 900, 500)

end


function Update(dt)
	deltatime = dt

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["Create"])) then
		--Call c++ create map

		if (created == false) then
			loaded = false
			for num, obj in pairs(objects) do
				obj:OnEnd()
			end

			-- reset objects
			objects = {}
			C_ResetGrid()
		end

	elseif(C_IsButtonPressed(GUI["Load"])) then
		--Call c++ load map
		if (loaded == false) then

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
		--Call c++ save map
		if saved == false then
			Write_To_File(objects, 'maps/test1.txt')
			saved = false
		end

	elseif(C_IsButtonPressed(GUI["Menu"])) then
		C_ChangeScene(Scenes.MENU)
	
	else
		-- place tile
		if (C_IsKeyDown(keys.LBUTTON)) then
			
			if (selector.selected ~= nil) then

				if (not C_IsTileOccupied(0)) then
					local obj = selector.selected:New()
					selector:UpdateBlock(obj)
					obj:LoadSprite(selector.sprite)
					C_AddTile(#objects + 1)

					local vec = vector:New()			
					vec.x, vec.y, vec.z = C_GetTilePos(#objects + 1)
					obj:SetPosition(vec.x, vec.y, vec.z)

					objects[#objects + 1] = obj
				end
			end		
		
		-- remove tile
		elseif (C_IsKeyDown(keys.RBUTTON)) then
			
			if (C_IsTileOccupied(0)) then
				local id = C_RemoveTile(0)
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
	local x, y = C_ObjectToScreen(playerDummy.id)

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