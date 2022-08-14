local weaponText = {}

function weaponText:Initialize()

	weaponText.id = C_AddText("Weapon: longname")
	local id = weaponText.id
	C_SetTextSize(id, 400, 50)
	C_SetTextPosition(id, 10, 150)
	C_SetTextAlignment(weaponText.id, "left")

end

function weaponText:Update()

	-- Update the text here
	C_UpdateText(weaponText.id, 'Weapon: ' .. player.weapon.name)

end

return weaponText