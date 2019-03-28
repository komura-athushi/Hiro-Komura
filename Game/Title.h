#pragma once
class Fade;
//�^�C�g��
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void Update() override;
	void PostRender() override;
private:
	CSprite m_sprite,m_sprite2;								//�X�v���C�g
	CVector2 m_position = CVector2::Zero();					//�摜�̍��W
	CVector2 m_scale = CVector2::One();						//�摜�̑傫��
	Fade* m_fade;											//�t�F�[�h
	float m_currentAlpha = 0.0f;							//!<���݂̃��l�B
	bool m_isadd = true;									//a�l�����Z���邩�ǂ���
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
};

