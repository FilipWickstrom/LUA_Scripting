#pragma once
#define LUA LuaHandler::GetLua()

class LuaHandler
{
private:
	lua_State* m_state;

	LuaHandler();
	~LuaHandler();
	static auto& Get();
public:
	// Get the Lua state
	static lua_State*& GetLua();

	// Dump the lua stack to console.
	static void DumpStack();

	// Writing out errors from pcall. Return when receiving errors 
	static bool CheckErrors(const int& nrOfArgs, const int& nrOfReturns);
};