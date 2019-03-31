#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Player;
class Boss2 : public IEnemy
{
public:
	Boss2();
	~Boss2();
	bool Start() override;
	void Update() override;
	//�{�X�̍s�����`�F���W
	void ChangeBehavior();										
	void Chase();												//�ǐ�
	void Turn();												//�L�����N�^�[�̌������v�Z
	void AnimationController();									//�A�j���[�V�����̍Đ�
	void Dead();												//�h���S�������񂾂Ƃ��̏���
	//�A�j���[�V�����C�x���g
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	void SetPlayer(Player* player)								//�v���C���[�̃|�C���g���Z�b�g
	{
		m_player = player;
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
		enAnimationClip_aria,
		enAnimationClip_aria2,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Attack1,
		enState_Aria,
		enState_Aria2,
		enState_Death,
	};
	EnState m_state = enState_Idle;								//�A�j���[�V��������
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//�h���S���̏����ʒu
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//�h���S���̍��W
	//�X�P�[����100.0f
	CVector3 m_scale = { 80.0f,80.0f,80.0f };				//�h���S���̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	CVector3 m_heikou = { 0.0f,0.0f,0.0f };                     //�h���S���̌����Ă�������ɕ��s�ȃx�N�g��
	float m_enemyspeed = 2.5f;									//�h���S���̈ړ��̔{��
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//���j�e�B�����̌����ƕ��s�ȃx�N�g��
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	CFont m_font;												//�����\���N���X
	bool m_disp = false;										//�_���\�����邩�ǂ���
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	Stage1* m_stage1;
	float m_r = 180.0f;                                         //�R���W�����̔��a
	const float m_collisionheight = 150.0f;						//�R���W������m_position����ǂꂾ����ɂ����邩
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 25000;                             //�ő�HP
	static const int m_Attack1 = 20;							//�Ђ������̍U����
	static const int m_Attack2 = 30;							//�v���X�̍U����
	static const int m_EXP = 50000;                               //�o���l
	static const int m_dropChances[];				            //�h���S���̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //delete���邩�ǂ���
	const int m_attackfire = 50;								//�t�@�C���[�̍U����
	const float m_attackr = 80.0f;								//�U�����ɔ���������R���W�����̑傫��
	const int m_attack1 = 500;
};

