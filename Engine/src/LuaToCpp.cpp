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
	rect.LowerRightCorner = irr::core::vector2di(x2, y2);
	rect.UpperLeftCorner = irr::core::vector2di(x, y);

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
	rect.LowerRightCorner = irr::core::vector2di(pos.X + x2, pos.Y + y2);
	rect.UpperLeftCorner = irr::core::vector2di(pos.X, pos.Y);

	Graphics2D::SetPosition(id, rect);
	return 0;
}

int RemoveUILua(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
	Graphics2D::RemoveElement(id);
	return 0;
}
