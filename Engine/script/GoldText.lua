
local goldText = {}

function goldText:Initialize()

	goldText.id = C_AddText("Gold: 0", "roboto_28.xml", 120, 100, 200, 100)
	C_SetTextAlignment(goldText.id, "left")

end

function goldText:Update()

	-- Update the text here
	C_UpdateText(goldText.id, 'Gold: ' .. player.gold)

end

return goldText