#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "IEnemy.h"
#define _USE_MATH_DEFINES //M_PI �~�����Ăяo��
#include <math.h> 
GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//PerspectiveCamera�N���X(���s�̂���J����)�𐶐����A���C���J�����ɐݒ�
	m_camera = FindGO<GameObj::PerspectiveCamera>(L"Camera");
	m_camera->SetPos(m_position);
	m_camera->SetNear(1.0f);
	m_camera->SetFar(200000.0f);
	SetMainCamera(m_camera);
	return true;
}

void GameCamera::Update()
{
	if (m_player->isCagliostro()) {
		cagliostro();
	}
	else {
		unityChan();
	}
	
}

void GameCamera::cagliostro()
{
	if (Pad(0).GetButton(enButtonUp)) {
		m_r -= 0.8f;
	}
	else if (Pad(0).GetButton(enButtonDown)) {
		m_r += 0.8f;
	}
	if (m_r <= 1.0f) {
		m_r = 1.0f;
	}
	//�E�X�e�B�b�N�̓��͗ʂ��擾
	CVector2 stickL;
	stickL = Pad(0).GetStick(L);
	m_topos += stickL.y * 1.0f;
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�E�X�e�B�b�N�̓��͗ʂ��擾
	CVector2 stickR;
	stickR = Pad(0).GetStick(R);
	stickR.x = -stickR.x;
	float m_sdegreexz = -stickR.x * 2.0f * 60.0f * GetDeltaTimeSec();
	float m_sdegreey = -stickR.y * 2.0f * 60.0f * GetDeltaTimeSec();
	//��]�x���Z
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//�㉺�����̃J�����ړ��𐧌�
	if (m_degreey >= 80.0f) {
		m_degreey = 80.0f;
	}
	if (m_degreey <= -80.0f) {
		m_degreey = -80.0f;
	}
	//�p�x�����W�A���P�ʂɒ���
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	//�����_��ݒ肷��
	m_target = { 0.0f,0.0f,0.0f };
	m_target.y += m_topos;
	m_target += m_player->GetPosition();
	//Y������ɉ�]������B
	CQuaternion qRot;
	qRot.SetRotation(m_axisY, m_radianx);
	//���ꂪ�v���C���[�ƃJ���������ԃx�N�g���ł�
	CVector3 toPos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(toPos);
	//�㉺�̉�]�B
	//�܂��͉񂷎����v�Z����B
	CVector3 rotAxis;
	rotAxis.Cross(toPos, m_axisY);
	//�x�N�g���𐳋K������B
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(toPos);
	toPos *= m_r;
	m_position = m_target + toPos;
	toPos *= 2;
	//m_target -= toPos;
	//���_
	m_camera->SetTarget(m_target);
	//���W
	m_camera->SetPos(m_position);
}

void GameCamera::unityChan()
{
	//�v���C���[�̍��W���擾
	CVector3 m_playerposition = m_player->GetPosition();
	//�E�X�e�B�b�N�̓��͗ʂ��擾
	CVector2 stickR;
	stickR = Pad(0).GetStick(R);
	stickR.x = -stickR.x;
	float m_sdegreexz = -stickR.x * 2.0f;
	float m_sdegreey = -stickR.y * 2.0f;
	//��]�x���Z
	m_degreexz += m_sdegreexz;
	m_degreey += m_sdegreey;
	//�㉺�����̃J�����ړ��𐧌�
	if (m_degreey >= 40.0f) {
		m_degreey = 40.0f;
	}
	if (m_degreey <= -15.0f) {
		m_degreey = -15.0f;
	}
	//�p�x�����W�A���P�ʂɒ���
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	Hutu();
	//���_
	m_camera->SetTarget(m_target);
	//���W
	m_camera->SetPos(m_position);
}

// ���ʎ��_�̏��� �J�����̍��W���ړ�������A�J�����̒����_�����Z�b�g
void GameCamera::Hutu()
{
	if (!m_tage) {
		//�����_��ݒ肷��
		m_target = { 0.0f,0.0f,0.0f };
		m_target.y += 140.0f;
		m_target += m_player->GetPosition();
	}
	//Y������ɉ�]������B
	CQuaternion qRot;
	qRot.SetRotation(m_axisY, m_radianx);
	//���ꂪ�v���C���[�ƃJ���������ԃx�N�g���ł�
	CVector3 toPos = { 0.0f, 0.0f, 1.0f };
	qRot.Multiply(toPos);
	//�㉺�̉�]�B
	//�܂��͉񂷎����v�Z����B
	CVector3 rotAxis;
	rotAxis.Cross(toPos, m_axisY);
	//�x�N�g���𐳋K������B
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(toPos);
	toPos *= m_r;
	m_position = m_target + toPos;
	toPos *= 2;
	//m_target -= toPos;
	/*m_target.y = m_playerposition.y;
	m_target.y += 140.0f;*/
	m_front = m_target - m_position;
	m_front.y = 0.0f;
	m_front.Normalize();
	m_right = m_front;
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	rot.Multiply(m_right);
}

