require('script/AllScenes')
local GUI	= {}

function Start()
	local window = { X = C_WinWidth(), Y = C_WinHeight() }
	local btnSize	= { X = 400, Y = 100 }

	-- Space between the GUI
	local verticalSpace	= btnSize.Y * 1.5
	
	local yDistance = 0.20 * window.Y
	GUI["Title"]= C_AddText("Game Over...", "roboto_48.xml", window.X/2, yDistance, 800, 200)

	yDistance	= yDistance + verticalSpace
	GUI["UnderTitle"]= C_AddText("Score: 0", "roboto_28.xml", window.X/2, yDistance, 800, 200)

	yDistance	= yDistance + verticalSpace
	GUI["ReturnToMenu"] = C_AddButton("Return to menu", "roboto_28.xml", window.X/2, yDistance, btnSize.X, btnSize.Y)

end


function Clean()
	-- Cleaning up everything in LUA
	for key, value in next, GUI do
		GUI[key] = nil	
	end
end

function Update(dt)

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["ReturnToMenu"])) then
		C_ChangeScene(Scenes.MENU)
	end
end