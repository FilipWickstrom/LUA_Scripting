require('script/vector')
gameObject = require('script/gameObject')
require('script/ProjectileHandler')
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
	instance.damage = weapons[_type].damage
	instance.fireRate = weapons[_type].fireRate
	instance.fireTimer = 0

	return instance
end

--Adds a new bullet into the bullets table and sets its props
function Weapon:Fire(spawnPos, dir, id)
	if self.fireTimer <= 0 then
		local projectile = gameObject:New()
		projectile.id = C_LoadSprite(weapons[self.type].sprite)
		projectile.position = spawnPos
		projectile.dir = dir
		projectile.speed = weapons[self.type].speed
		projectile.lifetime = weapons[self.type].lifetime
		projectile.damage = weapons[self.type].damage
		projectile.owner = id
		local rad = math.atan(projectile.dir.x, projectile.dir.z)
		local degrees = rad * 180 / math.pi
		local vec = vector:New()
		vec.y = degrees
		projectile:Rotate(vec)
		C_SetSpriteVisible(projectile.id, true)

		self.fireTimer = self.fireRate

		addProjectile(projectile)
	end
end

--This update will loop through all bullets and check its lifetime
--it will move all bullets that hasnt been removed and will check for collisions.
function Weapon:Update()
	if self.fireTimer > 0 then
		self.fireTimer = self.fireTimer - deltatime
	end
end