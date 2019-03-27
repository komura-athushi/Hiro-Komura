#pragma once
class Fade;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void PostRender() override;
private:
	CSprite m_sprite,m_sprite2;
	CVector2 m_position = { 0.0f, 0.0f };
	CVector2 m_scale = { 1.0f,1.0f };
	Fade* m_fade;
	float m_currentAlpha = 0.0f;		//!<Œ»Ý‚Ìƒ¿’lB
	bool m_isadd = true;			    //a’l‚ð‰ÁŽZ‚·‚é‚©‚Ç‚¤‚©
	//true‚È‚ç‰æ–ÊØ‚è‘Ö‚¦‚·‚é
	bool m_isWaitFadeout = false;
};

