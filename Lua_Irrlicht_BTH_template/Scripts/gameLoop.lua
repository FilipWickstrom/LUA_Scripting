player = require('Player')
require('Monster')

-- Update function for lua. return 0 if nothing happend, 1 if player died.
function Update()
	if player:getHealth() <= 0 then
		return 1
	end
	return 0
end