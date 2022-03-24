#include "PCH.h"
#include "LuaState.h"
#include "LuaToCpp.h"

// Run the console
void ConsoleThread(lua_State* L)
{
	char command[1000];
	while (GetConsoleWindow())
	{
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

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

	m_conThread = std::thread(ConsoleThread, m_state);
}

LuaHandler::~LuaHandler()
{
	m_conThread.join();
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
