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
	float m_currentAlpha = 0.0f;		//!<���݂̃��l�B
	bool m_isadd = true;			    //a�l�����Z���邩�ǂ���
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
};

