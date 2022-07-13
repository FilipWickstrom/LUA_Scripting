require('script/vector')
gameObject = require('script/gameObject')
Weapon = {}
local MetaWeapon = {}
MetaWeapon.__index = Weapon

--Provide a weapon type from the templated list in Utility.lua to be
--able to create new weapons
function Weapon.new(_type)
	assert(type(_type) == "string", "Weapon 'type' provided is not a string!")
	assert(weapons[_type] ~= nil, "Weapon type of: " .. _type .. " does not exist!")
	local instance = setmetatable({}, MetaWeapon)
	instance.type = _type
	instance.name = weapons[_type].name
	instance.bullets = {}
	instance.damage = weapons[_type].damage
	instance.fireRate = weapons[_type].fireRate
	instance.fireTimer = 0

	return instance
end

--Adds a new bullet into the bullets table and sets its props
function Weapon:Fire(spawnPos, dir)
	if self.fireTimer <= 0 then
		g = gameObject:New()
		g.id = C_LoadSprite(weapons[self.type].sprite)
		g.position = spawnPos
		g.dir = dir
		g.speed = weapons[self.type].speed
		g.lifetime = weapons[self.type].lifetime
		C_SetSpriteVisible(g.id, true)
		table.insert(self.bullets, g)

		self.fireTimer = self.fireRate
	end
end

--This update will loop through all bullets and check its lifetime
--it will move all bullets that hasnt been removed and will check for collisions.
function Weapon:Update(enemies)
	for i, bullet in ipairs(self.bullets) do
		removed = false
		if bullet.lifetime <= 0 then
			bullet:OnEnd()
			table.remove(self.bullets, i)
			removed = true
		end
		if not removed then
			bullet:Move(bullet.dir)
			bullet.lifetime = bullet.lifetime - deltatime
			--for j, enemy in ipairs(enemies) do
			--	if C_CheckSpriteCollision(bullet.id, enemy.id) and enemy.hp > 0 then
			--		enemy.hp = enemy.hp - self.damage
			--		bullet:OnEnd()
			--		table.remove(self.bullets, i)
			--	end
			--end
		end
	end

	if self.fireTimer > 0 then
		self.fireTimer = self.fireTimer - deltatime
	end
end