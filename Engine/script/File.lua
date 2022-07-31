local gameObject	= require('script/gameObject')

-- Enemies
local Monster		= require('script/Monster')
local Monkey		= require('script/ThrowingEnemy')
local Bouncy		= require('script/BasicBossEnemy')
local Shooter		= require('script/ThrowingBoss')

-- Tiles
local WallTile	= require('script/WallTile')
local DoorTile	= require('script/DoorTile')
local FloorTile = require('script/FloorTile')

-- Powerup
local Powerup		= require('script/Powerups')

-- Others
local spawnpoint	= require('script/spawnpoint')
local goalpoint		= require('script/goalpoint')

--[[LOAD TO FILE SECTION]]--

-- Load objects from a file into a table
function Load_File(path)

	local lines = Load_File_Lines(path)

	if lines == false then
		return {}
	end

	local fileObjects = {}

	local objNum = 1

	-- Divide objects into tables
	for num, line in pairs(lines) do
		
		-- current object start
		if line:find('{') then
			local object = gameObject:New()
			fileObjects[objNum] = object
		end

		if line:find('type') then Adjust_Object_Type(fileObjects, objNum, line) end
		if line:find('sprite') then Adjust_Object_Name(fileObjects, objNum, line) end
		if line:find('pos') then Adjust_Object_Pos(fileObjects, objNum, line) end
		if line:find('collision') then Adjust_Object_Collision(fileObjects, objNum, line) end
		if line:find('visible') then Adjust_Object_Visibility(fileObjects, objNum, line) end
		
		-- current object end
		if line:find('}') then
			objNum = objNum + 1
		end
	end

	return fileObjects

end

-- Load in each line from file
function Load_File_Lines(path)


	local f = io.open(path, "r+")
	if not f then return false end

	local lines = {}

	for line in f:lines() do
		lines[#lines + 1] = line
	end

	f:close()

	return lines

end


-- set the collision on the object
function Adjust_Object_Collision(objects, num, line)

	local coll = string.gsub(line, "collision=", "")

	if objects[num] ~= nil then
		objects[num]:SetCollision(tonumber(coll))
	end

end


-- set the visibility of the object
function Adjust_Object_Visibility(objects, num, line)

	local visible = string.gsub(line, "visible=", "")

	if objects[num] ~= nil then
		objects[num]:SetVisibility(tonumber(visible))
	end

end

-- set the position of the current object in file
function Adjust_Object_Pos(objects, num, line)

	-- removes the pos= from the current line
	local coordinates = string.gsub(line, "pos=", "")

	--Split the coordinates by spaces
	local vec = {}
	local substring
	for substring in coordinates:gmatch("%S+") do
	   table.insert(vec, tonumber(substring))
	end
	
	--Check that none is nil
	if (#vec == 3) then
		if (vec[1] and vec[2] and vec[3]) then	
			objects[num]:SetPosition(vec[1], vec[2], vec[3])
		else
			print("ERROR: '" .. line .. "' not correct... One of the numbers was nil")
		end
	else
		print("ERROR: '" .. line .. "' not correct... Expected: 3 numbers")
	end

end

-- create the sprite from the instructions in the loaded file
function Adjust_Object_Name(objects, num, line)

	local filepath = string.gsub(line, "sprite=", "")

	if objects[num] ~= nil then
		objects[num].id = C_LoadSprite(filepath)
		objects[num].defaultsprite = filepath
	end

end

-- create the specific type of object in the table of objects
function Adjust_Object_Type(objects, num, line)

	-- Spawn a normal following enemy
	if line:find('monster') then 
		objects[num] = Monster:New()
		objects[num].type = 'monster'

	-- Spawn a throwing stationary enemy
	elseif line:find('monkey') then
		objects[num] = Monkey:New()
		objects[num].type = 'monkey'
	
	-- Spawns a basic boss that bounces across the room
	elseif line:find('bouncy') then
		objects[num] = Bouncy:New()
		objects[num].type = 'bouncy'

	elseif line:find('wall') then
		objects[num] = WallTile:New()
		objects[num].type = 'wall'

	elseif line:find('shooter') then
		objects[num] = Shooter:New()
		objects[num].type = 'shooter'

	elseif line:find('door') then
		objects[num] = DoorTile:New()
		objects[num].type = 'door'

	elseif line:find('powerup') then
		objects[num] = Powerup:New()
		objects[num].type = 'powerup'

	elseif line:find('spawnpoint') then

		objects[num] = spawnpoint:New()
		objects[num].type = 'spawnpoint'

	elseif line:find('goalpoint') then

		objects[num] = goalpoint:New()
		objects[num].type = 'goalpoint'

	elseif line:find('floor') then
		objects[num] = FloorTile:New()
		objects[num].type = 'floor'
	end

end

--[[LOAD TO FILE SECTION]]--


--[[WRITE TO FILE SECTION]]--

-- Writes each relevant properties of the objects in table to file located in path
function Write_To_File(objects, path)

	-- clear the file if it already exists.
	io.open(path, "w"):close()

	-- Open the file in append mode. Creates the file if it doesn't exist
	local file = io.open(path, "a")

	for num, obj in pairs(objects) do

		-- make sure the object isn't a nil value
		if obj ~= nil then
			file:write('{', "\n")
			file:write('type=' .. obj.type, "\n")
			file:write('sprite=' .. obj.defaultsprite, "\n")
			file:write('pos=' .. obj.position.x .. ' ' .. obj.position.y .. ' ' .. obj.position.z, "\n")
			file:write('visible=' .. obj.isVisible, "\n")
			file:write('collision=' .. obj.hasCollision, "\n")
			file:write('}', "\n")

			-- finishing newline between each object
			file:write("\n")
		end

	end

	file:close()

end

--[[WRITE TO FILE SECTION]]--