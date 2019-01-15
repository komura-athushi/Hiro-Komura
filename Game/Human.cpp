#include "stdafx.h"
#include "Human.h"
#include "Player.h"
#include "GameData.h"
#include "PlayerStatus.h"
Human::Human()
{
}


Human::~Human()
{
	delete m_skinModelRender;
}

bool Human::Start()
{
	//アニメーションファイルをロード
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/unityChan/idle.tka", true);//, enZtoY);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num,enFbxUpAxisY);//, enFbxUpAxisZ);
	//m_skinModelRender->Init(L"Resource/modelData/human.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->GetAnimCon().SetSpeed(m_animationspeed);
	m_rotation.SetRotationDeg(CVector3::AxisY(),180.0f);
	m_skinModelRender->SetRot(m_rotation);
	m_gamedata = FindGO<GameData>(L"GameData");
	m_playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
	switch (m_gamedata->GetTownLevel()) {
	case 0:
		if (m_gamedata->GetStageClear(0)) {
			if (m_necessarymaterial <= m_playerstatus->GetMaterial(0)) {
				m_developtown = true;
			}
		}
		break;
	}
	return true;
}

void Human::Update()
{
	if (m_player == nullptr) {
		m_player = FindGO<Player>();
	}
	else {
		Turn();
	}
	AnimationController();
}

void Human::Turn()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	if (pos.Length() <= 300.0f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(pos.x,pos.z));
	}
	else if (pos.Length() >= 1500.0f) {
		m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	}
	m_skinModelRender->SetRot(m_rotation);
}

void Human::AnimationController()
{
	switch (m_state) {
	case enState_Idle:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		break;
	}
}

void Human::PostRender()
{

}