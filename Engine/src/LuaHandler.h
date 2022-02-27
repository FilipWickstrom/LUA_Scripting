#pragma once
#define LUA LuaHandler::GetLua()

// Dump the lua stack to console.
void DumpStack(lua_State* L);

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
	static void LoadScript(const std::string& script_name);
};