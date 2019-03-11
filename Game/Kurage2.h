#pragma once
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
class Game;
//�����_���Ɉړ����Ė��@�ōU�����Ă����ԖڂɎア���N���Q
class Kurage2 :public IEnemy
{
public:
	Kurage2();
	~Kurage2();
	bool Start();
	void Update();
	void Chase();
	void Attack();
	void Aria();
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
	CVector3 m_protposition = CVector3::Zero();
	const float m_r = 60.0f;                                    //�R���W�����̔��a
	const float m_collisionheight = 40.0f;                      //�R���W������m_position����ǂꂾ����ɂ����邩
	//�N���Q�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 300;                             //�ő�HP
	static const int m_Attack = 35;                             //�U����
	static const int m_EXP = 35;                                //�o���l
	//�w�b�_�[�t�@�C���ł͐錾�����A��`��cpp�t�@�C���ɏ����Ă�������
	static const int m_dropChances[];                           //�G�l�~�[�̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];					//�G�l�~�[�̃h���b�v����f�ނ̊m��
	static const int m_meseta = 80;								//�h���b�v���郁�Z�^�̑�̂̊z
	bool m_gekiha = false;                                      //delete���邩�ǂ���
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	Game* m_game;
	enum State {
		enState_Chase,
		enState_Pose,
		enState_Attack,
	};
	State m_state = enState_Pose;
	const float m_chasedistance = 2000.0f * 2000.0f;
	const float m_attackdistance = 700.0f * 700.0f;
	bool m_isaria = false;
	const float m_frame = 40.0f;
	const float m_movespeedmultiply = 4.0f;
	float m_dethtimer = 0.0f;
	const int m_dethtime = 5;
	float m_chasetimer = 0.0f;
	const int m_chasetime = 50;
	float m_stoptimer = 0.0f;
	const int m_stoptime = 20;
	float m_movetimer = 0.0f;
	const int m_movetime = 180;
	float m_attacktimer = 0.0f;
	const int m_attacktime = 50;
};


