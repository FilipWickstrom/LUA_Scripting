
local SystemDefinedGlobals = {}

-- Add all the globals that come from
function AddSystemGlobals()
	for k,v in pairs(_G) do
		--[Enabled] Prints all the globals
		--print(k)

		-- Ignore these two globals
		if (k ~= "AddSystemGlobals" and
			k ~= "PrintAllGlobals") then
			table.insert(SystemDefinedGlobals, k)
		end
	end	
end

function PrintAllGlobals()
	local total = 0
	local userDef = 0
	local systemDef = #SystemDefinedGlobals

	for k,v in pairs(_G) do
		total = total + 1
	end

	userDef = total - systemDef

	print("### Global variables ###")
	print("System:\t" .. systemDef)
	print("User:\t" .. userDef)

end
