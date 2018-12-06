#pragma once
class Human:public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	//�A�j���[�V����
	void AnimationController();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_scale = { 100.0f,100.0f,100.0f };
	CVector3 m_position = { 300.0f,200.0f,0.0f };
	float m_animationspeed = 0.7f;
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
};

