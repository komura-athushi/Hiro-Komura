#include "stdafx.h"
#include "BossAttack.h"


BossAttack::BossAttack() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances)
{
}


BossAttack::~BossAttack()
{
}

bool BossAttack::Start()
{
	//�e�P�̃X�L�����f�������_�[��\��
	m_bullet1skinModel = new GameObj::CSkinModelRender;
	m_bullet1skinModel->Init(L"Resource/modelData/Magic_Sample.cmo");
	////�e�Q�̃X�L�����f�������_�[��\��
	//m_bullet2skinModel = new GameObj::CSkinModelRender;
	//m_bullet2skinModel->Init(L"Resource/modelData/bullet2.cmo");
	////�e�R�̃X�L�����f�������_�[��\��
	//m_bullet3skinModel = new GameObj::CSkinModelRender;
	//m_bullet3skinModel->Init(L"Resource/modelData/bullet3.cmo");
	return true;
}

void BossAttack::Attack1()
{
	//�e�ۂ��ړ�������B
	m_position += m_moveSpeed;
	//�X�L�����f�������_�[�ɍ��W��`����B
	m_bullet1skinModel->SetPos(m_position);
	if (m_timer == 50) {
		//�^�C�}�[��50�ɂȂ�����C���X�^���X���폜����B
		DeleteGO(this);4
	}
}

void BossAttack::Attack2()
{

}

void BossAttack::Attack3()
{

}

void BossAttack::Update()
{
	//�^�C�}�[�����Z����B
	m_timer++;
	Attack1();
}