#pragma once
class Fade;
//ƒQ[ƒ€‚ğƒNƒŠƒA‚µ‚½‚Æ‚«‚ÉŒÄ‚Ñ‚¾‚³‚ê‚é‰æ–Ê
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void PostRender()override;
private:
	CSprite m_sprite;
	CVector2 m_position = CVector2::Zero();
	CVector2 m_scale = CVector2::One();
	const float m_stopY = -6200.0f;
	const float m_speedmultiply = -95.0f;
	float m_timer = 0.0f;
	const int m_time = 3.0f;
	bool m_isgo = false;
	Fade* m_fade;
	//true‚È‚ç‰æ–ÊØ‚è‘Ö‚¦‚·‚é
	bool m_isWaitFadeout = false;
	bool m_iscredit = false;
};

