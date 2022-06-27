require('script/AllScenes')

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
	-- Cleaning up everything in LUA
	for key, value in next, GUI do
		GUI[key] = nil	
	end
end

function Update(dt)

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["Play"])) then
		C_ChangeScene(Scenes.GAME)

	elseif(C_IsButtonPressed(GUI["Edit"])) then
		C_ChangeScene(Scenes.EDITOR)

	elseif(C_IsButtonPressed(GUI["Quit"])) then
		C_ChangeScene(Scenes.NONE)
	end
end