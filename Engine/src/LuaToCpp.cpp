#include "PCH.h"
#include "LuaToCpp.h"

int LoadModelLua(lua_State* L)
{
	std::string filepath = lua_tostring(L, -1);

	lua_pushnumber(L, SceneAccess::GetSceneHandler()->GetScene()->AddModel(filepath));
	return 1;
}

int RemoveModelLua(lua_State* L)
{
	int id = static_cast<int>(lua_tonumber(L, -1));
	SceneAccess::GetSceneHandler()->GetScene()->RemoveModel(id);
	return 0;
}

int GetWindowWidthLua(lua_State* L)
{
	lua_pushnumber(L, window_width);
	return 1;
}

int GetWindowHeightLua(lua_State* L)
{
	lua_pushnumber(L, window_height);
	return 1;
}
