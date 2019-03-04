#include "stdafx.h"
#include "Title.h"
#include "Town.h"
#include "Fade.h"
#include "MainSound.h"
Title::Title()
{
}

Title::~Title()
{
	//newしてないのでspriteはインスタンスが破棄されたらspriteは自動的に破棄されます
	
}

bool Title::Start()
{
	m_sprite.Init(L"Resource/sprite/Title.dds");
	m_sprite2.Init(L"Resource/sprite/pressstart.dds");
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	return true;
}

void Title::Update()
{
	
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			Town* town = new Town;
			delete this;
		}
	}
	else {
		if (Pad(0).GetDown(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			//SE
			SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/decision.wav");
			se->Play(); //再生(再生が終わると削除されます)
			se->SetVolume(2.5f);
			//3D再生
			se->SetPos(CVector3::Zero());//音の位置
			se->SetDistance(500.0f);//音が聞こえる範囲
			se->Play(true); //第一引数をtrue
		}
	}
	if (m_currentAlpha > 1.0f && m_isadd) {
		m_isadd = false;
	}
	else if(m_currentAlpha < 0.0f && !m_isadd){
		m_isadd = true;
	}
	if (m_isadd) {
		if (m_isWaitFadeout) {
			m_currentAlpha += GetDeltaTimeSec() * 13.0f;
		}
		else {
			m_currentAlpha += GetDeltaTimeSec() * 1.5f;
		}
	}
	else {
		if (m_isWaitFadeout) {
			m_currentAlpha -= GetDeltaTimeSec() * 13.0f;
		}
		else {
			m_currentAlpha -= GetDeltaTimeSec() * 1.5f;
		}
	}
}

void Title::PostRender()
{
	m_sprite.DrawScreenPos(m_position,m_scale, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.2f);
	m_sprite2.DrawScreenPos(m_position, m_scale, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, m_currentAlpha },
		DirectX::SpriteEffects_None,
		0.2f);
}
