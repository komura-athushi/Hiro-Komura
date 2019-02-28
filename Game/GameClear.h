#pragma once
class Fade;
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void PostRender()override;
private:
	CSprite m_sprite,m_sprite2;
	CVector2 m_position = { 0.0f, 0.0f };
	CVector2 m_scale = { 1.0f,1.0f };
	Fade* m_fade;
	//true‚È‚ç‰æ–ÊØ‚è‘Ö‚¦‚·‚é
	bool m_isWaitFadeout = false;
	bool m_iscredit = false;
};

