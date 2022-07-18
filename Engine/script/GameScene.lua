--Includes
local Player			= require('script/Player')
local Camera			= require('script/Camera')
local Powerup			= require('script/Powerups')
local goldText			= require('script/GoldText')
local weaponText		= require('script/WeaponText')
local lastpickupText	= require('script/lastpickuptext')
local weaponDrops		= require('script/WeaponDrop')
require('script/AllScenes')	
require('script/File')
require('script/ProjectileHandler')


-- Globals to collect separate types in different tables
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
	camera:SetZoom(10)

	objects = Load_File('maps/test2.txt')

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

	-- Update player
	player:Update(camera, objects)
	UpdateProjectiles()

	weaponDrops:Update()
	weaponText:Update()
	goldText:Update()

	camera:UpdateZoom()
	
	-- Go back to menu when player dies
	if (not player:IsAlive()) then
		C_ChangeScene(Scenes.GAMEOVER)
	end
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