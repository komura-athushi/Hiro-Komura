#pragma once
#include "DemolisherWeapon/physics/character/CCharacterController.h"
class Sword;
class GameCamera;
class PlayerStatus;
//�v���C���[�ł�
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	//�����\��
	void PostRender()override;
	//�v���C���[�X�e�[�^�X�̃N���X�̃����o�ϐ����v���C���[�̃X�e�[�^�X�ɔ��f
	void Status();
	//�L�����N�^�[�̌������v�Z
	void Turn();
	//�L�����N�^�[�̃A�j���[�V�������Đ�
	void AnimationController();
	//����ȃL�����N�^�[�̃A�j���[�V���������߂�
	void Animation();
	//�L�����N�^�[�̈ړ����v�Z
	void Move();
	//�U���֌W
	void Kougeki();
	//�v���C���[�X�e�[�^�X�N���X�̃|�C���^��ݒ�
	void SetPlayerStatus(PlayerStatus* ps)
	{
		m_playerstatus = ps;
	}
	//�v���C���[�̍��W���Z�b�g
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�v���C���[�̍��W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�v���C���[��HP���擾
	float GetHP() const
	{
		return m_HP;
	}
	//�Q�[���I�[�o�[���ǂ������擾
	bool GetGameOver() const
	{
		return m_gameover;
	}
	//�J�����̃|�C���^���Z�b�g
	void SetCamera(GameCamera* camera)
	{
		m_gamecamera = camera;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CFont m_font;                                               //�����\���N���X
	Bone* m_bone;                                               //��
	PlayerStatus* m_playerstatus;                               //�v���C���[�X�e�[�^�X�̃|�C���^
	int m_bonehand;                                             //�E���bone�̔ԍ�
	CVector3 m_savemovespeed;                                   //m_movespeed���L�����Ă���
	Sword* m_sword;                                             //Sword�N���X�̃|�C���^
	GameCamera* m_gamecamera;                                   //�J�����̃|�C���^
	CVector3 m_movespeed;                                       //�ړ����x
	CVector3 m_position = {0.0f,100.0f,00.0f};                  //���j�e�B�����̍��W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	int m_timer = 0;                                            //�U���̃N�[���^�C��
	bool m_gameover = false;                                    //�Q�[���I�[�o�[���ǂ���
	bool m_isjump = false;                                      //�W�����v���Ă��邩�ǂ���
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	//�ړ����x��Z
	const float m_multiply = 400.0f;                            //���j�e�B�����̈ړ����x�𒲐�����
	CQuaternion m_rotation;                                     //�N�I���e�[�V����
	CCharacterController m_charaCon;                            //�L�����N�^�[�̓����蔻��Ƃ��ړ��Ƃ�
	                               
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_Clear,
		enAnimationClip_Test,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Jump,
		enState_Damage,
		enState_GameOver,
		enState_WaitStartGameClear,
		enState_GameClear,
		enState_Test,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	//�v���C���[�̐F�X�ȃX�e�[�^�X
	int m_level;                                                //���x��
	float m_MaxHP;                                              //�ő�HP
	float m_HP;                                                 //HP
	float m_MaxPP;                                              //�ő�PP
	float m_PP;                                                 //PP
	float m_Attack;                                             //�U����
	float m_Defense;                                            //�h���
};

