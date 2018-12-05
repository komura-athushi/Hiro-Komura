#pragma once
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
};

