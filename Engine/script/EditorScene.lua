require('script/SceneHelp')
local gameObject = require('script/gameObject') --temp

local GUI = {}

function Start()
	local window = { X = WinWidth(), Y = WinHeight() }

	GUI["Title"] = AddText("Level editor", "roboto_28.xml", window.X/2, 25, 400, 100)

	-- Buttons: Create, Load, Save
	local editBtn = { X = 100, Y = 50 }
	local xSpace = 0;
	GUI["Create"] = AddButton("Create", "roboto_12.xml", editBtn.X/2, editBtn.Y/2, editBtn.X, editBtn.Y)
	xSpace = xSpace + editBtn.X
	GUI["Load"] = AddButton("Load", "roboto_12.xml", editBtn.X/2 + xSpace, editBtn.Y/2, editBtn.X, editBtn.Y)
	xSpace = xSpace + editBtn.X
	GUI["Save"] = AddButton("Save", "roboto_12.xml", editBtn.X/2 + xSpace, editBtn.Y/2, editBtn.X, editBtn.Y)

	-- Buttons: Back to menu
	local menuBtn = { X = 150, Y = 50 }
	GUI["Menu"] = AddButton("Back to menu", "roboto_12.xml", window.X-(menuBtn.X/2), menuBtn.Y/2, menuBtn.X, menuBtn.Y)

end


function Clean()
	-- Go through all the GUI and remove it
	for key, value in next, GUI do
		RemoveGUI(value)
	end
end

-- Handle input from keyboard
function OnInput(x, y)

end


function Update(dt)
	-- Check if any of the buttons is clicked
	if (IsButtonPressed(GUI["Create"])) then
		--Call c++ create map

	elseif(IsButtonPressed(GUI["Load"])) then
		--Call c++ load map

	elseif(IsButtonPressed(GUI["Save"])) then
		--Call c++ save map

	elseif(IsButtonPressed(GUI["Menu"])) then
		ChangeScene(Scene.MENU)

	end

end