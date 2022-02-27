#pragma once
#include "Components.h"

class EnemyManager
{
private:


	void SetupBasicEnemy();
	void LuaNewBasicEnemy();

public:

	EnemyManager();
	~EnemyManager() = default;

	void NewBasicEnemy(float x, float y);

	static unsigned int m_freeIndex;
};

namespace basicEnemy
{
	class BasicEnemy
	{
	private:

		unsigned int m_id;
		float m_attack;
		float m_speed;

		position_t m_pos;

	public:

		BasicEnemy(unsigned int index);

		position_t& GetPosition();
		float GetAttack();

	};

	int CreateBasicMonster(lua_State* L);

	int GetBasicMonsterPos(lua_State* L);

	int BasicMonsterAttack(lua_State* L);

	int ChasePlayerBasicMonster(lua_State* L);
}