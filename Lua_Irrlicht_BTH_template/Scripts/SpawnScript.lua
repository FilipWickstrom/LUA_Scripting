-- I thought that we could use a separate script to just simply use as a 
-- spawner for monsters and the like.

function SpawnPlayer()
	local player = require('Player.lua')
	return player
end

function SpawnEnemy()
	local new_enemy = require('Monster.lua')
	return new_enemy
end

function SpawnEnemy(x, y)
	local new_enemy = require('Monster.lua')
	new_enemy:setPosition(x, y)
	return new_enemy
end


