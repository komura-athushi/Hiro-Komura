#pragma once
class Player;
class GameData;
class PlayerStatus;
//�����ɘb��������ƊX�𔭓W�ł���(�ݒ�)
class Human:public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	//�A�j���[�V����
	void AnimationController();
	//��]
	void Turn();
	//�����\��
	void PostRender() override;
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�X�𔭓W�ł��邩�ǂ���
	bool isLevelUpTown()
	{
		return m_developtown;
	}
	//�X�𔭓W������I
	void SetLevelUpTown()
	{
		m_leveluptown = true;
	}
	//�g�[�N���I���ɂ���
	void OnTalk()
	{
		m_ontalk = true;
	}
	//�g�[�N���I�t�ɂ���
	void OffTalk()
	{
		m_ontalk = false;
	}
	//�g�[�N��Ԃ��擾
	bool GetTalk() const
	{
		return m_ontalk;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	CVector3 m_position = { 300.0f,200.0f,0.0f };
	float m_animationspeed = 0.7f;
	CQuaternion m_rotation;
	bool m_developtown = false;								   //�X�𔭓W�ł��邩�ǂ���
	bool m_leveluptown = false;								   //�X�𔭓W�����܂�
	int m_townlevel = 0;									   //�X�̔��W���x��
	CFont m_font;                                              //�����\���N���X
	bool m_ontalk = false;									   //�g�[�N�I��
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
	};
	static const int m_necessarymaterial = 10;						   //�X�̔��W�ɕK�v�ȑf�ނ̐�
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	Player* m_player;
	PlayerStatus* m_playerstatus;
	GameData* m_gamedata;
};

