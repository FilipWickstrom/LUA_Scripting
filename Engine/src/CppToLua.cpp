#include "PCH.h"
#include "CppToLua.h"

void LoadScript(const std::string& script_name)
{
	std::string script = SCRIPTSPATH + script_name;

	int error = luaL_dofile(LUA, script.c_str());

	if (lua_isstring(LUA, -1))
	{
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";
	}
}
