local weaponText = {}

function weaponText:Initialize()

	weaponText.id = C_AddText("Weapon: None", "roboto_28.xml", 220, 150, 400, 100)
	C_SetTextAlignment(weaponText.id, "left")

end

function weaponText:Update()

	-- Update the text here
	C_UpdateText(weaponText.id, 'Weapon: ' .. player.weapon.name)

end

return weaponText