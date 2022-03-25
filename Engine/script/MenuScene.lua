require('script/SceneHelp')

GUI	= {}

function Start()
	local window = { X = WinWidth(), Y = WinHeight() }
	local btnSize	= { X = 250, Y = 100 }

	-- Space between the GUI
	local verticalSpace	= btnSize.Y * 1.5
	
	yDistance = 0.20 * window.Y
	GUI["Title"]= AddText("Budget Binding of Isaac", "roboto_48.xml", window.X/2, yDistance, 800, 200)

	yDistance	= yDistance + verticalSpace
	GUI["Play"] = AddButton("Play", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)
	
	yDistance	= yDistance + verticalSpace
	GUI["Edit"] = AddButton("Edit", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)
	
	yDistance	= yDistance + verticalSpace
	GUI["Quit"] = AddButton("Quit", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)

end

function Clean()
	-- Go through all the GUI and remove it
	for key, value in next, GUI do
		RemoveGUI(value)
	end
end

function Update()
	-- Check if any of the buttons is clicked
	if (IsButtonPressed(GUI["Play"])) then
		ChangeScene(Scene.GAME)

	elseif(IsButtonPressed(GUI["Edit"])) then
		ChangeScene(Scene.EDITOR)

	elseif(IsButtonPressed(GUI["Quit"])) then
		ChangeScene(Scene.NONE)
	end

end

