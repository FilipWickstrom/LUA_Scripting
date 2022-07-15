--Global classes
Player			= require('script/Player')
Camera			= require('script/Camera')
Powerup			= require('script/Powerups')
goldText		= require('script/GoldText')
weaponText		= require('script/WeaponText')
lastpickupText	= require('script/lastpickuptext')
require('script/AllScenes')	
require('script/File')
weaponDrops		= require('script/WeaponDrop')
require('script/ProjectileHandler')



-- Collect separate types in different tables
objects	= {}
walls	= {}
enemies	= {}

function Start()
	math.randomseed(os.time())

	--Player setup
	player = Player:New()

	powerup = Powerup:New()
	goldText:Initialize()
	weaponText:Initialize()
	weaponDrops:new()
	lastpickupText:Initialize()

	--Camera setup
	camera = Camera:New()
	camera:SetPosition(0,40,0)
	camera:SetTarget(0,0,0.1)
	camera:SetFOV(90)

	objects = Load_File('maps/test1.txt')

	-- write down file
	--Write_To_File(objects, 'maps/test1.txt')

	-- Go through all the objects
	for i = 1, #objects do
		local type = objects[i].type	

		-- Collidable tiles
		if (type == 'wall' or 
			type == 'door') then
			table.insert(walls, objects[i])
		end

		-- Adds all enemies to the enemies table
		if (type == 'bouncy'	or 
			type == 'monster' or
			type == 'shooter' or
			type == 'monkey')	then
			table.insert(enemies, objects[i])
		end
	end
end

-- Destroying everything
function Clean()

	weaponDrops:OnEnd()

	print("### Removing player ###")
	player:OnEnd()

	print("### Removing objects ###")
	for k, v in pairs(objects) do
		v:OnEnd()
	end
end

-- Game loop
function Update(dt)
	deltatime = dt
	-- Loop through all objects
	for num, obj in pairs(objects) do
		if obj ~= nil then 
			if obj.hp > 0 then
				obj:Update()
			else
				RemoveObject(num, obj)
			end
		end
	end

	-- Update powerup
	if powerup ~= nil then
		powerup:Update(objects, goldText, lastpickupText)
	end

	-- Go back to menu when player dies
	if(player:IsAlive() == false) then
		C_ChangeScene(Scenes.GAMEOVER)
	end

	-- Update player
	player:Update(camera, objects)
	UpdateProjectiles()

	weaponDrops:Update()

	weaponText:Update()
	goldText:Update()
end


function RemoveObject(num, obj)

	if obj.name == "enemy" then
		player.gold = player.gold + obj.worth
		obj:OnDeath()
	end

	table.remove(objects, num)
	C_RemoveSprite(obj.id)
	C_RemoveUI(obj.gid)

end