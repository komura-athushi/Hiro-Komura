#include "stdafx.h"
#include "IEnemy.h"


IEnemy::IEnemy(int h,int a):m_HP(h),m_Attack(a)
{
	
}

IEnemy::~IEnemy()
{
}

void IEnemy::CCollision(CVector3 pos,float l, float r)
{
	//くらい判定の作成
	m_collision = std::make_unique<GameObj::CCollisionObj>();
	//形状の作成
	m_collision->CreateSphere(pos + CVector3::AxisY()*l, CQuaternion::Identity(),r);
	//寿命を設定
	m_collision->SetTimer(enNoTimer);//enNoTimerで寿命なし
	//名前を設定
	m_collision->SetName(L"IEnemy");
	//クラスのポインタを設定
	m_collision->SetClass(this);
}

void IEnemy::SetCCollision(CVector3 pos,float l)
{
	m_collision->SetPosition(pos + CVector3::AxisY()*l);
}

void IEnemy::Damage(int attack)
{
	if (m_timer >= 30) {
		m_HP -= attack;
		m_timer = 0;
		m_damage = true;
	}
	if (m_HP <= 0) {
		m_death = true;
	}
}

void IEnemy::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L"HP   %d\nPP   %d\n", m_HP,m_Attack);
	m_font.DrawScreenPos(output, { 00.0f,100.0f });
}


