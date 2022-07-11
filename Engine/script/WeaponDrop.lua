weapon = require('script/Weapon')

local weaponList = {
	[1] = "Heart",
	[2] = "Bomb",
	[3] = "Arrow"
 }

--[[

	This is a tabel that keeps tab on all the dropped weapons in the scene.

]]

weaponDrops = {}

function weaponDrops:new()

	weaponDrops.weapons = {}

end

-- Create a new weapon for and drop it on the ground.
function weaponDrops:CreateWeapon()

	local newWeapon = self:RandomizeWeapon()
	table.insert(self.weapons, newWeapon)

end

-- Randomize a weapon and return it
function weaponDrops:RandomizeWeapon()

	local randomWeapon = weapons[weaponList[math.random(#weaponList)]]

	return randomWeapon

end

-- Update
function weaponDrops:Update()

	

end


return weaponDrops