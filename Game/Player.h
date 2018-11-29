#pragma once
#include "DemolisherWeapon/physics/character/CCharacterController.h"

class Sword;
class GameCamera;
class PlayerStatus;
//�v���C���[�ł�
class Player:public IGameObject
{
public:
	//�J���I�X�g������񃂁[�h��ݒ�
	void Cagliostro()
	{
		m_cagliostro = true;
	}
	//�J���I�X�g������񃂁[�h���ǂ������擾
	bool isCagliostro()
	{
		return m_cagliostro;
	}
	Player();
	~Player();
	bool Start();
	void Update();
	//�����\��
	void PostRender()override;
	//���j�e�B������\�����鎞�̏���
	void unityChan();
	//�͂��[�����������B���p�t�̃J���I�X�g�����恙��낵���ˁ�
	void cagliostro();
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
	//�A�j���[�V�����C�x���g
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//�U���̐؂�ւ�
	void SwitchWeapon();
	//����̐؂�ւ��̍ۂɃX�e�[�^�X�𔽉f������
	void WeaponStatus();
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
	int GetHP() const
	{ 
		return m_HP;
	}
	//�Q�[���I�[�o�[���ǂ������擾
	bool GetGameOver() const
	{
		return m_gameover;
	}
	//�Q�[���N���A���ǂ������擾
	bool GetGameClear() const
	{
		return m_gameclear;
	}
	//�J�����̃|�C���^���Z�b�g
	void SetCamera(GameCamera* camera)
	{
		m_gamecamera = camera;
	}
	//�v���C���[���_���[�W���󂯂����̏���
	void Damage(const int& attack);
private:
	bool m_cagliostro = false;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
    SuicideObj::CCollisionObj* m_collision;                     //�ۂ��R���W����
	CFont m_font;                                               //�����\���N���X
	Bone* m_bone;                                               //��
	PlayerStatus* m_playerstatus;                               //�v���C���[�X�e�[�^�X�̃|�C���^
	int m_bonehand;                                             //�E���bone�̔ԍ�
	int m_bonecenter;                                           //center�̔ԍ�
	CVector3 m_savemovespeed;                                   //m_movespeed���L�����Ă���
	Sword* m_sword;                                             //Sword�N���X�̃|�C���^
	GameCamera* m_gamecamera;                                   //�J�����̃|�C���^
	CVector3 m_movespeed;                                       //�ړ����x
	CVector3 m_position = {0.0f,100.0f,00.0f};                  //���j�e�B�����̍��W
	CVector3 m_playerheikou = { 0.0f,0.0f,0.0f };               //�v���C���[�ƕ��s�ȃx�N�g��
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	int m_timer = 0;                                            //�U���̃N�[���^�C��
	int m_timer2 = 0;                                           //�_���[�W�̃N�[���^�C��
	bool m_gameover = false;                                    //�Q�[���I�[�o�[���ǂ���
	bool m_gameclear = false;									//�Q�[���N���A���ǂ���
	bool m_isjump = false;                                      //�W�����v���Ă��邩�ǂ���
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	//�ړ����x��Z
	const float m_multiply = 400.0f;                            //���j�e�B�����̈ړ����x�𒲐�����
	CQuaternion m_rotation;                                     //�N�H�[�^�j�I��
	CCharacterController m_charaCon;                            //�L�����N�^�[�̓����蔻��Ƃ��ړ��Ƃ�
	const float m_r = 40.0f;                                    //�R���W�����̔��a
	const float m_collisionUp = 50.0f;                          //�R���W�����̍��W��y�����Z
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_Clear,
		enAnimationClip_attack,
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
		enState_Attack,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	//�v���C���[�̐F�X�ȃX�e�[�^�X
	int m_Level;                                                //���x��
	int m_Exp;                                                  //�݌v�o���l
	int m_NextExp;                                              //���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_MaxHP;                                                //�ő�HP
	int m_HP;                                                   //HP
	int m_MaxPP;                                                //�ő�PP
	int m_PP;                                                   //PP
    int m_Attack;                                               //�U����
	int m_Mattack;                                              //���@�U����
	int m_SwordId;                                              //�������̕���̔ԍ�
	const wchar_t* m_SwordName;                                 //�������̕���̖��O
	int m_MagicId;                                              //�g���閂�@�̔ԍ�
	bool m_damage = false;                                      //�_���[�W���󂯂��I
	bool m_isbutton = false;                                    //����؂�ւ��̎��Ɏg�����
};

