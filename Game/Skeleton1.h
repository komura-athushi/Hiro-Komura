#pragma once
#include "Weapon.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
class Game;
//��Ԏア�X�P���g��
class Skeleton1 : public IEnemy
{
public:
	Skeleton1();
	~Skeleton1();
	bool Start() override;
	void Update() override;
	//�ǐ�
	void Chase();			
	//�A�j���[�V�����̍Đ�
	void AnimationController();					
	//�_���[�W���󂯂����̃A�N�V����
	void Damage();						
	//�L�����N�^�[�̌������v�Z
	void Turn();								
	//�G�l�~�[�����񂾂Ƃ��̏���
	void Dead();											
	//�A�j���[�V�����C�x���g
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void SetPlayer(Player* player)								//�v���C���[�̃|�C���g���Z�b�g
	{
		m_player = player;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//��]��ݒ�
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	void SetGame(Game* game)
	{
		m_game = game;
	}
	void SetOldPosition(const CVector3& pos)
	{
		m_oldpos = pos;
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
	CVector3 m_heikou = { 0.0f,0.0f,0.0f };                     //�S�̌����Ă�������ɕ��s�ȃx�N�g��
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;                                     //�N�H�[�^�j�I��
	Game* m_game;
	int m_timer = 0;											//�U���̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	const float m_r = 70.0f;                                    //�R���W�����̔��a
	const float m_attackr = 90.0f;                              //�U�������Ƃ��ɔ���������R���W�����̔��a
	const float m_collisionheight = 50.0f;                      //�R���W������m_position����ǂꂾ����ɂ����邩
	//Oni�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 450;                             //�ő�HP
	static const int m_Attack = 140;                            //�U����
	static const int m_EXP = 480;                               //�o���l
	//�w�b�_�[�t�@�C���ł͐錾�����A��`��cpp�t�@�C���ɏ����Ă�������
	static const int m_dropChances[];                           //�G�l�~�[�̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];					//�G�l�~�[�̃h���b�v����f�ނ̊m��
	static const int m_meseta = 100;							//�h���b�v���郁�Z�^�̑�̂̊z
	bool m_gekiha = false;                                      //delete���邩�ǂ���
	CVector3 m_effectscale = { 20.0f,20.0f,15.0f };				//�G�t�F�N�g�̑傫��
};

