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

local currentMap = "Level1.map"


function Start()
	math.randomseed(os.time())

	-- Globals to collect separate types in different tables
	objects	= {}
	walls	= {}
	enemies	= {}

	--Player setup
	player = Player:New()

	goldText:Initialize()
	weaponText:Initialize()
	lastpickupText:Initialize()
	weaponDrops:new()

	C_ToggleRenderUI(true)

	objects = Load_Map(currentMap)

	-- Go through all the objects
	for i = 1, #objects do
		local type = objects[i].type	

		if (type == 'spawnpoint') then
			local pos = objects[i].position
			player:SetPosition(pos.x, player.position.y, pos.z)

		-- Collidable tiles
		elseif (type == 'wall' or 
				type == 'door') then
				table.insert(walls, objects[i])

		-- Adds all enemies to the enemies table
		elseif (type == 'bouncy'  or 
				type == 'monster' or
				type == 'shooter' or
				type == 'monkey') then
				table.insert(enemies, objects[i])
		
		end
	end

	--Camera setup
	camera = Camera:New()
	camera:SetPosition(player.position.x, player.position.z)
	camera:SetZoom(5)

end

-- Game loop
function Update(dt)
	-- Go back to menu when player dies
	if(player:IsAlive() == false) then
		C_ChangeScene(Scenes.GAMEOVER)
		return
	end

	weaponText:Update()
	goldText:Update()

	deltatime = dt
	-- Loop through all objects
	for num, obj in pairs(objects) do
		if obj ~= nil then 
			if obj.hp > 0 and obj.type ~= 'powerup' then
				obj:Update()
			elseif obj.hp > 0 and obj.type == 'powerup' then
				obj:Update(objects, goldText, lastpickupText)
			else
				RemoveObject(num, obj)
			end
		end
	end

	-- Update player
	player:Update()
	UpdateProjectiles()

	weaponDrops:Update()

	camera:SetPosition(player.position.x, player.position.z)
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