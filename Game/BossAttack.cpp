#include "stdafx.h"
#include "BossAttack.h"


BossAttack::BossAttack()
{
}


BossAttack::~BossAttack()
{
	delete  m_bullet1skinModel;
	delete  m_bullet2skinModel;
	delete  m_bullet3skinModel;
}

bool BossAttack::Start()
{
	if (m_number==1) {
		//�e�P�̃X�L�����f�������_�[��\��
		m_bullet1skinModel = new GameObj::CSkinModelRender;
		m_bullet1skinModel->Init(L"Resource/modelData/Magic_Sample.cmo");
	}
	else if (m_number==2) {
		//�e�Q�̃X�L�����f�������_�[��\��
		m_bullet2skinModel = new GameObj::CSkinModelRender;
		m_bullet2skinModel->Init(L"Resource/modelData/bullet2.cmo");
		m_bullet2skinModel->SetScale(m_scale);
	}else{
		//�e�R�̃X�L�����f�������_�[��\��
		m_bullet3skinModel = new GameObj::CSkinModelRender;
		m_bullet3skinModel->Init(L"Resource/modelData/bullet3.cmo");
	}
	return true;
}

void BossAttack::Attack1()
{
	//�e�ۂ��ړ�������B
	m_position += m_moveSpeed;
	//�X�L�����f�������_�[�ɍ��W��`����B
	m_bullet1skinModel->SetPos(m_position);
}

void BossAttack::Attack2()
{
	//�v���C���[�̕����Ɍ�������B
	CVector3 moveplayer = m_moveSpeed;
	moveplayer.y = 0.0f;
	moveplayer.Normalize();
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveplayer.x, moveplayer.z));
	m_bullet2skinModel->SetRot(m_rotation);
	//�e�ۂ��ړ�������Bff
	m_position += m_moveSpeed;
	//�X�L�����f�������_�[�ɍ��W��`����B
	m_bullet2skinModel->SetPos(m_position);
}

void BossAttack::Attack3()
{
	//�v���C���[�̕����Ɍ�������B
	CVector3 moveplayer = m_moveSpeed;
	moveplayer.y = 0.0f;
	moveplayer.Normalize();
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveplayer.x, moveplayer.z));
	m_bullet3skinModel->SetRot(m_rotation);
	//�e�ۂ��ړ�������Bff
	m_position += m_moveSpeed;
	//�X�L�����f�������_�[�ɍ��W��`����B
	m_bullet3skinModel->SetPos(m_position);
}

void BossAttack::Update()
{
	//�^�C�}�[�����Z����B
	m_timer++;
	if (m_number==1) {
		Attack1();
	}
	else if (m_number==2) {
		Attack2();
	}
	else {
		Attack3();
	}
	if (m_timer == 50) {
		//�^�C�}�[��50�ɂȂ�����C���X�^���X���폜����B
		delete this;
	}
}