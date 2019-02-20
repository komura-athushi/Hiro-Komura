#pragma once
#include "DemolisherWeapon/physics/character/CCharacterController.h"
class Sword;
class GameCamera;
class PlayerStatus;
class Human;
class Merchant;
class IEnemy;
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
	//����ȃL�����N�^�[�̃A�j���[�V�����Ƃ����̑��������
	void Animation();
	//�L�����N�^�[�̈ړ����v�Z
	void Move();
	//�U���֌W
	void Kougeki();
	//�A�j���[�V�����C�x���g
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//����̐؂�ւ�
	void SwitchWeapon();
	//����̐؂�ւ��̍ۂɃX�e�[�^�X�𔽉f������
	void WeaponStatus();
	//���@�̃X�e�[�^�X�𔽉f������
	void MagicStatus();
	//�V�t�^��������
	void Shihuta();
	//���X�^��������
	void Resta(const int& volume);
	//�v���C���[���_���[�W���󂯂����̏���
	void Damage(const int& attack);
	//���l�֌W
	void RelationHuman();
	//���l�֌W
	void RelationMerchant();
	//�v���C���[��PP�����l�����񕜂�����
	void RecoveryPP();
	//���x���A�b�v���̃G�t�F�N�g
	void LevelUp();
	//�I�[�g�^�[�Q�b�g
	void OutTarget();
	//�N���A�{�C�X
	void ClearVoice();
	//�v���C���[�̍��W���Z�b�g
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�v���C���[�̉�]���Z�b�g
	void SetRotation(const CQuaternion qRot)
	{
		m_rotation = qRot;
	}
	//�v���C���[�̉�]���擾
	CQuaternion GetRot() const
	{
		return m_rotation;
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
	//�V�t�^�����������I
	void SetShihuta()
	{
		m_Shihuta = true;
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
	//�_���W�������狒�_�ւ̑J�ڂ��\���ǂ������擾
	bool GetTransScene()
	{
		return m_transscene;
	}
	//�J�����̃|�C���^���Z�b�g
	void SetCamera(GameCamera* camera)
	{
		m_gamecamera = camera;
	}
	//�v���C���[���~������
	void SetStop()
	{
		m_stop = true;
	}
	//�v���C���[�𓮂���
	void SetMove()
	{
		m_stop = false;
	}
	//���̍��W���擾
	CVector3 GetSwordPosition() const
	{
		return m_swordposition;
	}
	//���̉�]���擾
	CQuaternion GetSwordRot() const
	{
		return m_swordrot;
	}
	//�v���C���[�������r�������擾
	bool GetAria() const
	{
		return m_state == enState_Aria;
	}
	//�����r�����̃v���C���[�̌������擾
	CVector3 GetAttack() const
	{
		return m_attacktarget;
	}
	//�v���C���[�̐��ʂ̃x�N�g�����擾
	CVector3 GetFront() const
	{
		return m_playerheikou;
	}
	//�v���C���[���^�[�Q�b�g��Ԃ��ǂ������擾
	bool GetisTarget() const
	{
		return m_targetdisplay;
	}
	//�^�[�Q�b�g�̍��W���擾
	CVector3 GetTarget() const
	{
		return m_target;
	}
	//�^�[�Q�b�g���b�N�����ǂ������擾
	bool GetisTargetLock() const
	{
		return m_targetlock;
	}
	//PP��ݒ�
	void SetPP(const int& pp) 
	{
		m_MaxPP = pp;
		m_PP = pp;
	}
	//�Q�[���N���A�I�I
	void SetGameClear()
	{
		m_state = enState_GameClear;
	}
private:
	bool m_cagliostro = false;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[
	CSprite m_sprite2;											//�Q�[���N���A�Ƃ��Q�[���I�[�o�[��
	CSprite m_targetsprite;										//�^�[�Q�b�g�̃X�v���C�g
	CSprite m_locktargetsprite;
	CSprite m_hp, m_hpframe;									//HP�֌W�̃e�N�X�`��
	CSprite m_statussprite;
	bool m_displaysprite = false;								//
    SuicideObj::CCollisionObj* m_collision;                     //�ۂ��R���W����
	CFont m_font;                                               //�����\���N���X
	Bone* m_bone;                                               //��
	PlayerStatus* m_playerstatus;                               //�v���C���[�X�e�[�^�X�̃|�C���^
	Human* m_human = nullptr;									//Human�N���X�̃|�C���^
	Merchant* m_merchant =  nullptr;							//Merchant�N���X�̃|�C���^
	int m_bonehand;                                             //�E���bone�̔ԍ�
	int m_bonecenter;                                           //center�̔ԍ�
	CVector3 m_savemovespeed;                                   //m_movespeed���L�����Ă���
	Sword* m_sword;                                             //Sword�N���X�̃|�C���^
	GameCamera* m_gamecamera = nullptr;                         //�J�����̃|�C���^
	CVector3 m_movespeed;                                       //�ړ����x
	CVector3 m_position = {0.0f,100.0f,00.0f};                  //���j�e�B�����̍��W
	CVector3 m_playerheikou = { 1.0f,0.0f,0.0f };               //�v���C���[�ƕ��s�ȃx�N�g��
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	CVector3 m_swordposition = CVector3::Zero();				//���̍��W
	CQuaternion m_swordrot = CQuaternion::Identity();			//���̉�]
	float m_timer = 0.0f;                                       //�U���̃N�[���^�C�}�[
	const int m_attacktime = 5;								    //�U���̃N�[���^�C��
	float m_timer2 = 0.0f;                                      //�_���[�W�̃N�[���^�C��
	CVector3 m_target = CVector3::Zero();
	CVector3 m_attacktarget = CVector3::Zero();
	bool m_ontarget = false;									//�^�[�Q�b�g�\�����邩�ǂ���
	bool m_gameover = false;                                    //�Q�[���I�[�o�[���ǂ���
	bool m_gameclear = false;									//�Q�[���N���A���ǂ���
	bool m_isjump = false;                                      //�W�����v���Ă��邩�ǂ���
	bool m_stop = false;										//�v���C���[���~������
	bool m_transscene = false;									//�X�e�[�W�J�ڂ����̂����ǂ���
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	//�ړ����x��Z
	const float m_multiply = 400.0f;                            //���j�e�B�����̈ړ����x�𒲐�����
	CQuaternion m_rotation;                                     //�N�H�[�^�j�I��
	CCharacterController m_charaCon;                            //�L�����N�^�[�̓����蔻��Ƃ��ړ��Ƃ�
	const float m_lvheight = 20.0f;								//���x���A�b�v���̃G�t�F�N�g�o������y���W�ɉ��Z������
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
		enAnimationClip_aria,
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
		enState_Aria,
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
	int m_WeaponNumber;
	const wchar_t* m_SwordName;                                 //�������̕���̖��O
	int m_MagicId;                                              //�g���閂�@�̔ԍ�
	const wchar_t* m_MagicName;						            //���@�̖��O
	float m_DamageRate;								       	    //���@�̃_���[�W�{��
	int m_PPCost;										        //���@����̂ɕK�v��PP
	bool m_damage = false;                                      //�_���[�W���󂯂��I
	bool m_isbutton = false;                                    //����؂�ւ��̎��Ɏg�����
	float m_PPtimer = 0.0f;										//PP�����񕜂̃N�[���^�C��
	int m_PPtime = 40;											//PP�����񕜂̃^�C��
	static const int m_AttackRecoveryPP = 5;					//�G�l�~�[�ɍU�������Ƃ��ɉ񕜂���PP�̉񕜗�
	bool m_Shihuta = false;										//�V�t�^��������Ȃ�true
	int m_ShihutaAttack = 0;									//�V�t�^�ɂ������Ă���Ƃ��ɃV�t�^�O�̍U���͂�ۑ�
	float m_Shihutatimer = 0.0f;								//�V�t�^�̂������Ă��鎞��
	float m_Shihutatime = 360.0f * 10.0f;						//�V�t�^�̂����鎞�Ԃ𐧌�
	const float m_AttackMultiply = 1.3f;						//�V�t�^�������������̍U���͂��グ��{��
	const float m_frame = 40.0f;								//40fps
	bool m_clear_over_voice = false;							//�Q�[���I�[�o�[���邢�̓Q�[���N���A�̃{�C�X�𔭐����������ǂ���
	const float m_voicevolume = 3.5f;							//�{�C�X�̉���
	const float m_lvupvollume = 2.0f;							//���x���A�b�v��SE�̉���
	bool m_targetdisplay = false;								//�^�[�Q�b�e�B���O��Ԃ��ǂ���
	const float m_distancetarget = 1400.0f * 1400.0f;			//�^�[�Q�b�g���L���ȋ���
	const float m_degreemultiply = 0.3f;						//�^�[�Q�b�g�̋����␳
	//���C�t�\���̏����̉��̒���
	const float m_side = 384.0f;
	//���C�t�\���̏����̏c�̒���
	const float m_length = 64.0f;
	//���C�t�̌��̂�̒���
	const float m_side2 = 512.0f;
	const float m_length2 = 128.0f;
	const CVector2 m_protspriteposition = { 0.0f,0.0f };
	CVector2 m_spriteposition = { 0.0f ,0.0f };
	const float m_morugantime = 300.0f;
	const float m_height = 60.0f;
	bool m_aria = false;										//�����r�������ǂ���
	IEnemy* m_enemy = nullptr;
	bool m_targetlock = false;									//�^�[�Q�b�g���b�N�����ǂ���
	bool m_displaystatus = false;
};

