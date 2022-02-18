#pragma once
#pragma comment(lib, "Irrlicht.lib")
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include "lua.hpp"
#include <thread>
#include <string>

class LuaHandler
{
private:

	lua_State* m_state;
	std::thread m_conThread;

	LuaHandler();
	~LuaHandler();

public:

	static auto& Get();
	static lua_State*& GetLua();

	// Load a script from file. Make sure its inside the "Scripts" Folder
	static int LoadScript(const std::string& script_name);
};