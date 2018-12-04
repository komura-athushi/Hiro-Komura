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
	
};

