#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const int& id, const std::string& name, const int& hp, const int& atk, const int& exp, const int dropchances[Weapon::m_HighestRarity])
	:m_id(id),m_name(name),m_hp(hp),m_atk(atk),m_exp(exp)
{
	for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		m_dropChances[i] = dropchances[i];
	}
}

Enemy::Enemy(const Enemy& enemy):m_id(enemy.m_id), m_name(enemy.m_name), m_hp(enemy.m_hp), m_atk(enemy.m_atk), m_exp(enemy.m_exp)
{

}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	return true;
}

void Enemy::Update()
{

}
