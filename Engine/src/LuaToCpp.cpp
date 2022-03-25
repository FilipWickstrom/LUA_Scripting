#include "PCH.h"
#include "LuaToCpp.h"
#include "LuaState.h"

int LoadModelLua(lua_State* L)
{
	std::string filepath = lua_tostring(L, -1);

	lua_pushnumber(L, SceneAccess::GetSceneHandler()->GetScene()->AddModel(filepath));
	//std::cout << "ID: " << lua_tostring(L, -1) << "\n";
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

int UpdatePosLua(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -3));
	float x = static_cast<float>(lua_tonumber(L, -2));
	float z = static_cast<float>(lua_tonumber(L, -1));

	SceneAccess::GetSceneHandler()->GetScene()->UpdatePosition(id, { x, 0.f, z });
	return 0;
}
