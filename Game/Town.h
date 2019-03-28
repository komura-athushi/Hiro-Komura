#pragma once
class Ground;
class GameCamera;
class Player;
class Human;
class Merchant;
class Stage1_Teleport;
class Stage2_Teleport;
class Stage3_Teleport;
class PlayerStatus;
class Fade;
class GameData;
//���_�ƂȂ钬�ł�
class Town:public IGameObject
{
public:
	Town();
	~Town();
	bool Start() override;
	void Update() override;
	//���x���\�z
	void BuildLevel();
	//�X�𔭓W
	void DevelopTown()
	{
		m_developtown = true;
	}
private:
	bool m_developtown = false;						    //�X�𔭓W�����邩�ǂ���
	Ground* m_ground;                                   //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera;                           //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig;                    //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color;                                   //�f�B���N�V�������C�g�̃J���[
	Player* m_player;                                   //�v���C���[�N���X�̃|�C���^
	Human* m_human;									    //�q���[�}���N���X�̃|�C���^
	Merchant* m_merchant;							    //�}�[�`�����g�N���X�̃|�C���^
	Stage1_Teleport* m_stage1_teleport = nullptr;       //�X�e�[�W1�ɑJ�ڂ��邽�߂̃N���X�̃|�C���^
	Stage2_Teleport* m_stage2_teleport = nullptr;	    //�X�e�[�W2�ɑJ�ڂ��邽�߂̃N���X�̃|�C���^
	Stage3_Teleport* m_stage3_teleport = nullptr;		//�X�e�[�W3�ɑJ�ڂ��邽�߂̃N���X�̃|�C���^
	Level m_level;                                      //���x���f�U�C���̂��߂̃N���X
	PlayerStatus* m_playerstatus;                       //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	GameData* m_gamedata;								//�Q�[���f�[�^																
	CascadeShadowHandler* m_CascadeShadowmap;			//�J�X�P�[�h�V���h�E
	Fade* m_fade;										//�t�F�[�h
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	//��ʂ̐؂�ւ���𕪊򂳂���
	enum State {
		enSt1 = 1,										//�X�e�[�W1
		enSt2,											//�X�e�[�W2
		enSt3,											//�X�e�[�W3
		enTown,											//���_
		enCga,											//�J���I�X�g��
	};
	State m_state;										//�X�e�[�g
};

