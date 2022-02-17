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

};