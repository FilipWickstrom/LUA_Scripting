require('script/SceneHelp')

local GUI	= {}

function Start()
	local window = { X = C_WinWidth(), Y = C_WinHeight() }
	local btnSize	= { X = 250, Y = 100 }

	-- Space between the GUI
	local verticalSpace	= btnSize.Y * 1.5
	
	local yDistance = 0.20 * window.Y
	GUI["Title"]= C_AddText("Budget Binding of Isaac", "roboto_48.xml", window.X/2, yDistance, 800, 200)

	yDistance	= yDistance + verticalSpace
	GUI["Play"] = C_AddButton("Play", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)
	
	yDistance	= yDistance + verticalSpace
	GUI["Edit"] = C_AddButton("Edit", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)
	
	yDistance	= yDistance + verticalSpace
	GUI["Quit"] = C_AddButton("Quit", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)

end


function Clean()
	-- Go through all the GUI and remove it
	for key, value in next, GUI do
		C_RemoveGUI(value)
	end
end


-- Handle input from keyboard
function OnInput(x, y)

end


function Update(dt)

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["Play"])) then
		C_ChangeScene(Scene.GAME)

	elseif(C_IsButtonPressed(GUI["Edit"])) then
		C_ChangeScene(Scene.EDITOR)

	elseif(C_IsButtonPressed(GUI["Quit"])) then
		C_ChangeScene(Scene.NONE)
	end

end

