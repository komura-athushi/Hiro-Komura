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
	//���炢����̍쐬
	m_collision = std::make_unique<GameObj::CCollisionObj>();
	//�`��̍쐬
	m_collision->CreateSphere(pos + CVector3::AxisY()*l, CQuaternion::Identity(),r);
	//������ݒ�
	m_collision->SetTimer(enNoTimer);//enNoTimer�Ŏ����Ȃ�
	//���O��ݒ�
	m_collision->SetName(L"IEnemy");
	//�N���X�̃|�C���^��ݒ�
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


