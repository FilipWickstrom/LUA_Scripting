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
}

LuaHandler::~LuaHandler()
{
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
