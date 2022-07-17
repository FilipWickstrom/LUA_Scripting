require('script/AllScenes')
local vector = require('script/Vector')
local gameObject = require('script/gameObject') --temp
local levelObjects = {}
local loaded = false
local created = false
local camera = require('script/Camera'):New()
local selectedBlock = require('script/WallTile')
require('script/File')

local GUI = {}

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
	camera:SetPosition(0,40,0)
	camera:SetTarget(0,0,0.1)
	camera:SetZoom(10)

	C_ToggleRenderUI(false)

	C_AddGrid(100,100)

	-- [DEBUG] Place a blank tile in origo 
	C_LoadSprite("")

end


function Update(dt)
	deltatime = dt

	if (C_IsKeyDown(keys.LBUTTON)) then
		if selectedBlock ~= nil then
			local newObject = selectedBlock:New()
			local newVector = vector:New()
			newVector.x, newVector.y, newVector.z = C_AddTile()
			newObject:LoadSprite('wall_mid.png')
			newObject:SetPosition(newVector.x, newVector.y, newVector.z)
			table.insert(levelObjects, newObject)
		end
	end

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["Create"])) then
		--Call c++ create map

		
		if (created == false) then
			loaded = false
			created = true
			for num, obj in pairs(levelObjects) do
				obj:OnEnd()
			end

			-- reset levelObjects
			levelObjects = {}
		end

	elseif(C_IsButtonPressed(GUI["Load"])) then
		--Call c++ load map
		if (loaded == false) then

			-- Reset scene before loading.
			for num, obj in pairs(levelObjects) do
				obj:OnEnd()
			end
			levelObjects = {}

			levelObjects = Load_File('maps/test1.txt')
			loaded = true
			created = false
		end


	elseif(C_IsButtonPressed(GUI["Save"])) then
		--Call c++ save map

	elseif(C_IsButtonPressed(GUI["Menu"])) then
		C_ChangeScene(Scenes.MENU)
	end

	camera:UpdateMovement()
	camera:UpdateZoom()

end