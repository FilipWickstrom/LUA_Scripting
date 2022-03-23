#pragma once

//TODO Add a scope: CppToLua

/*
	Call LUA function within C++

	structure:
		Not limits
*/

// Load a script from file. Make sure its inside the "Scripts" Folder
void LoadScript(const std::string& script_name);