#include "EnemyManager.h"
#include "Includer.h"

unsigned int EnemyManager::m_freeIndex = 0;

void EnemyManager::LuaNewBasicEnemy()
{
	//lua_getglobal(LUA, "BasicMonster");
	//lua_getfield(LUA, -1, "new");
	//lua_pcall(LUA, 0, 1, 0);
	//lua_remove(LUA, lua_gettop(LUA) - 1);

	lua_getglobal(LUA, "addMonster");
	int id = (int)m_freeIndex;
	lua_pushnumber(LUA, id);

	lua_pcall(LUA, 1, 0, 0);
}

void EnemyManager::SetupBasicEnemy()
{
	// Initialize the basic enemy table.
	if (luaL_newmetatable(LUA, "BasicMonster") != 0)
	{
		// Success, Continue on.

		// Register functions
		luaL_Reg BasicMonsterFuncs[] =
		{
			{"new", basicEnemy::CreateBasicMonster},
			{"GetPos", basicEnemy::GetBasicMonsterPos},
			{"AttackPlayer", basicEnemy::BasicMonsterAttack},
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

		lua_pushnumber(LUA, 7.5f);
		lua_setfield(LUA, -2, "attack");

		lua_pushnumber(LUA, 5.0f);
		lua_setfield(LUA, -2, "speed");

		lua_pushnumber(LUA, 0);
		lua_setfield(LUA, -2, "x");

		lua_pushnumber(LUA, 0);
		lua_setfield(LUA, -2, "y");

		//lua_pushnumber(LUA, -1);
		//lua_setfield(LUA, -2, "id");

		// Pop out the table.
		lua_pop(LUA, -1);
	}
	else
		lua_pop(LUA, 1);
}


int basicEnemy::CreateBasicMonster(lua_State* L)
{
	BasicEnemy** monster = reinterpret_cast<BasicEnemy**>(lua_newuserdata(L, sizeof(BasicEnemy*)));
	*monster = new BasicEnemy(EnemyManager::m_freeIndex);

	luaL_getmetatable(L, "BasicMonster");
	lua_setmetatable(L, -2);

#ifdef _DEBUG
	luaL_dostring(L, "print('New Monster!')");
#endif

	return 1;
}

int basicEnemy::GetBasicMonsterPos(lua_State* L)
{
	BasicEnemy* enemy = nullptr;
	void* ptr = luaL_testudata(L, -2, "BasicMonster");
	if (ptr != nullptr)
	{
		enemy = *(BasicEnemy**)ptr;

		// First X is pushed. Then Y.
		lua_pushnumber(L, (lua_Number)enemy->GetPosition().x);
		lua_pushnumber(L, (lua_Number)enemy->GetPosition().y);

		return 2;
	}
	return 0;
}

int basicEnemy::BasicMonsterAttack(lua_State* L)
{
	BasicEnemy* enemy = nullptr;
	void* ptr = luaL_testudata(L, -2, "BasicMonster");
	if (ptr != nullptr)
	{
		enemy = *(BasicEnemy**)ptr;
		lua_getglobal(L, "HurtPlayer");
		lua_pushnumber(L, enemy->GetAttack());
		int type = lua_isfunction(L, -2);
		if (type)
		{
			if (lua_pcall(L, 1, 0, 0) != 0)
			{
				lua_pop(L, 1);
			}
			else
			{
#ifdef _DEBUG
				//std::cout << "Player got Hurt!" << std::endl;
#endif
			}
		}
	}

	return 0;
}

int basicEnemy::ChasePlayerBasicMonster(lua_State* L)
{

	return 0;
}

basicEnemy::BasicEnemy::BasicEnemy(unsigned int index)
{
	m_id = index;
	m_attack = 7.5f;
	m_speed = 5.0f;
}

position_t& basicEnemy::BasicEnemy::GetPosition()
{
	return m_pos;
}

float basicEnemy::BasicEnemy::GetAttack()
{
	return m_attack;
}

EnemyManager::EnemyManager()
{
	SetupBasicEnemy();
}

void EnemyManager::NewBasicEnemy(float x, float y)
{
	LuaNewBasicEnemy();

	void* ptr = luaL_testudata(LUA, -1, "BasicMonster");
	if (ptr)
	{
		basicEnemy::BasicEnemy* enemy = *(basicEnemy::BasicEnemy**) ptr;

		enemy->GetPosition().x = x;
		enemy->GetPosition().y = y;
	}
}

