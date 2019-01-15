#pragma once
class Fade;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void PostRender()override;
private:
	CSprite m_sprite;
	CVector2 m_position = { 0.0f, 0.0f };
	CVector2 m_scale = { 1.0f,1.0f };
	Fade* m_fade;
	//true‚È‚ç‰æ–ÊØ‚è‘Ö‚¦‚·‚é
	bool m_isWaitFadeout = false;
};

