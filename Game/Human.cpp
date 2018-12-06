#include "stdafx.h"
#include "Human.h"


Human::Human()
{
}


Human::~Human()
{
}

bool Human::Start()
{
	//アニメーションファイルをロード
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/human/idle.tka", true);//, enZtoY);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/human.cmo", m_animClip, enAnimationClip_num);//, enFbxUpAxisZ);
	//m_skinModelRender->Init(L"Resource/modelData/human.cmo");
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->GetAnimCon().SetSpeed(m_animationspeed);
	return true;
}

void Human::Update()
{
	AnimationController();
}

void Human::AnimationController()
{
	switch (m_state) {
	case enState_Idle:
		m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
		break;
	}
}