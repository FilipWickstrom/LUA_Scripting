#include "PCH.h"
#include "LuaState.h"
#include "LuaToCpp.h"

LuaHandler::LuaHandler()
{
	m_state = luaL_newstate();
	luaL_openlibs(m_state);

	/*
		Sprites
	*/

	// Param: filename{string}
	// Return: id{uint}
	lua_register(m_state, "C_LoadSprite", 			L_LoadSprite);
	// Param: id{uint}
	lua_register(m_state, "C_ChangeSprite",			L_ChangeSprite);
	// Param: id{uint}
	lua_register(m_state, "C_RemoveSprite", 		L_RemoveSprite);
	// Param: id{uint}, isVisible{bool}
	lua_register(m_state, "C_SetSpriteVisible",		L_SetSpriteVisible);
	// Param: id{uint}, x{float}, y{float}, z{float}
	lua_register(m_state, "C_SetSpritePosition", 	L_SetSpritePosition);
	// Param: id{uint}, scaling{float}
	lua_register(m_state, "C_SetSpriteScale", 		L_SetSpriteScale);
	// Param: id{uint}, x{float}, y{float}, z{float}
	lua_register(m_state, "C_SetSpriteRotation", 	L_SetSpriteRotation);
	// Param: id1{uint}, id2{uint}, direction{string}[optional]
	// Return: isColliding{bool}
	lua_register(m_state, "C_CheckSpriteCollision", L_CheckSpriteCollision);
	// Param: id1{uint}, id2{uint}
	// Return: isColliding{bool}
	lua_register(m_state, "C_CheckSpriteCircleCollision", L_CheckSpriteCircleCollision);

	/*
		Window
	*/

	// Return: width{uint}
	lua_register(m_state, "C_WinWidth", 			L_GetWindowWidth);
	// Return: height{uint}
	lua_register(m_state, "C_WinHeight", 			L_GetWindowHeight);
	
	/*
		Camera
	*/

	// Param: none
	lua_register(m_state, "C_CreateCamera",			CAM::L_CreateCamera);
	// Param: x{float}, y{float}, z{float}
	lua_register(m_state, "C_SetCameraPosition",	CAM::L_SetCameraPosition);
	// Param: x{float}, y{float}, z{float}
	lua_register(m_state, "C_SetCameraTarget",		CAM::L_SetCameraTarget);
	// Param: fov{float}
	lua_register(m_state, "C_SetCameraFOV",			CAM::L_SetCameraFOV);

	/*
		Scene
	*/

	// Param: fileToLUA_Scene{string}
	lua_register(m_state, "C_ChangeScene", 			L_ChangeScene);	
	
	/*
		GUI
	*/

	// Param: x1{float}, y1{float}, x2{float}, y2{float} 
	// Return: id{uint}
	lua_register(m_state, "C_AddHealthbar", 		L_AddHealthbarUI);
	// Param: id{uint}, health{float}
	lua_register(m_state, "C_UpdateUI", 			L_UpdateGraphicalInterface);
	// Param: id{uint}, x1{float}, y1{float}, x2{float}, y2{float} 
	lua_register(m_state, "C_UpdatePosUI", 			L_UpdatePosUI);
	// Param: id{uint}
	lua_register(m_state, "C_RemoveUI", 			L_RemoveUI);
	// Param: id{uint}, isVisible{bool}
	lua_register(m_state, "C_SetVisibleUI",			L_SetHealthbarVisibility);
	// Param: text{string}, font{string}, posX{float}, posY{float}, sizeX{float}, sizeY{float}
	// Return: id{uint}
	lua_register(m_state, "C_AddText", 				GUI::L_AddText);
	// Param: text{string}, font{string}, posX{float}, posY{float}, sizeX{float}, sizeY{float}
	// Return: id{uint}
	lua_register(m_state, "C_AddButton", 			GUI::L_AddButton);
	// Param: id{uint}
	lua_register(m_state, "C_RemoveGUI", 			GUI::L_RemoveGUI);
	// Param: id{uint}
	// Return: isPressed{bool}
	lua_register(m_state, "C_IsButtonPressed", 		GUI::L_IsButtonPressed);
	// Param: id{uint}, text{string}
	lua_register(m_state, "C_UpdateText", 			GUI::L_UpdateText);
	// Param: id{uint}, alignment{string}
	lua_register(m_state, "C_SetTextAlignment",		GUI::L_SetTextAlignment);
	// Return: posX{int}, posY{int}
	lua_register(m_state, "C_GetScreenCoords",		L_GetScreenCoords);
	// Param: keyCode{irr::EKEY_CODE}
	// Return: isKeyDown{bool}
	lua_register(m_state, "C_IsKeyDown",			L_IsKeyDown);
	// Return: posX{float}, posY{float}, posZ{float}
	lua_register(m_state, "C_GetWorldFromScreen",	L_GetWorldFromScreen);
}

LuaHandler::~LuaHandler()
{
	lua_close(m_state);
}

auto& LuaHandler::Get()
{
	static LuaHandler instance;
	return instance;
}

lua_State*& LuaHandler::GetLua()
{
	return Get().m_state;
}

void LuaHandler::DumpStack()
{
	lua_State* L = Get().m_state;

	std::cout << "------- STACK DUMP -------\n";
	for (int i = lua_gettop(L); i > 0; i--)
	{
		std::cout << "Index " << i << ": " << lua_typename(L, lua_type(L, i));
		
		//Print out more info about the data in the stack
		switch (lua_type(L, i))
		{
		case LUA_TNUMBER:
			std::cout << " '" << lua_tonumber(L, i) << "'";
			break;
		case LUA_TSTRING:
			std::cout << " '" << lua_tostring(L, i) << "'";
			break;
		case LUA_TBOOLEAN:
			std::cout << " '" << lua_toboolean(L, i) << "'";
			break;
		default:
			break;
		}
		std::cout << '\n';
	}
	std::cout << "--------------------------\n";
}

bool LuaHandler::CheckErrors(const int& nrOfArgs, const int& nrOfReturns)
{
	lua_State* L = Get().m_state;
	if (lua_pcall(L, nrOfArgs, nrOfReturns, 0) != LUA_OK)
	{
		std::cout << "LUA Error: " << lua_tostring(L, -1) << '\n';
		lua_pop(L, 1);
		return true;
	}
	return false;
}
