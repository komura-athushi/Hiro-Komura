#pragma once
#include "GameData.h"
class Player;
class GameData;
class PlayerStatus;
class Merchant :public IGameObject
{
public:
	Merchant();
	~Merchant();
	bool Start() override;
	void Update() override;
	void PostRender() override;
	//��]
	void Turn();
	//���틭������������
	void UpgradeorRelease();
	//���������邩�ǂ���
	void ChoiceRelease();
	//����������
	void Release();
	//���틭���̃x�[�X�I��
	void Base();
	//���틭���̑f�ޑI��
	void Material();
	//�������܂����H
	void Decision();
	//�������܂����I
	void Upgrade();
	//�{�^��
	void Button();
	//B�{�^���ŃX�e�[�g����O�̏�Ԃɖ߂�
	void BackState();
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
		if (m_state == enState_Free) {
			m_state = enState_UpgradeorRelease;
		}
	}
	//�g�[�N��Ԃ��I�t
	void OffTalk()
	{
		m_state = enState_Free;
	}
	//�g�[�N��Ԃ��ǂ������擾
	bool GetTalk() const
	{
		return m_state != enState_Free;
	}
	//�x�[�X�I�������ǂ������擾
	bool GetBase() const
	{
		return m_state == enState_Base;
	}
	//�A�C�h����Ԃ��ǂ������擾
	bool GetIdle() const
	{
		return m_state == enState_Free;
	}
private:
	enum State {
		enState_Free,                               //�������ĂȂ����
		enState_UpgradeorRelease,					//����̋������邩����Lv�̏��������邩
		enState_ChoiceRelease,						//����Lv�̏����������邩�ǂ���
		enState_Release,							//���������܂����I
		enState_Base,								//�x�[�X��I��
		enState_Material,							//�f�ނ�I��
		enState_Decision,							//�������邩�ǂ���������
		enState_Upgrade,							//�����I���A���ʂ�\��
	};
	enum Cursor2 {
		enState_onUpgrade,
		enState_onRelease,
	};
	Cursor2 m_cursorstate = enState_onUpgrade;
	State m_state = enState_Free;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero();
	CVector2 m_aiconposition = { 800.0f,50.0f + 70.0f * 4 };	    //�摜�̈ʒu;
	CVector3 m_aiconscale = { 0.15f,0.15f,0.15f };
	CVector3 m_scale = { 0.8f,0.8f,0.8f };
	CQuaternion m_rotation = CQuaternion::Identity();
	CSprite m_sprite2, m_sprite3;
	CSprite m_equipment, m_base;							    //�������\���ƃx�[�X�\��
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
	GameData* m_gamedata = nullptr;
	PlayerStatus* m_playerstatus = nullptr;
	int m_swordid1 = 0, m_swordid2 = 0, m_swordid3 = 0;              //���ꂼ��v���C���[���������Ă��镐��̔ԍ��A�x�[�X�̔ԍ��A�f�ނ̔ԍ��ł���
	bool m_button = false;
	int m_equipmentnumber = 0;
	CSprite m_basesprite, m_materialsprite, m_upgradesprite;      //���ꂼ��x�[�X�A�f�ށA�������ʂ̕���̃X�v���C�g�ł���
	CSprite m_mesetasprite;
	CSprite m_back;												  //�����̎��ɕ���̃o�b�N�ɕ\������摜
	bool m_isspriteInit = false;								  //��L�̉摜�̓ǂݍ��݂��I��������ǂ���
	int m_level = 0;
	bool m_isstrength = false;									  //����̋������ł��邩�ǂ���
	const float m_sevolume = 2.0f;
	CVector2 m_FontSize = { 0.5f,0.5f };
	static const int m_limitstage = 3;
	CSprite m_upgrade, m_release,m_cursor2;
	CVector2 m_cursor2position = { 380.0f,320.0f };
	bool m_isweaponlimitrelease = true;
};

