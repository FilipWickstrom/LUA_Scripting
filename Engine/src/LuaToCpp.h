#pragma once

/*
	Call C++ functions within LUA

	structure:
		parameter: lua_State
		return: int				- amount of results to return
*/

// Lua function to load model into c++
int LoadModelLua(lua_State* L);

// Lua function to remove model from c++
int RemoveModelLua(lua_State* L);

// Lua function to get the size of the window from c++
int GetWindowWidthLua(lua_State* L);
int GetWindowHeightLua(lua_State* L);

int UpdatePosLua(lua_State* L);

int ChangeScene(lua_State* L);

namespace GUI
{
	int AddText(lua_State* L);
	int AddButton(lua_State* L);
	int RemoveGUI(lua_State* L);
	int IsButtonPressed(lua_State* L);

};
