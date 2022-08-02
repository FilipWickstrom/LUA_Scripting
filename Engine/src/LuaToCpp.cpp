#include "PCH.h"
#include "LuaToCpp.h"
#include "LuaState.h"

int L_LoadSprite(lua_State* L)
{
	if (lua_isstring(L, -1))
	{
		std::string filepath = lua_tostring(L, -1);
		lua_pushnumber(L, SceneHandler::AddSprite(filepath));
	}
	return 1;
}

int L_RemoveSprite(lua_State* L)
{
	if (lua_isnumber(L, -1))
	{
		int id = static_cast<int>(lua_tonumber(L, -1));
		SceneHandler::RemoveSprite(id);
	}
	return 0;
}

int L_ChangeSprite(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isstring(L, -1))
	{
		int id = static_cast<int>(lua_tonumber(L, -2));
		std::string file = lua_tostring(L, -1);
		SceneHandler::ChangeSprite(id, file);
	}
	return 0;
}

int L_SetSpriteVisible(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isboolean(L, -1))
	{
		int id = static_cast<int>(lua_tonumber(L, -2));
		bool trueOrFalse = lua_toboolean(L, -1);

		SceneHandler::SetSpriteVisible(id, trueOrFalse);
	}
	return 0;
}

int L_SetSpritePosition(lua_State* L)
{
	if (lua_isnumber(L, -4) && lua_isnumber(L, -3) &&
		lua_isnumber(L, -2) && lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -4));
		irr::core::vector3df vec;
		vec.X = static_cast<float>(lua_tonumber(L, -3));
		vec.Y = static_cast<float>(lua_tonumber(L, -2));
		vec.Z = static_cast<float>(lua_tonumber(L, -1));
		SceneHandler::SetSpritePosition(id, vec);
	}
	return 0;
}

int L_SetSpriteScale(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
		float scl = static_cast<float>(lua_tonumber(L, -1));
		SceneHandler::SetSpriteScale(id, { scl, scl, scl });
	}
	return 0;
}

int L_SetSpriteRotation(lua_State* L)
{
	if (lua_isnumber(L, -4) && lua_isnumber(L, -3) &&
		lua_isnumber(L, -2) && lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -4));
		irr::core::vector3df vec;
		vec.X = static_cast<float>(lua_tonumber(L, -3));
		vec.Y = static_cast<float>(lua_tonumber(L, -2));
		vec.Z = static_cast<float>(lua_tonumber(L, -1));
		SceneHandler::SetSpriteRotation(id, vec);
	}
	return 0;
}

int L_CheckSpriteCollision(lua_State* L)
{
	// C_CheckSpriteCollision(id1, id2) 
	// Defaults to AABB collision
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		unsigned int id1 = static_cast<unsigned int>(lua_tonumber(L, -2));
		unsigned int id2 = static_cast<unsigned int>(lua_tonumber(L, -1));
		bool collided = SceneHandler::SpriteCollisionAABB(id1, id2);
		lua_pushboolean(L, collided);
	}
	// C_CheckSpriteCollision(id1, id2, "AABB")
	// C_CheckSpriteCollision(id1, id2, "circle")
	else if (lua_isstring(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3))
	{
		unsigned int id1 = static_cast<unsigned int>(lua_tonumber(L, -3));
		unsigned int id2 = static_cast<unsigned int>(lua_tonumber(L, -2));
		std::string type = lua_tostring(L, -1);

		bool collided = false;
		if (type == "AABB")
		{
			collided = SceneHandler::SpriteCollisionAABB(id1, id2);
		}
		else if (type == "circle")
		{
			collided = SceneHandler::SpriteCollisionCircle(id1, id2);
		}
		lua_pushboolean(L, collided);
	}
	// Wrong arguments
	else
	{
		lua_pushboolean(L, false);
	}

	return 1;
}

int L_SetSpriteCollision(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isboolean(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
		const bool trueorfalse = static_cast<bool>(lua_toboolean(L, -1));
		SceneHandler::SetHasCollision(id, trueorfalse);
	}
	return 0;
}

int L_SetColliderSize(lua_State* L)
{
	if (lua_isnumber(L, -3) && 
		lua_isnumber(L, -2) &&
		lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -3));
		float width = static_cast<float>(lua_tonumber(L, -2));
		float height = static_cast<float>(lua_tonumber(L, -1));
		SceneHandler::SetColliderSize(id, width, height);
	}
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
	float y2 = static_cast<float>(lua_tonumber(L, -2));
	float x2 = static_cast<float>(lua_tonumber(L, -3));
	float y = static_cast<float>(lua_tonumber(L, -4));
	float x = static_cast<float>(lua_tonumber(L, -5));
	float maxHp = 100.0f;

	// Checks if maxHp is entered into the function, and sets it accordingly.
	if (lua_isnumber(L, -5))
	{
		maxHp = static_cast<float>(lua_tonumber(L, -1));
	}

	irr::core::rect<irr::s32> rect;
	rect.LowerRightCorner = irr::core::vector2di(static_cast<int>(x2), static_cast<int>(y2));
	rect.UpperLeftCorner = irr::core::vector2di(static_cast<int>(x), static_cast<int>(y));

	const unsigned int ret = Graphics2D::AddHealthbar(rect);
	dynamic_cast<Healthbar*>(Graphics2D::GetElement(ret))->SetMaxHealth(maxHp);

	lua_pushnumber(L, ret);

	return 1;
}

int L_SetHealthbarMax(lua_State* L)
{

	float maxHp = 100;
	unsigned int id = 0;

	if (lua_isnumber(L, -1))
		maxHp = static_cast<float>(lua_tonumber(L, -1));

	if (lua_isnumber(L, -2))
		id = static_cast<unsigned int>(lua_tonumber(L, -2));

	Element2D* elem = Graphics2D::GetElement(id);

	if (elem)
	{
		dynamic_cast<Healthbar*>(elem)->SetMaxHealth(maxHp);
	}

	return 0;
}

int L_SetHealthbarBackgroundColor(lua_State* L)
{
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
	unsigned int id = 0;

	b = static_cast<unsigned int>(lua_tonumber(L, -1));
	g = static_cast<unsigned int>(lua_tonumber(L, -2));
	r = static_cast<unsigned int>(lua_tonumber(L, -3));
	id = static_cast<unsigned int>(lua_tonumber(L, -4));

	Element2D* elem = Graphics2D::GetElement(id);

	if (elem)
	{
		const irr::video::SColor color = irr::video::SColor(255, r, g, b);
		dynamic_cast<Healthbar*>(elem)->SetBackgroundColor(color);
	}

	return 0;
}

int L_SetHealthbarForegroundColor(lua_State* L)
{
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
	unsigned int id = 0;

	b = static_cast<unsigned int>(lua_tonumber(L, -1));
	g = static_cast<unsigned int>(lua_tonumber(L, -2));
	r = static_cast<unsigned int>(lua_tonumber(L, -3));
	id = static_cast<unsigned int>(lua_tonumber(L, -4));

	Element2D* elem = Graphics2D::GetElement(id);

	if (elem)
	{
		const irr::video::SColor color = irr::video::SColor(255, r, g, b);
		dynamic_cast<Healthbar*>(elem)->SetForegroundColor(color);
	}

	return 0;
}

int L_SetHealthbarVisibility(lua_State* L)
{

	const unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
	const bool visible = lua_toboolean(L, -1);

	if (Graphics2D::GetElement(id))
		Graphics2D::GetElement(id)->SetVisibility(visible);

	return 0;
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
	irr::core::vector2d<irr::s32> pos = m->getScreenCoordinatesFrom3DPosition({ x, 0, y });
	rect.LowerRightCorner = irr::core::vector2di(static_cast<int>(pos.X + x2 * 0.5f), static_cast<int>(pos.Y + y2 * 1.5f));
	rect.UpperLeftCorner = irr::core::vector2di(static_cast<int>(pos.X - x2 * 0.5f), static_cast<int>(pos.Y + y2 * 1.f));

	Graphics2D::SetPosition(id, rect);
	return 0;
}

int L_RemoveUI(lua_State* L)
{
	if (lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
		Graphics2D::RemoveElement(id);
	}
	return 0;
}

int L_ToggleRenderUI(lua_State* L)
{
	bool shouldRender = true;

	if (lua_isboolean(L, -1))
		shouldRender = lua_toboolean(L, -1);

	Graphics2D::ToggleRender(shouldRender);

	return 0;
}

int CAM::L_CreateCamera(lua_State* L)
{
	SceneHandler::AddCamera();
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
		SceneHandler::SetCameraPosition(vec);
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
		SceneHandler::SetCameraTarget(vec);
	}
	return 0;
}

int CAM::L_SetCameraZoom(lua_State* L)
{
	float zoom = 1.f;
	if (lua_isnumber(L, -1))
	{
		zoom = static_cast<float>(lua_tonumber(L, -1));
		SceneHandler::SetCameraZoom(zoom);
	}
	return 0;
}

int L_ChangeScene(lua_State* L)
{
	if (lua_isstring(L, -1))
	{
		std::string file = lua_tostring(L, -1);
		SceneHandler::ChangeScene(file);
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

	unsigned int id = SceneHandler::AddText(text, fontfile, pos, size);

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



	SceneHandler::UpdateText(id, text);

	return 0;
}

int GUI::L_SetTextAlignment(lua_State* L)
{
	std::string text = "";
	unsigned int id = 0;

	if (lua_isnumber(L, -2) && lua_isstring(L, -1))
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
		SceneHandler::SetTextAlignment(id, alignment);
	}
	return 0;
}

int GUI::L_Add2dImage(lua_State* L)
{
	std::string filepath;
	unsigned int id = 0;

	if (lua_isstring(L, -1))
	{
		filepath = lua_tostring(L, -1);
		id = SceneHandler::AddImage2d(filepath);
	}
	lua_pushnumber(L, id);

	return 1;
}

int GUI::L_RemoveImage2d(lua_State* L)
{
	if (lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
		SceneHandler::RemoveImage2d(id);
	}
	return 0;
}

int GUI::L_SetImage2dPosition(lua_State* L)
{
	if (lua_isnumber(L, -1) && 
		lua_isnumber(L, -2) && 
		lua_isnumber(L, -3))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -3));
		irr::core::vector2di pos;
		pos.X = static_cast<int>(lua_tonumber(L, -2));
		pos.Y = static_cast<int>(lua_tonumber(L, -1));
		SceneHandler::SetImage2dPosition(id, pos);
	}
	return 0;
}

int GUI::L_Change2dImage(lua_State* L)
{
	if (lua_isnumber(L, -2) && lua_isstring(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
		std::string filepath = static_cast<std::string>(lua_tostring(L, -1));
		SceneHandler::ChangeImage2d(id, filepath);
	}
	return 0;
}

int GUI::L_SetImage2dScale(lua_State* L)
{
	if (lua_isnumber(L, -1) &&
		lua_isnumber(L, -2))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -2));
		float size = static_cast<float>(lua_tonumber(L, -1));
		SceneHandler::SetImage2dScale(id, size);
	}
	return 0;
}

int L_GetScreenCoords(lua_State* L)
{
	/*
		Arguments: None
		Return: Pos[vector2di]
	*/

	irr::core::vector2di screenPos = Input::GetInputHandler().MouseState.pos;
	lua_pushnumber(L, screenPos.X);
	lua_pushnumber(L, screenPos.Y);

	return 2;
}

int L_GetWorldCoords(lua_State* L)
{
	/*
		Arguments: None
		Return: Pos[vector3df]
	*/

	irr::core::vector3df worldPos = SceneHandler::GetWorldCoordFromScreen();
	lua_pushnumber(L, worldPos.X);
	lua_pushnumber(L, worldPos.Y);
	lua_pushnumber(L, worldPos.Z);

	return 3;
}

int L_IsKeyDown(lua_State* L)
{
	bool isKeyDown = false;

	if (lua_type(L, -1) == LUA_TNUMBER)
	{
		irr::EKEY_CODE key = static_cast<irr::EKEY_CODE>((int)lua_tonumber(L, -1));

		isKeyDown = Input::IsKeyDown(key);
	}

	lua_pushboolean(L, isKeyDown);

	return 1;
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

	unsigned int id = SceneHandler::AddButton(text, fontfile, pos, size);

	//Return the id to LUA
	lua_pushnumber(L, id);
	return 1;
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
		isPressed = SceneHandler::IsButtonPressed(id);
	}

	lua_pushboolean(L, isPressed);
	return 1;
}

int GUI::L_RemoveButton(lua_State* L)
{
	if (lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
		SceneHandler::RemoveButton(id);
	}
	return 0;
}

int L_AddGridsystem(lua_State* L)
{
	irr::core::vector2di size;
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		size.X = static_cast<unsigned int>(std::abs(lua_tonumber(L, -2)));
		size.Y = static_cast<unsigned int>(std::abs(lua_tonumber(L, -1)));
		SceneHandler::AddGridSystem(size);
	}

	return 0;
}

int L_IsTileOccupied(lua_State* L)
{
	bool success = false;
	if (SceneHandler::GetGridsystem())
	{
		irr::core::vector3di vec;
		success = SceneHandler::GetGridsystem()->IsTileOccupied(vec);
	}
	lua_pushboolean(L, success);
	return 1;
}

int L_AddTile(lua_State* L)
{
	bool success = false;

	if (lua_isnumber(L, 1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, 1));
		if (SceneHandler::GetGridsystem())
		{
			// Position vector
			// Example: C_AddTile(id, pos.x, pos.y, pos.z)
			if (lua_isnumber(L, 2) && 
				lua_isnumber(L, 3) &&
				lua_isnumber(L, 4))
			{
				irr::core::vector3df vec;
				vec.X = static_cast<float>(lua_tonumber(L, 2));
				vec.Y = static_cast<float>(lua_tonumber(L, 3));
				vec.Z = static_cast<float>(lua_tonumber(L, 4));

				if (SceneHandler::GetGridsystem()->AddTile(id, vec))
					success = true;
			}
			// Defaults to mouse position
			// Example: C_AddTile(id)
			else
			{
				// Return true if we could place tile
				if (SceneHandler::GetGridsystem()->AddTileAtMouse(id))
					success = true;
			}
		}
	}

	lua_pushboolean(L, success);
	return 1;
}

int L_RemoveTile(lua_State* L)
{
	int id = -1;
	if (SceneHandler::GetGridsystem())
	{
		id = SceneHandler::GetGridsystem()->RemoveTile();
	}
	lua_pushnumber(L, id);
	return 1;
}

int L_GetTilePos(lua_State* L)
{
	irr::core::vector3df vec(0, -1000, 0);

	if (lua_isnumber(L, -1))
	{
		unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));
		if (SceneHandler::GetGridsystem())
		{
			vec = SceneHandler::GetGridsystem()->GetTilePosition(id);
		}
	}

	lua_pushnumber(L, vec.X);
	lua_pushnumber(L, vec.Y);
	lua_pushnumber(L, vec.Z);
	return 3;
}

int L_ResetGridsystem(lua_State* L)
{
	if (SceneHandler::GetGridsystem())
	{
		SceneHandler::GetGridsystem()->ResetGrid();
	}
	return 0;
}

int L_GetScreenFromWorld(lua_State* L)
{
	unsigned int id = static_cast<unsigned int>(lua_tonumber(L, -1));

	Sprite* sprite = SceneHandler::GetSprite(id);
	if (sprite)
	{
		irr::core::vector2di pos = Graphics::GetSceneManager()->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(sprite->GetPosition());
		//irr::core::vector3df pos = sprite->GetPosition();
		//irr::core::matrix4 posMatrix = SceneHandler::GetCamera()->getViewMatrix();
		//posMatrix.transformVect(pos);
		//posMatrix = SceneHandler::GetCamera()->getProjectionMatrix();
		//posMatrix.transformVect(pos);
		//
		//float x = (((pos.X + 1) * (Graphics::GetWindowWidth())) / (2.0f));
		//float y = Graphics::GetWindowHeight() - (((pos.Y + 1) * Graphics::GetWindowHeight()) / (2.0f));

		lua_pushnumber(L, pos.X);
		lua_pushnumber(L, pos.Y);

		return 2;
	}

	float x = 1.0f;
	float y = 1.0f;

	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	return 2;
}

int L_SetGridLayer(lua_State* L)
{
	if (lua_isnumber(L, -1))
	{
		if (SceneHandler::GetGridsystem())
		{
			int layer = static_cast<int>(lua_tonumber(L, -1));
			SceneHandler::GetGridsystem()->ChangeLayer(layer);
		}
	}
	return 0;
}

int L_GridUpdateHover(lua_State* L)
{
	if (SceneHandler::GetGridsystem())
	{
		SceneHandler::GetGridsystem()->UpdateHoverEffect();
	}
	return 0;
}
