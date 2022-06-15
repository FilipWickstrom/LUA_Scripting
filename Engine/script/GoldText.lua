
local goldText = {}

function goldText:Initialize()

	goldText.text = AddText("Gold: 0", "roboto_48.xml", 100, 100, 800, 200)

end

function goldText:Update(player)

	-- Update the text here
	UpdateText(goldText.text, 'Gold: ' .. player.gold)

end

return goldText