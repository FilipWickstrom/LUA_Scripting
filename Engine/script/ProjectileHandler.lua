local projectiles = {}

function addProjectile(projectile)
	if(getmetatable(projectile) ~= gameObject) then
		error("Error: parameter is not a gameobject!")
		return
	end

	table.insert(projectiles, projectile)
end

function UpdateProjectiles()
	for i, bullet in ipairs(projectiles) do
		bullet:Move(bullet.dir)
		remove = false

		if bullet.owner ~= player.id then
			if C_CheckSpriteCollision(bullet.id, player.id) then
				player.hp = player.hp - bullet.damage
				remove = true
			end
		else
			for j, enemy in ipairs(enemies) do
				if C_CheckSpriteCollision(bullet.id, enemy.id) and enemy.hp > 0 then
					enemy.hp = enemy.hp - bullet.damage
					remove = true
					break
				end
			end
		end

		bullet.lifetime = bullet.lifetime - deltatime

		if bullet.lifetime <= 0 then
			remove = true
		end

		if remove == true then
			bullet:OnEnd()
			table.remove(projectiles, i)
		end
	end
end