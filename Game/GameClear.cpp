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
	m_sprite.Init(L"Resource/sprite/credit.dds");
	m_fade = FindGO<Fade>();
	m_fade->StartFadeIn();
	MainSound* ms = FindGO<MainSound>();
	ms->SetBGM(MainSound::enBGM_End);
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
		if (!m_isgo) {
			m_timer += GetDeltaTimeSec();
			if (m_timer >= m_time) {
				m_timer = 0.0f;
				m_isgo = true;
			}
		}
		else {
			if (m_position.y > m_stopY) {
				m_position.y += m_speedmultiply * GetDeltaTimeSec();
			}
			else {
				m_position.y = m_stopY;
				m_timer += GetDeltaTimeSec();
				if (m_timer >= m_time) {
					m_isWaitFadeout = true;
					m_fade->StartFadeSlowOut();
				}
			}
		}
	}
}

void GameClear::PostRender()
{

	m_sprite.DrawScreenPos(m_position, m_scale, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.2f);

}


