#pragma once
#include "Player.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Oni : public IEnemy
{
public:
	Oni();
	~Oni();
	bool Start() override;
	void Update() override;
	void Attack() override;										//�U��
	void Chase();												//�ǐ�
	void AnimationController();									//�A�j���[�V�����̍Đ�
	void Damage();												//�_���[�W���󂯂����̃A�N�V����
	void Turn();												//�L�����N�^�[�̌������v�Z
	void Dead();												//�G�l�~�[�����񂾂Ƃ��̏���
	void SetPlayer(Player* player)								//�v���C���[�̃|�C���g���Z�b�g
	{
		m_player = player;
	}

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
	CVector3 m_oldpos = { 30.0f,100.0f,1500.0f };               //�S�̏����ʒu
	CVector3 m_position = { 30.0f,100.0f,1500.0f };				//�S�̍��W
	CVector3 m_scale = { 10.0f,10.0f,10.0f };					//�S�̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	int m_timer;												//�U���̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	//�v���C���[�̐F�X�ȃX�e�[�^�X
	int m_level;                                                //���x��
	float m_MaxHP;                                              //�ő�HP
	float m_HP;                                                 //HP
	float m_MaxPP;                                              //�ő�PP
	float m_PP;                                                 //PP
	float m_Attack;                                             //�U����
	float m_Defense;                                            //�h���
};

