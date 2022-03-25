#include "PCH.h"
#include "EditorScene.h"

void EditorScene::Load()
{
	//Read the lua-script
	LoadScript("EditorScene.lua");

	//Execute the start-function
	lua_getglobal(LUA, "Start");
	lua_pcall(LUA, 0, 0, 0);
	if (lua_isstring(LUA, -1))
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";
}

void EditorScene::Clean()
{
	//Execute the start-function
	lua_getglobal(LUA, "Clean");
	lua_pcall(LUA, 0, 0, 0);
	if (lua_isstring(LUA, -1))
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";
}

void EditorScene::Update()
{
	lua_getglobal(LUA, "Update");
	lua_pcall(LUA, 0, 0, 0);
}
