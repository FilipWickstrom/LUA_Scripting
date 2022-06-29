#include "PCH.h"
#include "CppToLua.h"

bool LoadScript(const std::string& script_name)
{
	//No name on the file...
	if (script_name.empty()) return false;

	std::string script = SCRIPTSPATH + script_name;

	if (luaL_dofile(LUA, script.c_str()) != LUA_OK)
	{
		std::cout << "Error: " << lua_tostring(LUA, -1) << '\n';
		return false;
	}
	return true;
}
