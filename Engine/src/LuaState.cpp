#include "PCH.h"
#include "LuaState.h"
#include "LuaToCpp.h"

LuaHandler::LuaHandler()
{
	m_state = luaL_newstate();
	luaL_openlibs(m_state);

	//Add functions to LUA
	lua_register(m_state, "C_LoadSprite", 			L_LoadSprite);
	lua_register(m_state, "C_ChangeSprite",			L_ChangeSprite);
	lua_register(m_state, "C_RemoveSprite", 		L_RemoveSprite);
	lua_register(m_state, "C_SetSpritePosition", 	L_SetSpritePosition);
	lua_register(m_state, "C_SetSpriteScale", 		L_SetSpriteScale);
	lua_register(m_state, "C_SetSpriteRotation", 	L_SetSpriteRotation);

	lua_register(m_state, "C_WinWidth", 			L_GetWindowWidth);
	lua_register(m_state, "C_WinHeight", 			L_GetWindowHeight);
	
	lua_register(m_state, "C_CreateCamera",			CAM::L_CreateCamera);
	lua_register(m_state, "C_SetCameraPosition",	CAM::L_SetCameraPosition);
	lua_register(m_state, "C_SetCameraTarget",		CAM::L_SetCameraTarget);
	lua_register(m_state, "C_SetCameraFOV",			CAM::L_SetCameraFOV);

	lua_register(m_state, "C_ChangeScene", 			L_ChangeScene);	
	
	//GUI
	lua_register(m_state, "C_AddHealthbar", 		L_AddHealthbarUI);
	lua_register(m_state, "C_UpdateUI", 			L_UpdateGraphicalInterface);
	lua_register(m_state, "C_UpdatePosUI", 			L_UpdatePosUI);
	lua_register(m_state, "C_RemoveUI", 			L_RemoveUI);
	
	lua_register(m_state, "C_AddText", 				GUI::L_AddText);
	lua_register(m_state, "C_AddButton", 			GUI::L_AddButton);
	lua_register(m_state, "C_RemoveGUI", 			GUI::L_RemoveGUI);
	lua_register(m_state, "C_IsButtonPressed", 		GUI::L_IsButtonPressed);
	lua_register(m_state, "C_UpdateText", 			GUI::L_UpdateText);
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
