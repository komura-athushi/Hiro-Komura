#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Player;
class BossAttack;
class Boss2 : public IEnemy
{
public:
	Boss2();
	~Boss2();
	bool Start() override;
	void Update() override;
	void Attack();       										//�U��
	void Chase();												//�ǐ�
	void Damage();												//�_���[�W���󂯂����̃A�N�V����
	void Turn();												//�L�����N�^�[�̌������v�Z
	void AnimationController();									//�A�j���[�V�����̍Đ�
	void Dead();												//�h���S�������񂾂Ƃ��̏���
	//�����\��
	void PostRender()override;
	void SetPlayer(Player* player)								//�v���C���[�̃|�C���g���Z�b�g
	{
		m_player = player;
	}
	void SetBossAttack(BossAttack* bossattack)					//BossAttack�̃|�C���g���Z�b�g
	{
		m_bossattack = bossattack;
	}
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetStage1(Stage1* stage1)
	{
		m_stage1 = stage1;
	}
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_attack1,
		enAnimationClip_attack2,
		enAnimationClip_attack3,
		enAnimationClip_damage,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle_Run,
		enState_Attack1,
		enState_Attack2,
		enState_Attack3,
		enState_Damage,
		enState_Dead,
	};
	EnState m_state = enState_Idle_Run;
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//�h���S���̏����ʒu
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//�h���S���̍��W
	//�X�P�[����300.0f
	CVector3 m_scale = { 100.0f,100.0f,100.0f };				//�h���S���̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	float m_enemyspeed = 2.5f;									//�h���S���̈ړ��̔{��
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//���j�e�B�����̌����ƕ��s�ȃx�N�g��
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	BossAttack* m_bossattack;									//BossAttack�N���X�̃|�C���^
	CFont m_font;												//�����\���N���X
	bool m_disp = false;										//�_���\�����邩�ǂ���
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	Stage1* m_stage1;
	int m_timer = 0;											//�U���̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	int m_atk3timer = 0;										//�U��3�̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	int m_atk3count = 0;
	int m_cooltime = 400;										//�U�����I�������̃N�[���^�C��
	int m_atk3cooltime = 300;									//�U��3���I�������̃N�[���^�C��
	int m_posttiming = 30;										//�U��������O�̒��ӂ̃^�C�~���O
	int m_atktype = 0;											//�U���̎��
	float m_r = 150.0f;                                         //�R���W�����̔��a
	float m_collisionheight = 270.0f;                           //�R���W������m_position����ǂꂾ����ɂ����邩
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 900;                             //�ő�HP
	static const int m_Attack1 = 20;							//�U����1
	static const int m_Attack2 = 30;							//�U����2
	static const int m_Attack3 = 40;							//�U����3
	static const int m_EXP = 500;                               //�o���l
	static const int m_dropChances[];				            //�h���S���̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //delete���邩�ǂ���
};
