#pragma once

/*
	Call C++ functions within LUA

	structure:
		parameter: lua_State
		return: int
*/

// Lua function to load model into c++
int LoadModelLua(lua_State* L);

// Lua function to remove model from c++
int RemoveModelLua(lua_State* L);

// Lua function to get the size of the window from c++
int GetWindowWidthLua(lua_State* L);
int GetWindowHeightLua(lua_State* L);

/*
	Add scopes for specific functions
*/
