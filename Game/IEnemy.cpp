#include "stdafx.h"
#include "IEnemy.h"


IEnemy::IEnemy(const int& h,const int& a,const int& e, const int dropchances[Weapon::m_HighestRarity]):m_HP(h),m_Attack(a),m_Exp(e)
{
	/*for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		m_dropChances[i] = dropchances[i];
	}*/
	memcpy(m_dropChances, dropchances, sizeof(dropchances));
}

IEnemy::~IEnemy()
{
}

void IEnemy::CCollision(const CVector3& pos,const float& l,const float& r)
{
	//くらい判定の作成
	//m_collision = std::make_unique<SuicideObj::CCollisionObj>();
	m_collision = new SuicideObj::CCollisionObj;
	//形状の作成
	m_collision->CreateSphere(pos + CVector3::AxisY()*l, CQuaternion::Identity(),r);
	//寿命を設定
	m_collision->SetTimer(enNoTimer);//enNoTimerで寿命なし
	//名前を設定
	m_collision->SetName(L"IEnemy");
	//クラスのポインタを設定
	m_collision->SetClass(this);
}

void IEnemy::SetCCollision(const CVector3& pos,const float& l)
{
	m_collision->SetPosition(pos + CVector3::AxisY()*l);
}

void IEnemy::Damage(const int& attack)
{
	
		if (m_timer >= 30) {
			m_HP -= attack;
			m_timer = 0;
			m_damage = true;
		}
		if (m_HP <= 0) {
			m_death = true;
			m_collision->Delete();
		}
}

void IEnemy::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L"HP   %d\natk  %d\n", m_HP,m_Attack);
	m_font.DrawScreenPos(output, { 00.0f,100.0f });
}

void IEnemy::Drop()
{
	for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		int rad = rand() % 100;
		if (int(m_dropChances[i]) <= rad) {

		}
	}
}

