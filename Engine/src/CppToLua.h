#pragma once

//TODO Add a scope: CppToLua

/*
	Call LUA function within C++

	structure:
		Not limits
*/

// Load a script from file. Make sure its inside the "Scripts" folder.
// Returns true when loaded correctly.
bool LoadScript(const std::string& script_name);