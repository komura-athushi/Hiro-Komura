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
	void Attack();       										//�U��
	void Chase();												//�ǐ�
	void Turn();												//�L�����N�^�[�̌������v�Z
	void AnimationController();									//�A�j���[�V�����̍Đ�
	void Damage();												//�_���[�W���󂯂����̃A�N�V����
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
	void SetOldPosition(const CVector3 pos)
	{
		m_oldpos = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle1,
		enAnimationClip_idle2,
		enAnimationClip_run,
		enAnimationClip_tuki,
		enAnimationClip_harai,
		enAnimationClip_nidan,
		enAnimationClip_bash,
		enAnimationClip_kaiten,
		enAnimationClip_damage,
		enAnimationClip_death,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle_Run,
		enState_tuki,
		enState_harai,
		enState_nidan,
		enState_bash,
		enState_kaiten,
		enState_Damage,
		enState_Dead,
	};
	EnState m_state = enState_Idle_Run;
	AnimationClip m_animClip[enAnimationClip_num];
	CVector3 m_oldpos = { 1000.0f,0.0f,-1000.0f };				//�R�m�̏����ʒu
	CVector3 m_position = { 1000.0f,0.0f,-1000.0f };			//�R�m�̍��W
	//�X�P�[����100.0f
	CVector3 m_scale = { 1.0f,1.0f,1.0f };						//�R�m�̃X�P�[��
	CVector3 m_movespeed = { 0.0f,  0.0f,  0.0f };				//�ړ����x
	//���@�̊p�x�@������180�x
	float m_degree = 180.0f;                                    //�R�m�̌����Ă�p�x
	float m_radian = 0;                                         //��L�����W�A���P�ʂɒ���������
	CQuaternion m_rotation;
	CVector3 m_parallel = { 0.0f,0.0f,0.0f };					//�R�m�̌����ƕ��s�ȃx�N�g��
	int m_idlecount = 0;
	int m_timer = 0;											//�ҋ@���[�V�����̃N�[���^�C���̂��߂Ƀt���[�����𐔂���
	int m_Ctimer = 0;											//��i�˂��̓��ڂ̂��߂Ƀt���[�����𐔂���
	int m_cooltime = 500;
	Player* m_player;											//�v���C���[�N���X�̃|�C���^
	bool m_ischase = true;										//�v���C���[��ǔ����Ă��邩�ǂ���
	//Boss�̐F�X�ȃX�e�[�^�X
	static const int m_MaxHP = 100;                             //�ő�HP
	static const int m_Attack =50;								//�˂��̍U����
	static const int m_EXP = 500;                               //�o���l
	static const int m_dropChances[];				            //�h���S���̃h���b�v����A�C�e���A[1]��10�Ȃ烌�A�x1��10%�Ńh���b�v����݂�����
	static const int m_dropmaterialChances[];
	static const int m_meseta = 500;
	bool m_gekiha = false;                                      //delete���邩�ǂ���
	//�R���W�����֌W
	float m_collisionheight = 70.0f;							//�R���W������m_position����ǂꂾ����ɂ����邩
	CVector3 m_size = { 130.0f, 120.0f, 400.0f};				//�˂��̃R���W�����̔��a
	const float m_harai_r = 150.0f;								//�͂炢�������Ƃ��ɔ���������R���W�����̔��a
	//��i
//	const float m_harai_r = 150.0f;								//��i�˂��������Ƃ��ɔ���������R���W�����̔��a
	bool deletefirst = false;									//��i�˂��̏������s�������ǂ���
};

