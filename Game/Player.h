#pragma once
#include "DemolisherWeapon/physics/character/CCharacterController.h"
//�v���C���[�ł�
class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	//�L�����N�^�[�̌������v�Z
	void Turn();
	//�L�����N�^�[�̃A�j���[�V������ݒ�
	void AnimationController();
	//�L�����N�^�[�̈ړ����v�Z
	void Move();
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
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_movespeed;                                       //�ړ����x
	CVector3 m_position = {0.0f,100.0f,00.0f};                  //���j�e�B�����̍��W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
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

