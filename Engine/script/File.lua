Monster = require('script/Monster')
Monkey = require('script/ThrowingEnemy')
gameObject = require('script/gameObject')
Bouncy = require('script/BasicBossEnemy')

-- Load objects from a file into a table
function Load_File(path)

	local lines = Load_File_Lines(path)
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

end


-- set the visibility of the object
function Adjust_Object_Visibility(objects, num, line)

end

-- set the position of the current object in file
function Adjust_Object_Pos(objects, num, line)

	-- removes the pos= from the current line
	local filepath = string.gsub(line, "pos=", "")

	local x, y = string.match(filepath, '(%d+)%s(%d+)')

	-- check if x and y is properly present in the text file
	if x ~= nil and y ~= nil then
		objects[num].position.x = tonumber(x)
		objects[num].position.y = tonumber(y)
	end

end

-- create the sprite from the instructions in the loaded file
function Adjust_Object_Name(objects, num, line)

	local filepath = string.gsub(line, "sprite=", "")

	objects[num].id = C_LoadSprite(filepath)

end

-- create the specific type of object in the table of objects
function Adjust_Object_Type(objects, num, line)

	-- Spawn a normal following enemy
	if line:find('monster') then 
		objects[num] = Monster:New()
	end

	-- Spawn a throwing stationary enemy
	if line:find('monkey') then
		objects[num] = Monkey:New()
	end

	-- Spawns a basic boss that bounces across the room
	if line:find('bouncy') then
		objects[num] = Bouncy:New()
	end

end