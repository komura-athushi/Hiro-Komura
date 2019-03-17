#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Game;
class Player;
class BossAttack;
class Boss : public IEnemy
{
public:
	Boss();
	~Boss();
	bool Start() override;
	void Update() override;
	void Attack();       										//�U��
	void Damage();												//�_���[�W���󂯂����̃A�N�V����
	void Turn();												//�L�����N�^�[�̌������v�Z
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
	void SetStage1(Game* stage1)
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
	CVector3 m_oldpos = { 0.0f,0.0f,0.0f };						//�{�X�̏����ʒu
	CVector3 m_position = { 0.0f,0.0f,0.0f };					//�{�X�̍��W
	CVector3 m_scale = { 1.5f,1.5f,1.5f };						//�{�X�̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//���j�e�B�����̌����ƕ��s�ȃx�N�g��
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	BossAttack* m_bossattack;									//BossAttack�N���X�̃|�C���^
	CFont m_font;												//�����\���N���X
	bool m_disp = false;										//�_���\�����邩�ǂ���
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	Game* m_stage1;
	int m_timer = 0;											//�U���̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	int m_atk3timer = 0;										//�U��3�̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	int m_atk3count = 0;
	int m_cooltime = 200;										//�U�����I�������̃N�[���^�C��
	int m_atk3cooltime = 300;									//�U��3���I�������̃N�[���^�C��
	int m_posttiming = 30;										//�U��������O�̒��ӂ̃^�C�~���O
	int m_atktype = 0;											//�U���̎��
	float m_r = 150.0f;                                         //�R���W�����̔��a
	float m_collisionheight = 270.0f;                           //�R���W������m_position����ǂꂾ����ɂ����邩
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 1800;                             //�ő�HP
	static const int m_Attack1 = 50;							//�U����1
	static const int m_Attack2 = 100;							//�U����2
	static const int m_Attack3 = 90;							//�U����3
	static const int m_EXP = 500;                               //�o���l
	static const int m_dropChances[];				            //�G�l�~�[�̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	float m_deathtimer = 0.0f;
	const int m_attack1 = 50;
	const int m_attack2 = 60;
	const int m_attack3 = 80;
};

