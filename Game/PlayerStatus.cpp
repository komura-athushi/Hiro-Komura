#include "stdafx.h"
#include "PlayerStatus.h"
PlayerStatus::PlayerStatus()
{
}


PlayerStatus::~PlayerStatus()
{
}

bool PlayerStatus::Start()
{

	return true;
}

void PlayerStatus::Update()
{

}

void PlayerStatus::PlusExp(const int& exp)
{
	int ep = exp;
	//ŒoŒ±’l‚ð‰ÁŽZ
	m_Exp += ep;
	while (m_LevelExp <= m_Exp) {
		ep -= m_NextExp;
		m_Level+=1;
		m_NextExp = (int)((1 + (float)(m_Level*m_Level * 0.1f)) * 80);
		m_LevelExp += m_NextExp;
		m_Power += 5 + rand() % 3;
		m_Attack = m_Power + m_SwordAttack;
		m_MaxHP += 10;
		m_MaxPP += 10;
	}
		m_NextExp -= ep;
}
