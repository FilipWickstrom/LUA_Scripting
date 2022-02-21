#pragma once
#include "Components.h"
#include "Model.h"
#include <lua.hpp>

constexpr int ENEMY_MAX_COUNT = 25;

class BasicEnemyManager
{
private:

	int ids[ENEMY_MAX_COUNT] = {-1};
	int m_nrOfEnemies = 0;

public:

	void NewEnemy();

	BasicEnemyManager();
	~BasicEnemyManager() = default;

};

namespace basicEnemy
{
	static unsigned int s_freeIndex = 0;

	class BasicEnemy
	{
	private:

		unsigned int m_id;
		float m_attack;
		float m_speed;

		position_t m_pos;

	public:

		BasicEnemy(unsigned int index);

	};

	int CreateBasicMonster(lua_State* L);

	int GetBasicMonsterPos(lua_State* L);

	int BasicMonsterAttack(lua_State* L);
}