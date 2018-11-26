#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const int& id, const std::string& name, const int& hp, const int& atk, const int& exp, const float dropchances[4])
	:m_id(id),m_name(name),m_hp(hp),m_atk(atk),m_exp(exp)
{
	m_dropChances[0] = dropchances[0];
	m_dropChances[1] = dropchances[1];
	m_dropChances[2] = dropchances[2];
	m_dropChances[3] = dropchances[3];
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
