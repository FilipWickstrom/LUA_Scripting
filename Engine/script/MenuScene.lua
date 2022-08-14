require('script/AllScenes')

local GUI	= {}

function Start()
	local window	= { X = C_WinWidth(),		Y = C_WinHeight() }
	local titleSize = { X = window.X * 0.6,		Y = window.Y * 0.2}
	local btnSize	= { X = window.X * 0.15,	Y = window.Y * 0.1 }
	local guiID

	local yDistance = 0.10 * window.Y
	GUI["Title"] = C_AddText("Budget Binding of Isaac")
	guiID = GUI["Title"]
	C_SetTextSize(guiID, titleSize.X, titleSize.Y)
	C_SetTextPosition(guiID, (window.X - titleSize.X)/2, 0.10 * window.Y)

	-- Space between the GUI
	yDistance = yDistance + titleSize.Y

	-- Play button
	GUI["Play"] = C_AddButton()
	guiID = GUI["Play"]
	C_SetButtonPosition(guiID, (window.X - btnSize.X)/2, yDistance)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Play")
	yDistance = yDistance + (btnSize.Y * 1.5)

	-- Edit button
	GUI["Edit"] = C_AddButton()
	guiID = GUI["Edit"]
	C_SetButtonPosition(guiID, (window.X - btnSize.X)/2, yDistance)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Edit")
	yDistance = yDistance + (btnSize.Y * 1.5)

	-- Quit button
	GUI["Quit"] = C_AddButton()
	guiID = GUI["Quit"]
	C_SetButtonPosition(guiID, (window.X - btnSize.X)/2, yDistance)
	C_SetButtonSize(guiID, btnSize.X, btnSize.Y)
	C_SetButtonText(guiID, "Quit")

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