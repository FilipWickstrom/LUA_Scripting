
local lpText = {}

function lpText:Initialize(player)

	lpText.playerRef = player
	lpText.id = C_AddText("Last Pickup: None", "roboto_28.xml", 245, 200, 450, 100)
	C_SetTextAlignment(lpText.id, "left")

end

function lpText:Update()
	C_UpdateText(self.id, "Last Pickup: " .. self.playerRef.lastpickup)
end


return lpText