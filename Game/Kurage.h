#pragma once
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Player;
//�v���C���[�ɋ߂Â��čU�����Ă����Ԏア�΂̃N���Q
class Kurage:public IEnemy
{
public:
	Kurage();
	~Kurage();
	bool Start() override;
	void Update() override;
	//�ړ�
	void Move();
	//�U��
	void Attack();
	//�r��
	void Aria();
	//�U���Ɉڍs�H
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
	//�傫����ݒ�
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
	CVector3 m_protposition = CVector3::Zero();					//�ŏ��ɋ������W
	const float m_r = 60.0f;                                    //�R���W�����̔��a
	const float m_collisionheight = 40.0f;                      //�R���W������m_position����ǂꂾ����ɂ����邩
	//�N���Q�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 150;                             //�ő�HP
	static const int m_Attack = 20;                             //�U����
	static const int m_EXP = 20;                                //�o���l
	//�w�b�_�[�t�@�C���ł͐錾�����A��`��cpp�t�@�C���ɏ����Ă�������
	static const int m_dropChances[];                           //�G�l�~�[�̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];					//�G�l�~�[�̃h���b�v����f�ނ̊m��
	static const int m_meseta = 30;								//�h���b�v���郁�Z�^�̑�̂̊z
	bool m_gekiha = false;                                      //delete���邩�ǂ���
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	//�s���p�^�[��
	enum State {
		enState_Chase,											//�ړ�
		enState_Pose,											//�ҋ@
		enState_Attack,											//�U��
	};
	bool m_isaria = false;										//�r���������ǂ���
	const float m_chasedistance = 1200.0f * 1200.0f;			//�v���C���[�Ƃ̋��������ȉ��ɂȂ�Έړ�����
	const float m_attackdistance = 130.0f * 130.0f;				//�v���C���[�Ƃ̋��������ȉ��ɂȂ�΍U������
	State m_state = enState_Pose;								//�X�e�[�g
	const float m_frame = 40.0f;
	const float m_movespeedmultiply = 7.0f;						//�ړ����x
	float m_dethtimer = 0.0f;									//�|�����܂ł�����Ǝ��Ԃ�����
	const int m_dethtime = 5;
	float m_chasetimer = 0.0f;									
	const int m_chasetime = 30;
	float m_stoptimer = 0.0f;
	const int m_stoptime = 20;
	float m_movetimer = 0.0f;
	const int m_movetime = 130;
	float m_attacktimer = 0.0f;
	const int m_ariatime = 20;
	const int m_attacktime = 60;
};

