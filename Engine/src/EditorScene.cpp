#include "PCH.h"
#include "EditorScene.h"

void EditorScene::Load()
{
	//Read the lua-script
	LoadScript("EditorScene.lua");

	//Execute the start-function
	lua_getglobal(LUA, "Start");
	LuaHandler::CheckErrors(0, 0);
}

void EditorScene::Clean()
{
	lua_getglobal(LUA, "Clean");
	LuaHandler::CheckErrors(0, 0);
}

void EditorScene::Update()
{
	lua_getglobal(LUA, "Update");
	lua_pushnumber(LUA, Graphics::GetDeltaTime());
	LuaHandler::CheckErrors(1, 0);
}
