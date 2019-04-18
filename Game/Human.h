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
	bool Start() override;
	void Update() override;
	//�A�j���[�V����
	void AnimationController();
	//��]
	void Turn();
	//�X�𔭓W������I
	void SetLevelUpTown();
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
	CVector3 m_scale = { 2.0f,2.0f,2.0f };						//���f���̑傫��
	CVector3 m_position = { 300.0f,200.0f,0.0f };			    //���f���̍��W
	CSprite m_sprite;											//�摜
	float m_animationspeed = 0.7f;								//�A�j���[�V�����̍Đ����x
	CQuaternion m_rotation;										//��]
	bool m_developtown = false;								    //�X�𔭓W�ł��邩�ǂ���
	bool m_leveluptown = false;								    //�X�𔭓W�����܂�
	int m_townlevel = 0;									    //�X�̔��W���x��
	CFont m_font;                                               //�����\���N���X
	bool m_ontalk = false;									    //�g�[�N�I��
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
	};
	static const int m_necessarymaterial = 10;				    //�X�̔��W�ɕK�v�ȑf�ނ̐�
	AnimationClip m_animClip[enAnimationClip_num];	
	EnState m_state = enState_Idle;								//�X�e�[�g
	Player* m_player = nullptr;									//�v���C���[
	PlayerStatus* m_playerstatus = nullptr;						//�v���C���[�X�e�[�^�X
	GameData* m_gamedata = nullptr;								//�Q�[���f�[�^
	bool m_istalk = true;										//�b���Ă�H
};

