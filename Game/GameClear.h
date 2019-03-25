#pragma once
class Fade;
//�Q�[�����N���A�����Ƃ��ɌĂт��������
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
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	bool m_iscredit = false;
};

