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
		m_Exp += exp;
		int e = m_NextExp;
		e-= exp;
		if (e <= 0) {
			m_Level++;
			m_NextExp = (int)(1 + (float)(m_Level*0.1f+ m_Level * 0.1f)) * 80;
			m_NextExp += exp - e;
			m_Power += 5 + rand() % 3;
			m_Attack = m_Power + m_SwordAttack;
			m_MaxHP += 10;
			m_MaxPP += 10;
		}
		else {
			m_NextExp -= exp;
		}
}
