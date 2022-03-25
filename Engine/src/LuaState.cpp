#include "PCH.h"
#include "LuaState.h"
#include "LuaToCpp.h"

LuaHandler::LuaHandler()
{
	m_state = luaL_newstate();
	luaL_openlibs(m_state);

	//Add functions to LUA
	lua_register(m_state, "LoadModel", LoadModelLua);
	lua_register(m_state, "RemoveModel", RemoveModelLua);
	lua_register(m_state, "WinWidth", GetWindowWidthLua);
	lua_register(m_state, "WinHeight", GetWindowHeightLua);
	lua_register(m_state, "UpdatePos", UpdatePosLua);
	lua_register(m_state, "AddHealthbar", AddHealthbarUILua);
	lua_register(m_state, "UpdateUI", UpdateGraphicalInterfaceLua);
	lua_register(m_state, "UpdatePosUI", UpdatePosUILua);
	lua_register(m_state, "RemoveUI", RemoveUILua);

	lua_register(m_state, "ChangeScene", ChangeScene);

	//GUI
	lua_register(m_state, "AddText", GUI::AddText);
	lua_register(m_state, "AddButton", GUI::AddButton);
	lua_register(m_state, "RemoveGUI", GUI::RemoveGUI);
	lua_register(m_state, "IsButtonPressed", GUI::IsButtonPressed);
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
		std::cout << "Index " << i << ": " << lua_typename(L, lua_type(L, i)) << "\n";
	}
	std::cout << "--------------------------\n";
}
