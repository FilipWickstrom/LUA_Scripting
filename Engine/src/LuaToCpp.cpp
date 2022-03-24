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
	float y = static_cast<float>(lua_tonumber(L, -1));
	//float z = static_cast<float>(lua_tonumber(L, -1));
	SceneAccess::GetSceneHandler()->GetScene()->UpdatePosition(id, { x, 0, y });
	return 0;
}

int ChangeScene(lua_State* L)
{
	if (lua_type(L, -1) == LUA_TNUMBER)
	{
		EScene scene = static_cast<EScene>(lua_tonumber(L, -1));
		lua_pop(L, -1);
		SceneAccess::GetSceneHandler()->SetScene(scene);
	}
	return 0;
}

int GUI::AddText(lua_State* L)
{
	/*
		Arguments:	Text[string], Font[string], Pos[vector2di], Size[vector2di]
		Return:		ID[int]
	*/

	//Default values
	std::string text			= "";
	std::string fontfile		= "";
	irr::core::vector2di pos	= { 0,0 };
	irr::core::vector2di size	= { 100,50 };

	// Get the data from LUA-stack
	if (lua_type(L, -6) == LUA_TSTRING)
		text = lua_tostring(L, -6);
	if (lua_type(L, -5) == LUA_TSTRING)
		fontfile = lua_tostring(L, -5);
	if (lua_type(L, -4) == LUA_TNUMBER)
		pos.X = static_cast<int>(lua_tonumber(L, -4));
	if (lua_type(L, -3) == LUA_TNUMBER)
		pos.Y = static_cast<int>(lua_tonumber(L, -3));
	if (lua_type(L, -2) == LUA_TNUMBER)
		size.X = static_cast<int>(lua_tonumber(L, -2));
	if (lua_type(L, -1) == LUA_TNUMBER)
		size.Y = static_cast<int>(lua_tonumber(L, -1));

	unsigned int id = SceneAccess::GetSceneHandler()->GetScene()->AddText(text, fontfile, pos, size);

	//Return the id to LUA
	lua_pushnumber(L, id);
	return 1;
}

int GUI::AddButton(lua_State* L)
{
	/*
		Arguments:	Text[string], Font[string], Pos[vector2di], Size[vector2di]
		Return:		ID[int]
	*/

	//Default values
	std::string text = "";
	std::string fontfile = "";
	irr::core::vector2di pos = { 0,0 };
	irr::core::vector2di size = { 100,50 };

	// Get the data from LUA-stack
	if (lua_type(L, -6) == LUA_TSTRING)
		text = lua_tostring(L, -6);
	if (lua_type(L, -5) == LUA_TSTRING)
		fontfile = lua_tostring(L, -5);
	if (lua_type(L, -4) == LUA_TNUMBER)
		pos.X = static_cast<int>(lua_tonumber(L, -4));
	if (lua_type(L, -3) == LUA_TNUMBER)
		pos.Y = static_cast<int>(lua_tonumber(L, -3));
	if (lua_type(L, -2) == LUA_TNUMBER)
		size.X = static_cast<int>(lua_tonumber(L, -2));
	if (lua_type(L, -1) == LUA_TNUMBER)
		size.Y = static_cast<int>(lua_tonumber(L, -1));

	unsigned int id = SceneAccess::GetSceneHandler()->GetScene()->AddButton(text, fontfile, pos, size);

	//Return the id to LUA
	lua_pushnumber(L, id);
	return 1;
}

int GUI::RemoveGUI(lua_State* L)
{
	/*
		Arguments: ID[unsigned int]
	*/
	if (lua_type(L, -1) == LUA_TNUMBER)
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
		SceneAccess::GetSceneHandler()->GetScene()->RemoveGUI(id);
	}
	return 0;
}

int GUI::IsButtonPressed(lua_State* L)
{
	/*
		Arguments: ID[unsigned int]
	*/
	bool isPressed = false;
	if (lua_type(L, -1) == LUA_TNUMBER)
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
		isPressed = SceneAccess::GetSceneHandler()->GetScene()->IsButtonPressed(id);
	}
	
	lua_pushboolean(L, isPressed);
	return 1;
}
