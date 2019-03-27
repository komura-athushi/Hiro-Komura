#pragma once
class Fade;
//�Q�[�����N���A�����Ƃ��ɌĂт��������
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
	void PostRender()override;
private:
	CSprite m_sprite;									//�X�v���C�g
	CVector2 m_position = CVector2::Zero();				//�X�v���C�g�̍��W
	CVector2 m_scale = CVector2::One();					//�X�v���C�g�̑傫��
	const float m_stopY = -6200.0f;						//�X�v���C�g��y���W�����l�Œ�~������
	const float m_speedmultiply = -95.0f;				//y���W�𖈃t���[���{����
	float m_timer = 0.0f;								//�^�C�}�[
	const int m_time = 3.0f;							//�^�C�}�[�̐���
	bool m_isgo = false;								//true��y���W�𓮂���
	Fade* m_fade;										//�t�F�[�h
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
};

