#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start() override;
	void Update() override;
	void PostRender() override;
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

	bool IsFade() const
	{
		return m_state != enState_Idle;
	}
	float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

private:
	enum EnState {
		enState_FadeIn,		//!<フェードイン中。
		enState_FadeOut,		//!<フェードアウト中。
		enState_Idle,		//!<アイドル中。
	};
	CSprite m_sprite;
	EnState m_state = enState_Idle;	//!<状態。
	float m_currentAlpha = 1.0f;		//!<現在のα値。
};

