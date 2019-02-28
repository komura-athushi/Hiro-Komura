#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Fade.h"
#include "MainSound.h"

GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	m_sprite.Init(L"Resource/sprite/gameclear.dds");
	m_sprite2.Init(L"Resource/sprite/credit.dds");
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	return true;
}

void GameClear::Update()
{

	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			Title* title = new Title;
			delete this;
		}
	}
	else {
		if (Pad(0).GetDown(enButtonStart)) {
			if (m_iscredit) {
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
			}
			else {
				m_iscredit = true;
			}
		}
	}
}

void GameClear::PostRender()
{
	if (m_iscredit) {
		m_sprite2.DrawScreenPos(m_position, m_scale, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.2f);
	}
	else {
		m_sprite.DrawScreenPos(m_position, m_scale, CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::SpriteEffects_None,
			0.2f);
	}
}


