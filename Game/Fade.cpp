#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
{
}


Fade::~Fade()
{
}
bool Fade::Start()
{
	//ロード画面の画像を読み込む
	m_sprite.Init(L"Resource/sprite/loading.dds");
	return true;
}
void Fade::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 2.0f * GetDeltaTimeSec();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeSlowIn:
		m_currentAlpha -= 0.4f * GetDeltaTimeSec();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += 2.0f * GetDeltaTimeSec();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeSlowOut:
		m_currentAlpha += 0.4f * GetDeltaTimeSec();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:

		break;
	}
}
void Fade::PostRender()
{
	if (m_currentAlpha > 0.0f) {
		m_sprite.DrawScreenPos(CVector2::Zero(), CVector2::One(), CVector2::Zero(),
			0.0f,
			{ 1.0f, 1.0f, 1.0f, m_currentAlpha },
			DirectX::SpriteEffects_None,
			0.1f);
	}
}