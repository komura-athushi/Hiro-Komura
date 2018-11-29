#include "stdafx.h"
#include "IEnemy.h"
#include "DropItem.h"

IEnemy::IEnemy(const int& h,const int& a,const int& e,const int dropchances[Weapon::m_HighestRarity]):m_HP(h),m_Attack(a),m_Exp(e)
{
	/*for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		m_dropChances[i] = *dropchances;
		dropchances++;
	}*/
	memcpy(m_dropChances, dropchances, sizeof(dropchances));
}

IEnemy::~IEnemy()
{
	Drop();
	m_collision->Delete();
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
	m_position = pos;
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
		}
}

void IEnemy::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L"HP   %d\natk  %d\nドロップ  %d\n", m_HP,m_Attack,m_dropChances[1]);
	m_font.DrawScreenPos(output, { 00.0f,100.0f });
}

void IEnemy::Drop()
{
	int rad = rand() % 100 + 1;
	for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		if (m_dropChances[i] >= rad) {
			DropItem* dropitem = new DropItem;
			dropitem->SetRarity(i);
			dropitem->SetPosition(m_position);
			dropitem->SetName(L"DropItem");
			return;
		}
	}
}

