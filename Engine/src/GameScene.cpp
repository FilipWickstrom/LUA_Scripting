#include "PCH.h"
#include "GameScene.h"


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	this->Clean();
}

void GameScene::AddBasicEnemy(float x, float y)
{
	/*
		Spawn an enemy in lua and an object to respresent it in game.
	*/
	m_enemyManager.NewBasicEnemy(x, y);
	std::string modelname = "cube.obj";
	m_models[EnemyManager::m_freeIndex] = Model(modelname, { x, 0.f, y }, { 0.f,0.f,0.f }, { 1.f, 1.f, 1.f });
	EnemyManager::m_freeIndex = m_models[EnemyManager::m_freeIndex].GetID();
}

void GameScene::UpdateCamera()
{
	lua_getglobal(LUA, "GetObjectPosition");
	lua_pushnumber(LUA, 0);
	int ret = lua_pcall(LUA, 1, 2, 0);

	if (ret == 0)
	{
		if (lua_isnumber(LUA, -1) && lua_isnumber(LUA, -2))
		{
			irr::f32 x = static_cast<irr::f32>(lua_tonumber(LUA, -2));
			irr::f32 z = static_cast<irr::f32>(lua_tonumber(LUA, -1));

			if (m_gameCamera)
			{
				// + 1 to look in the correct direction, z positive
				m_gameCamera->setTarget({ x, 0, z + 1 });
				m_gameCamera->setPosition({ x, 40.f, z });
			}
		}
		else
		{
			// 'Err' was returned, do something like delete this object or something idk.
		}
		lua_pop(LUA, 2);
	}
	else
	{
		std::cout << lua_tostring(LUA, -1) << "\n";
		lua_pop(LUA, 1);
	}
}

void GameScene::Load()
{
	//Read the lua-script
	LoadScript("gameLoop.lua");

	lua_getglobal(LUA, "Start");
	lua_pcall(LUA, 0, 0, 0);
	if (lua_isstring(LUA, -1))
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";
	LuaHandler::DumpStack();


	//Read the scene basics from a file
	//Read the map


	//Remove current camera and replace with gamecamera
	RemoveCamera();

	//Orthographic camera
	m_gameCamera = Graphics::GetSceneManager()->addCameraSceneNode(0, { 0,40,0 }, { 0,0,1 });
	irr::core::matrix4 orthoMatrix;
	/*
		-25 <= X <= 25
		-13 <= Y <= 13
		0	<= z <= 20
	*/
	orthoMatrix.buildProjectionMatrixOrthoLH(50, 26, 0, 50);
	m_gameCamera->setProjectionMatrix(orthoMatrix);
	Graphics::GetSceneManager()->setActiveCamera(m_gameCamera);
	
}

void GameScene::Clean()
{
	//Clear all the models
	auto it = m_models.begin();
	while (it != m_models.end())
	{
		it->second.Drop();
		it = m_models.erase(it);
	}

	Graphics::GetSceneManager()->clear();
}

void GameScene::Update()
{
	//Update from lua-scrips
	lua_getglobal(LUA, "Update");
	lua_pushnumber(LUA, Graphics::GetDeltaTime());
	lua_pcall(LUA, 1, 1, 0);
	int lua_return = static_cast<int>(lua_tonumber(LUA, -1));
	lua_pop(LUA, 1);

	UpdateCamera();
}
