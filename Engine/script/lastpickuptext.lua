
local lpText = {}

function lpText:Initialize(player)

	lpText.playerRef = player
	lpText.text = C_AddText("Last Pickup: None", "roboto_48.xml", 270, 200, 700, 100)

end

function lpText:Update()
	C_UpdateText(self.text, "Last Pickup: " .. self.playerRef.lastpickup)
end


return lpText