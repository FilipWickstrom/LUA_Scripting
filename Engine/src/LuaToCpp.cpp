#include "PCH.h"
#include "LuaToCpp.h"
#include "LuaState.h"

int L_LoadSprite(lua_State* L)
{
	std::string filepath = lua_tostring(L, -1);
	lua_pushnumber(L, SceneAccess::GetSceneHandler()->GetScene()->AddSprite(filepath));
	return 1;
}

int L_ChangeSprite(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
	std::string filepath = lua_tostring(L, -1);

	SceneAccess::GetSceneHandler()->GetScene()->ChangeSprite(id, filepath);

	return 0;
}

int L_RemoveSprite(lua_State* L)
{
	if (lua_isnumber(L, -1))
	{
		int id = static_cast<int>(lua_tonumber(L, -1));
		SceneAccess::GetSceneHandler()->GetScene()->RemoveSprite(id);
	}
	return 0;
}

int L_ChangeSprite(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isstring(L, -1))
	{
		int id = static_cast<int>(lua_tonumber(L, -2));
		std::string file = lua_tostring(L, -1);
		SceneAccess::GetSceneHandler()->GetScene()->ChangeSprite(id, file);
	}
	return 0;
}

int L_SetSpriteVisible(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isboolean(L, -1))
	{
		int id = static_cast<int>(lua_tonumber(L, -2));
		bool trueOrFalse = lua_toboolean(L, -1);
		SceneAccess::GetSceneHandler()->GetScene()->SetSpriteVisible(id, trueOrFalse);
	}
	return 0;
}

int L_SetSpritePosition(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -3));
	irr::core::vector3df vec;
	vec.X = static_cast<float>(lua_tonumber(L, -2));
	//vec.Y = static_cast<float>(lua_tonumber(L, -2));
	vec.Z = static_cast<float>(lua_tonumber(L, -1));
	SceneAccess::GetSceneHandler()->GetScene()->SetSpritePosition(id, vec);
	return 0;
}

int L_SetSpriteScale(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
	float scl = static_cast<float>(lua_tonumber(L, -1));
	SceneAccess::GetSceneHandler()->GetScene()->SetSpriteScale(id, { scl, scl, scl });
	return 0;
}

int L_SetSpriteRotation(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -4));
	irr::core::vector3df vec;
	vec.X = static_cast<float>(lua_tonumber(L, -3));
	vec.Y = static_cast<float>(lua_tonumber(L, -2));
	vec.Z = static_cast<float>(lua_tonumber(L, -1));
	SceneAccess::GetSceneHandler()->GetScene()->SetSpriteRotation(id, vec);
	return 0;
}

int L_GetWindowWidth(lua_State* L)
{
	lua_pushnumber(L, Graphics::GetWindowWidth());
	return 1;
}

int L_GetWindowHeight(lua_State* L)
{
	lua_pushnumber(L, Graphics::GetWindowHeight());
	return 1;
}

int L_UpdateGraphicalInterface(lua_State* L)
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

int L_AddHealthbarUI(lua_State* L)
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

int L_UpdatePosUI(lua_State* L)
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

int L_RemoveUI(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
	Graphics2D::RemoveElement(id);
	return 0;
}

int CAM::L_CreateCamera(lua_State* L)
{
	SceneAccess::GetSceneHandler()->GetScene()->AddCamera();
	return 0;
}

int CAM::L_SetCameraPosition(lua_State* L)
{
	irr::core::vector3df vec;
	if (lua_isnumber(L, -3) &&
		lua_isnumber(L, -2) &&
		lua_isnumber(L, -1))
	{
		vec.X = static_cast<float>(lua_tonumber(L, -3));
		vec.Y = static_cast<float>(lua_tonumber(L, -2));
		vec.Z = static_cast<float>(lua_tonumber(L, -1));
		SceneAccess::GetSceneHandler()->GetScene()->SetCameraPosition(vec);
	}
	return 0;
}

int CAM::L_SetCameraTarget(lua_State* L)
{
	irr::core::vector3df vec;
	if (lua_isnumber(L, -3) &&
		lua_isnumber(L, -2) &&
		lua_isnumber(L, -1))
	{
		vec.X = static_cast<float>(lua_tonumber(L, -3));
		vec.Y = static_cast<float>(lua_tonumber(L, -2));
		vec.Z = static_cast<float>(lua_tonumber(L, -1));
		SceneAccess::GetSceneHandler()->GetScene()->SetCameraTarget(vec);
	}
	return 0;
}

int CAM::L_SetCameraFOV(lua_State* L)
{
	float fov = 0.f;
	if (lua_isnumber(L, -1))
	{
		fov = static_cast<float>(lua_tonumber(L, -1));
		SceneAccess::GetSceneHandler()->GetScene()->SetCameraFOV(fov);
	}
	return 0;
}

int L_ChangeScene(lua_State* L)
{
	if (lua_type(L, -1) == LUA_TNUMBER)
	{
		EScene scene = static_cast<EScene>(lua_tonumber(L, -1));
		lua_pop(L, -1);
		SceneAccess::GetSceneHandler()->SetScene(scene);
	}
	return 0;
}

int GUI::L_AddText(lua_State* L)
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

int GUI::L_UpdateText(lua_State* L)
{
	std::string text = "";
	unsigned int id = 0;

	if (lua_type(L, -2) == LUA_TNUMBER)
		id = static_cast<unsigned int>(lua_tonumber(L, -2));

	if (lua_type(L, -1) == LUA_TSTRING)
		text = lua_tostring(L, -1);



	SceneAccess::GetSceneHandler()->GetScene()->UpdateText(id, text);

	return 0;
}

int GUI::L_SetTextAlignment(lua_State* L)
{
	std::string text = "";
	unsigned int id = 0;

	if (lua_isnumber(L, -2) && lua_isstring(L,-1))
	{
		id = static_cast<unsigned int>(lua_tonumber(L, -2));
		text = lua_tostring(L, -1);

		irr::gui::EGUI_ALIGNMENT alignment;

		if (text == "center")
		{
			alignment = irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER;
		}
		else if (text == "left")
		{
			alignment = irr::gui::EGUI_ALIGNMENT::EGUIA_UPPERLEFT;
		}
		else if (text == "right")
		{
			alignment = irr::gui::EGUI_ALIGNMENT::EGUIA_LOWERRIGHT;
		}
		else
		{
			//Default
			alignment = irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER;
		}
		SceneAccess::GetSceneHandler()->GetScene()->SetTextAlignment(id, alignment);
	}

	return 0;
}

int GUI::L_AddButton(lua_State* L)
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

int GUI::L_RemoveGUI(lua_State* L)
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

int GUI::L_IsButtonPressed(lua_State* L)
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
