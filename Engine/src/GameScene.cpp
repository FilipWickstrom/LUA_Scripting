#include "PCH.h"
#include "GameScene.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	this->Clean();
}

void GameScene::UpdateCamera()
{
	lua_getglobal(LUA, "GetObjectPosition");
	lua_pushnumber(LUA, 0);

	if (!LuaHandler::CheckErrors(1, 2))
	{
		// Did not get any errors
		
		if (lua_isnumber(LUA, -1) && lua_isnumber(LUA, -2))
		{
			irr::f32 x = static_cast<irr::f32>(lua_tonumber(LUA, -2));
			irr::f32 z = static_cast<irr::f32>(lua_tonumber(LUA, -1));

			if (m_camera)
			{
				// + 1 to look in the correct direction, z positive
				m_camera->setTarget({ x, 0, z + 1 });
				m_camera->setPosition({ x, 40.f, z });
			}
		}
		else
		{
			// 'Err' was returned, do something like delete this object or something idk.
			std::cout << "Error: Player is not on index 0" << std::endl;
		}
		lua_pop(LUA, 2);
	}
}

void GameScene::Load()
{
	//Read the lua-script
	LoadScript("GameScene.lua");

	lua_getglobal(LUA, "Start");
	LuaHandler::CheckErrors(0, 0);

	//Read the scene basics from a file
	//Read the map


	//Remove active camera and replace with game-specific camera
	RemoveActiveCam();

	//Orthographic camera
	m_camera = Graphics::GetSceneManager()->addCameraSceneNode(0, { 0,40,0 }, { 0,0,1 });
	irr::core::matrix4 orthoMatrix;
	float aspectRatio = static_cast<float>(Graphics::GetWindowWidth()) /
						static_cast<float>(Graphics::GetWindowHeight());
	/*
		-25 <= X <= 25
		-13 <= Y <= 13
		0	<= z <= 20
	*/
	orthoMatrix.buildProjectionMatrixOrthoLH(50 * aspectRatio, 50, 0, 50);
	m_camera->setProjectionMatrix(orthoMatrix);
	Graphics::GetSceneManager()->setActiveCamera(m_camera);
	
}

void GameScene::Clean()
{
	//Execute the start-function
	lua_getglobal(LUA, "Clean");
	LuaHandler::CheckErrors(0, 0);
}

void GameScene::Update()
{
	//Update from lua-scrips
	lua_getglobal(LUA, "Update");
	lua_pushnumber(LUA, Graphics::GetDeltaTime());
	LuaHandler::CheckErrors(1, 1);

	// [NOT IN USE FOR NOW]
	bool isAlive = static_cast<int>(lua_toboolean(LUA, -1));
	lua_pop(LUA, 1);

	UpdateCamera();
}
