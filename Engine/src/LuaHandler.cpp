#include "PCH.h"
#include "LuaHandler.h"

void DumpStack(lua_State* L)
{
	std::cout << "------- STACK DUMP -------\n";
	for (int i = lua_gettop(L); i > 0; i--)
	{
		std::cout << "Index " << i << ": " << lua_typename(L, lua_type(L, i)) << "\n";
	}
	std::cout << "--------------------------\n";
}

void ConsoleThread(lua_State* L) {
	char command[1000];
	while (GetConsoleWindow()) {
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

void LuaHandler::LoadScript(const std::string& script_name)
{
	std::string script = SCRIPTSPATH + script_name;

	int error = luaL_dofile(Get().m_state, script.c_str());

	if (lua_isstring(Get().m_state, -1))
	{
		std::cout << "Error: " << lua_tostring(Get().m_state, -1) << "\n";
	}
}