require('script/SceneHelp')

GUI = {}

function Start()
	local window = { X = WinWidth(), Y = WinHeight() }

	GUI["Title"] = AddText("Level editor", "roboto_28.xml", window.X/2, 25, 400, 100)

	-- Buttons: Create, Load, Save
	local btnSize	= { X = 100, Y = 50 }
	local xSpace = 0;
	GUI["Create"] = AddButton("Create", "roboto_12.xml", btnSize.X/2, btnSize.Y/2, btnSize.X, btnSize.Y)
	xSpace = xSpace + btnSize.X
	GUI["Load"] = AddButton("Load", "roboto_12.xml", btnSize.X/2 + xSpace, btnSize.Y/2, btnSize.X, btnSize.Y)
	xSpace = xSpace + btnSize.X
	GUI["Save"] = AddButton("Save", "roboto_12.xml", btnSize.X/2 + xSpace, btnSize.Y/2, btnSize.X, btnSize.Y)

	-- Other stuff

	GUI["Menu"] = AddButton("Back to menu", "roboto_12.xml", window.X, btnSize.Y/2, btnSize.X, btnSize.Y)

end


function Clean()
	-- Go through all the GUI and remove it
	for key, value in next, GUI do
		RemoveGUI(value)
	end
end


function Update()
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