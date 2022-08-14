require('script/AllScenes')

local GUI = {}

function Start()
	local window	= { X = C_WinWidth(),		Y = C_WinHeight() }
	local btnSize	= { X = window.X * 0.25,	Y = window.Y * 0.1 }
	local textSize	= { X = window.X * 0.5,		Y = window.Y * 0.15 }
	local guiID

	local yDistance = 0.10 * window.Y
	local verticalSpace	= textSize.Y * 2

	-- Main text
	GUI["Title"] = C_AddText("Game Over...")
	guiID = GUI["Title"]
	C_SetTextSize(guiID, textSize.X, textSize.Y)
	C_SetTextPosition(guiID, (window.X - textSize.X)/2, yDistance)
	yDistance = yDistance + verticalSpace

	-- Undertitle
	GUI["UnderTitle"] = C_AddText("Score: 0")
	guiID = GUI["UnderTitle"]
	C_SetTextSize(guiID, btnSize.X, btnSize.Y)
	C_SetTextPosition(guiID, (window.X - btnSize.X)/2, yDistance)
	yDistance = yDistance + verticalSpace

	-- Button to get back to menu
	GUI["ReturnToMenu"] = C_AddButton()
	guiID = GUI["ReturnToMenu"]
	C_SetButtonPosition(guiID, (window.X - btnSize.X)/2, yDistance)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Return to menu")

end


function Update(dt)

	-- Check if any of the buttons is clicked
	if (C_IsButtonPressed(GUI["ReturnToMenu"])) then
		C_ChangeScene(Scenes.MENU)
	end
end