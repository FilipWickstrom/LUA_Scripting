
local lpText = {}

function lpText:Initialize()

	lpText.playerRef = player
	lpText.id = C_AddText("Last pickup: None")
	local id = lpText.id
	C_SetTextSize(id, 400, 50)
	C_SetTextPosition(id, 10, 225)
	C_SetTextAlignment(id, "left")

end

function lpText:Update()
	C_UpdateText(self.id, "Last Pickup: " .. self.playerRef.lastpickup)
end


return lpText