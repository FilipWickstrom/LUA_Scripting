function Load_File(path, objects)

	local lines = Load_File_Lines(path)

	for num, line in pairs(lines) do
		print(line)
	end

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