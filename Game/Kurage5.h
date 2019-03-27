#pragma once
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
class Game;
//�X�e�[�W2�̑傫�ڂ̃N���Q
class Kurage5 :public IEnemy
{
public:
	Kurage5();
	~Kurage5();
	bool Start() override;
	void Update() override;
	//�ړ�
	void Chase();
	//�U��
	void Attack();
	//�r��
	void Aria();
	//�U���ɓ]���� 
	void ChangeAttack();
	void SetPlayer(Player* player)								//�v���C���[�̃|�C���g���Z�b�g
	{
		m_player = player;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetGame(Game* game)
	{
		m_game = game;
	}
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	CVector3 m_position = CVector3::Zero();				        //�S�̍��W
	CVector3 m_scale = CVector3::One();					        //�S�̃X�P�[��
	CVector3 m_movespeed = CVector3::Zero();					//�ړ����x
	CVector3 m_protposition = CVector3::Zero();					//�����ɋ������W
	const float m_r = 110.0f;                                   //�R���W�����̔��a
	const float m_collisionheight = 80.0f;                      //�R���W������m_position����ǂꂾ����ɂ����邩
	//�N���Q�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 2000;                            //�ő�HP
	static const int m_Attack = 450;                            //�U����
	static const int m_EXP = 4790;                              //�o���l
	//�w�b�_�[�t�@�C���ł͐錾�����A��`��cpp�t�@�C���ɏ����Ă�������
	static const int m_dropChances[];                           //�G�l�~�[�̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];					//�G�l�~�[�̃h���b�v����f�ނ̊m��
	static const int m_meseta = 600;							//�h���b�v���郁�Z�^�̑�̂̊z
	bool m_gekiha = false;                                      //delete���邩�ǂ���
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	Game* m_game;												
	//�s���p�^�[��
	enum State {
		enState_Chase,											//�ړ�	
		enState_Pose,											//�ҋ@
		enState_Attack,											//�U��
	};
	State m_state = enState_Pose;
	const float m_chasedistance = 1500.0f * 1500.0f;
	const float m_attackdistance = 1200.0f * 1200.0f;
	const float m_magicspeed = 0.4f;
	bool m_isaria = false;
	const float m_frame = 40.0f;
	const float m_movespeedmultiply = 3.5f;
	float m_dethtimer = 0.0f;
	const int m_dethtime = 5;
	float m_chasetimer = 0.0f;
	const int m_chasetime = 50;
	float m_stoptimer = 0.0f;
	const int m_stoptime = 80;
	float m_movetimer = 0.0f;
	const int m_movetime = 200;
	float m_attacktimer = 0.0f;
	const int m_ariatime = 30;
	const int m_attacktime = 70;
	CVector3 m_castscale = { 20.0f,20.0f,20.0f };
};
