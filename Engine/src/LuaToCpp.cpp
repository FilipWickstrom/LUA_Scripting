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
	lua_pushnumber(L, Graphics::GetWindowWidth());
	return 1;
}

int GetWindowHeightLua(lua_State* L)
{
	lua_pushnumber(L, Graphics::GetWindowHeight());
	return 1;
}

int UpdatePosLua(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -3));
	float x = static_cast<float>(lua_tonumber(L, -2));
	float z = static_cast<float>(lua_tonumber(L, -1));
	//float z = static_cast<float>(lua_tonumber(L, -1));
	SceneAccess::GetSceneHandler()->GetScene()->UpdatePosition(id, { x, 0, z });

	return 0;
}

int UpdateGraphicalInterfaceLua(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
	float update = static_cast<float>(lua_tonumber(L, -1));

	Element2D* elem = Graphics2D::GetElement(id);
	if (elem)
	{
		elem->Update(&update);
	}

	return 0;
}

int AddHealthbarUILua(lua_State* L)
{
	float y2 = static_cast<float>(lua_tonumber(L, -1));
	float x2 = static_cast<float>(lua_tonumber(L, -2));
	float y = static_cast<float>(lua_tonumber(L, -3));
	float x = static_cast<float>(lua_tonumber(L, -4));

	irr::core::rect<irr::s32> rect;
	rect.LowerRightCorner	= irr::core::vector2di(static_cast<int>(x2), static_cast<int>(y2));
	rect.UpperLeftCorner	= irr::core::vector2di(static_cast<int>(x), static_cast<int>(y));

	const unsigned int ret = Graphics2D::AddHealthbar(rect);

	lua_pushnumber(L, ret);

	return 1;
}

int UpdatePosUILua(lua_State* L)
{
	/*
		Convert the 3d world position to 2d screen space position.
	*/
	float y2 = static_cast<float>(lua_tonumber(L, -1));
	float x2 = static_cast<float>(lua_tonumber(L, -2));
	float y = static_cast<float>(lua_tonumber(L, -3));
	float x = static_cast<float>(lua_tonumber(L, -4));
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -5));

	irr::core::rect<irr::s32> rect;
	irr::scene::ISceneCollisionManager* m = Graphics::GetSceneManager()->getSceneCollisionManager();
	irr::core::vector2d<irr::s32> pos = m->getScreenCoordinatesFrom3DPosition({ x, 0, y});
	rect.LowerRightCorner	= irr::core::vector2di(static_cast<int>(pos.X + x2), static_cast<int>(pos.Y + y2));
	rect.UpperLeftCorner	= irr::core::vector2di(static_cast<int>(pos.X), static_cast<int>(pos.Y));

	Graphics2D::SetPosition(id, rect);
	return 0;
}

int RemoveUILua(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
	Graphics2D::RemoveElement(id);
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
