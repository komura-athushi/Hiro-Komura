#pragma once
#include "GameData.h"
class Player;
class GameData;
class PlayerStatus;
class Merchant:public IGameObject
{
public:
	Merchant();
	~Merchant();
	bool Start();
	void Update();
	void PostRender() override;
	void Turn();
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
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�g�[�N��Ԃ��I��
	void SetTalk()
	{
		m_talk = true;
	}
	//�g�[�N��Ԃ��I�t
	void OffTalk()
	{
		m_talk = false;
	}
	//�g�[�N��Ԃ��ǂ������擾
	bool GetTalk() const
	{
		return m_talk;
	}
private:
	
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero();
	CVector2 m_aiconposition = { 350.0f,50.0f+70.0f*4 };	    //�摜�̈ʒu;
	CVector3 m_aiconscale = { 0.15f,0.15f,0.15f };
	CVector3 m_scale = { 0.8f,0.8f,0.8f };
	CQuaternion m_rotation = CQuaternion::Identity();
	CQuaternion m_protrotation = CQuaternion::Identity();
	CFont m_font;                                               //�����\���N���X
	std::vector<CFont*> m_spritefont;					        //�����\��
	bool m_talk = false;
	CSprite m_sprite[GameData::enWeapon_num];                   //�摜�\���N���X
	CSprite m_cursor;
	std::vector<CSprite*> m_spritelist;				            //�摜�̔z��
	//�A�j���[�V�����֌W
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//�A�j���[�V��������
	enum EnState {
		enState_Idle,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	CVector2 m_spriteposition[GameData::enWeapon_num];
	Player* m_player = nullptr;
	GameData* m_gamedata;
	PlayerStatus* m_playerstatus;
	int m_swordid;
	bool m_button = false;
	int m_equipmentnumber = 0;
};

