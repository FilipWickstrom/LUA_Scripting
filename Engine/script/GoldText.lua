
local goldText = {}

function goldText:Initialize()

	goldText.id = C_AddText("Gold: XXX")
	local id = goldText.id
	C_SetTextSize(id, 400, 50)
	C_SetTextPosition(id, 10, 75)
	C_SetTextAlignment(id, "left")

end

function goldText:Update()

	-- Update the text here
	C_UpdateText(goldText.id, 'Gold: ' .. player.gold)

end

return goldText