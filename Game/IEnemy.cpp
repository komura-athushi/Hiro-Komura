#include "stdafx.h"
#include "IEnemy.h"
#include "DropItem.h"
#include "Player.h"
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
}

void IEnemy::CCollision(const CVector3& pos,const float& l,const float& r)
{
	//���炢����̍쐬
	//m_collision = std::make_unique<SuicideObj::CCollisionObj>();
	m_collision = new SuicideObj::CCollisionObj;
	//�`��̍쐬
	m_collision->CreateSphere(pos + CVector3::AxisY()*l, CQuaternion::Identity(),r);
	//������ݒ�
	m_collision->SetTimer(enNoTimer);//enNoTimer�Ŏ����Ȃ�
	//���O��ݒ�
	m_collision->SetName(L"IEnemy");
	//�N���X�̃|�C���^��ݒ�
	m_collision->SetClass(this);
}

void IEnemy::SetCCollision(const CVector3& pos,const float& l)
{
	if (m_death) {
		return;
	}
	m_collision->SetPosition(pos + CVector3::AxisY()*l);
	m_position = pos;
	m_timer++;
	m_timer1++;
	m_timer2++;
	m_timer3++;
}

void IEnemy::Damage(const int& attack,int number)
{
	switch (number) {
	case 0:
		if (m_timer >= 15) {		//�ʏ�U��
			m_HP -= attack;
			m_timer = 0;
			m_damage = true;
			//�v���C���[��PP����
			Player* player = FindGO<Player>(L"Player");
			player->RecoveryPP();
		}
		break;
	case 1:
		if (m_timer1 >= 40) {		//�t�H�C�G
			m_HP -= attack;
			m_timer1 = 0;
			m_damage = true;
		}
		break;
	case 2:
		if (m_timer2 >= 8) {		//�C���O�����c
			m_HP -= attack;
			m_timer2 = 0;
			m_damage = true;
		}
		break;
	case 3:
		if (m_timer3 >= 15) {		//�U���o�[�X
			m_HP -= attack;
			m_timer3 = 0;
			m_damage = true;
		}
		break;
	case 4:							//�V�t�^(�_���[�W����)
		break;
	case 5:							//�}�W�X�t�B

		break;
	}
	if (m_HP <= 0) {
		m_death = true;
		m_collision->Delete();
	}
}

void IEnemy::PostRender()
{
	wchar_t output[256];
	swprintf_s(output, L"HP   %d\natk  %d\n�h���b�v  %d\n", m_HP,m_Attack,m_dropChances[1]);
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

