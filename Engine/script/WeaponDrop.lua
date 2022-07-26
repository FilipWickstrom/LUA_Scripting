require('script/Weapon')
gameObject = require('script/gameObject')

local weaponList = {
	[1] = "Heart",
	[2] = "Bomb",
	[3] = "Arrow"
 }

--[[

	This is a tabel that keeps tab on all the dropped weapons in the scene.

]]

weaponDrops = {}
weaponDrops.__index = weaponDrops
setmetatable(weaponDrops, self)

function weaponDrops:new()

	weaponDrops.weapons = {}
	weaponDrops.objects = {}

end

-- Create a new weapon for and drop it on the ground.
function weaponDrops:CreateWeapon(pos)

	-- Randomize a weapon pick up
	local newWeapon = self:RandomizeWeapon()

	-- Create an object in the scene to represent the weapon pickup.
	local newObject = gameObject:New()
	newObject.id = C_LoadSprite(weapons[newWeapon.type].sprite)
	newObject:SetPosition(pos.x, pos.y, pos.z)

	-- insert into tables
	table.insert(self.objects, newObject)
	table.insert(self.weapons, newWeapon)
end

-- Randomize a weapon and return it
function weaponDrops:RandomizeWeapon()

	local randomWeapon = Weapon.new(weaponList[math.random(#weaponList)])
	return randomWeapon

end

-- Update
function weaponDrops:Update()

	for num, obj in pairs(self.objects) do

		-- collision with one of the weapon pick ups in the scene.
		if C_CheckSpriteCollision(obj.id, player.id) then
			player.weapon = self.weapons[num]

			-- Update max fireRate
			C_SetHealthbarMax(player.sid, player.weapon.fireRate)
			obj:OnEnd()
			table.remove(self.objects, num)
			table.remove(self.weapons, num)
			break
		end

	end

end

function weaponDrops:OnEnd()

	for num, obj in pairs(self.objects) do
		obj:OnEnd()
	end

end


return weaponDrops