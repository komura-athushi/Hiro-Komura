#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Game;
class Player;
class Boss : public IEnemy
{
public:
	Boss();
	~Boss();
	bool Start() override;
	void Update() override;
	void Turn();												//�L�����N�^�[�̌������v�Z
	//�p�^�[��1
	void One();
	//�p�^�[��2
	void Two();
	//�p�^�[��3
	void Three();
	//�}�W�b�N�X�t�B�A
	void MG();			
	//�t���[�Y�V���b�g
	void FS();
	//�G�A���o�[�X�g
	void EB();
	//�r��
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
	void SetStage1(Game* stage1)
	{
		m_stage1 = stage1;
	}
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
	//�s�����J�n�������ǂ���
	bool GetisStart() const
	{
		return m_start;
	}
private:
	enum State {
		enState_One,						//��Ԗڂ̍s���p�^�[��
		enState_Two,						//��Ԗڂ̍s���p�^�[��
		enState_Three,						//�O�Ԗڂ̍s���p�^�[��
	};
	State m_state = enState_One;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	CVector3 m_oldpos = { 0.0f,0.0f,0.0f };						//�{�X�̏����ʒu
	CVector3 m_position = { 0.0f,0.0f,0.0f };					//�{�X�̍��W
	CVector3 m_scale = { 1.5f,1.5f,1.5f };						//�{�X�̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//���j�e�B�����̌����ƕ��s�ȃx�N�g��
	Player* m_player = nullptr;									//�v���C���[�N���X�̃|�C���^
	CFont m_font;												//�����\���N���X
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //���j�e�B�����̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	Game* m_stage1 = nullptr;
	float m_r = 150.0f;                                         //�R���W�����̔��a
	const float m_height = 220.0f;                              //�R���W������m_position����ǂꂾ����ɂ����邩
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 5000;                            //�ő�HP
	static const int m_AttackMG = 75;							//�}�W�X�t�B
	static const int m_AttackFS = 90;							//�t���[�Y�V���b�g
	static const int m_AttackEB = 185;							//�G�A���A���o�[�X�g
	static const int m_EXP = 5000;                              //�o���l
	static const int m_dropChances[];				            //�G�l�~�[�̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	float m_deathtimer = 0.0f;
	float m_timer = 0;
	enum Attack {
		enState_Move,
		enState_MG,
		enState_FS,
		enState_EB,
	};
	CVector3 m_magicdirection = CVector3::Zero();
	float m_timer2 = 0.0f;
	Attack m_attackstate = enState_MG;
	bool m_start = false;
	const float m_startdistance = 2000.0f * 2000.0f;
	const float m_MGariatimer = 1.5f;							//�}�W�b�N�X�t�B�A�̉r������
	const float m_FSariatimer = 1.0f;							//�t���[�Y�V���b�g�ƃG�A���o�[�X�g�̉r���^�C��
	bool m_isaria = false;										//�r���������ǂ���
	bool m_ismagic = false;
	const float m_posetime1 = 0.5f, m_posetime2 = 1.0f, m_posetime3 = 3.5f;
	int m_fscounter = 0,m_mgcounter = 0;                        //���@��������
	const int m_fsnumber = 5;
	const float m_plusdegree = 22.5f;
	const CVector3 m_ariascale = { 25.0f,25.0f,25.0f };
	const float m_icedeletetime = 300.0f;
	const float m_timemultiply = 1.3f;
	int m_countfs = 0,m_countmg=0;								//���@����������
	const float m_attackchanceEB = 400.0f * 400.0f;
	const float m_speedmultiply = 600.0f;
	bool m_isEB = false;										//EB�������Ă������ǂ���
	CVector3 m_EBposition = CVector3::Zero();
	bool m_isdecisionposition = false;
	CVector3 m_playerposition = CVector3::Zero();
	const float m_y = -50.0f;
	const float m_MGdeletetime = 180.0f;

};

