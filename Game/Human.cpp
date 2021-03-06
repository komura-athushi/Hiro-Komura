#include "stdafx.h"
#include "Human.h"
#include "Player.h"
#include "GameData.h"
#include "PlayerStatus.h"
#include "Town.h"
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
	m_skinModelRender->Init(L"Resource/modelData/unityChan.cmo", m_animClip, enAnimationClip_num,enFbxUpAxisY);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->GetAnimCon().SetSpeed(m_animationspeed);
	m_rotation.SetRotationDeg(CVector3::AxisY(),180.0f);
	m_skinModelRender->SetRot(m_rotation);
	m_gamedata = &GameData::GetInstance();
	m_playerstatus = &PlayerStatus::GetInstance();
	m_townlevel = m_gamedata->GetTownLevel();
	m_sprite.Init(L"Resource/sprite/window.dds");
	//街の発展レベルが2であればこれ以上は発展しないようにする
	if (m_gamedata->GetTownLevel() != 2) {
		//条件を満たし手入れば、街を発展できるようにする
		if (m_gamedata->GetStageClear(m_townlevel)) {
			m_developtown = true;
		}
	}
	return true;
}

void Human::Update()
{
	if (!m_istalk) {
		return;
	}
	m_townlevel = m_gamedata->GetTownLevel();
	if (m_player == nullptr) {
		m_player = FindGO<Player>();
		return;
	}
	else {
		Turn();
	}
	if (m_leveluptown) {
		//街の発展フラグをonにする
		Town* tonw = FindGO<Town>();
		tonw->DevelopTown();
		//発展レベルを上げる
		m_gamedata->UpTownLevel();
		m_developtown = false;								
		m_leveluptown = false;
		m_ontalk = false;
		m_istalk = false;
	}
	AnimationController();
}

void Human::Turn()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	//プレイヤーが一定距離以内に居たらプレイヤーの方向を向くようにする
	if (pos.Length() <= 300.0f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(pos.x,pos.z));
	}
	//プレイヤーが一定距離以外に居たら回転をもとに戻す
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

void Human::SetLevelUpTown()
{
	if (m_gamedata->GetTownLevel() == GameData::m_stagenumber - 1) {
		return;
	}
	m_leveluptown = true;
}

void Human::PostRender()
{
	if (!m_istalk) {
		return;
	}
	if (!m_ontalk) {
		return;
	}
	wchar_t output[100];
	if (m_gamedata->GetTownLevel() == GameData::m_stagenumber - 1) {
		swprintf_s(output, L"これ以上街を発展させることは出来ません\n");
	}
	else {
		if (m_developtown) {
			swprintf_s(output, L"街を発展させることができます。\n街を発展させますか？\n");
		}
		else {
			swprintf_s(output, L"街を発展させるにはステージ%dをクリアする必要があります\n", m_townlevel + 1);
			
		}
	}
	m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), {0.6f,0.6f});
	m_sprite.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
}