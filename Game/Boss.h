#pragma once
#include "Player.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Boss : public IEnemy
{
public:
	Boss();
	~Boss();
	bool Start() override;
	void Update() override;
	void Attack();       										//�U��
	void Chase();												//�ǐ�
	void AnimationController();									//�A�j���[�V�����̍Đ�
	void Damage();												//�_���[�W���󂯂����̃A�N�V����
	void Turn();												//�L�����N�^�[�̌������v�Z
	void Dead();												//�G�l�~�[�����񂾂Ƃ��̏���
	//�A�j���[�V�����C�x���g
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void SetPlayer(Player* player)								//�v���C���[�̃|�C���g���Z�b�g
	{
		m_player = player;
	}
	/*void SetPosition(const CVector3& pos)
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
	}*/
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_attack,
		enAnimationClip_damage,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle_Run,
		enState_Attack,
		enState_Damage,
		enState_Dead,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle_Run;
	CVector3 m_oldpos = { 30.0f,100.0f,1500.0f };               //�{�X�̏����ʒu
	CVector3 m_position = { 30.0f,100.0f,1500.0f };				//�{�X�̍��W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };						//�{�X�̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//���j�e�B�����̌����ƕ��s�ȃx�N�g��
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	Stage1* m_stage1;
	int m_timer = 0;											//�U���̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	float m_r = 80.0f;                                          //�R���W�����̔��a
	float m_collisionheight = 50.0f;                            //�R���W������m_position����ǂꂾ����ɂ����邩
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 50;                              //�ő�HP
	static const int m_Attack = 20;                             //�U����
	static const int m_EXP = 20;                                //�o���l
	bool m_gekiha = false;
};
