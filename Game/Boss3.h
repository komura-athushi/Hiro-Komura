#pragma once
#include "Weapon.h"
#include "Material.h"
#include "IEnemy.h"
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Stage1;
class Player;
class Boss3 : public IEnemy
{
public:
	Boss3();
	~Boss3();
	bool Start() override;
	void Update() override;
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle_Run,
		enState_Hikkaki,
		enState_Fire,
		enState_Press,
		enState_Damage,
		enState_Dead,
	};
	EnState m_state = enState_Idle_Run;
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//�h���S���̏����ʒu
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//�h���S���̍��W
	//�X�P�[����100.0f
	CVector3 m_scale = { 100.0f,100.0f,100.0f };				//�h���S���̃X�P�[��
	float m_collisionheight = 70.0f;							//�R���W������m_position����ǂꂾ����ɂ����邩
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 900;                             //�ő�HP
	static const int m_Attack1 = 20;							//�Ђ������̍U����
	static const int m_EXP = 500;                               //�o���l
	static const int m_dropChances[];				            //�h���S���̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //delete���邩�ǂ���
};

