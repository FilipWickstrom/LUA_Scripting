#include "BasicEnemyManager.h"
#include "Includer.h"

void BasicEnemyManager::NewEnemy()
{
}

BasicEnemyManager::BasicEnemyManager()
{
	// Initialize the basic enemy table.
	if (luaL_newmetatable(LUA, "BasicMonster") != 0)
	{
		// Success, Continue on.

		// Register functions
		luaL_Reg BasicMonsterFuncs[] =
		{
			{"new", basicEnemy::CreateBasicMonster},
			{"pos", basicEnemy::GetBasicMonsterPos},
			{"attack", basicEnemy::BasicMonsterAttack},
			{NULL, NULL}
		};

		// Register functions onto metatable thats on top of the stack.
		luaL_setfuncs(LUA, BasicMonsterFuncs, 0);

		// Make a copy of the metatable on spot -1
		lua_pushvalue(LUA, -1);

		// Make itself __index
		lua_setfield(LUA, -1, "__index");

		lua_setglobal(LUA, "BasicMonster");

		lua_getglobal(LUA, "BasicMonster");
		// Pop out the table.
		lua_pop(LUA, -1);
	}
	else
		lua_pop(LUA, 1);
}

int basicEnemy::CreateBasicMonster(lua_State* L)
{
	BasicEnemy** monster = reinterpret_cast<BasicEnemy**>(lua_newuserdata(L, sizeof(BasicEnemy*)));
	*monster = new BasicEnemy(s_freeIndex);
	s_freeIndex++;

	luaL_getmetatable(L, "BasicMonster");
	lua_setmetatable(L, -2);

#ifdef _DEBUG
	luaL_dostring(L, "print('New Monster!')");
#endif

	return 1;
}

int basicEnemy::GetBasicMonsterPos(lua_State* L)
{
	return 0;
}

int basicEnemy::BasicMonsterAttack(lua_State* L)
{
	return 0;
}

basicEnemy::BasicEnemy::BasicEnemy(unsigned int index)
{
	m_id = index;
	m_attack = 7.5f;
	m_speed = 5.0f;
}
