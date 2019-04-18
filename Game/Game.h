#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Boss;
class Fade;
class GameData;
class Wall;
//�X�e�[�W�Ɋ֌W������̂𐶐�������A�Ǘ������肷��N���X�ł�
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	//�X�e�[�W�̔ԍ���ݒ�
	void SetStageNumber(const int& number)
	{
		m_stagenumber = number;
	}
private:
	Ground* m_ground = nullptr;							//Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera = nullptr;					//GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig = nullptr;			//�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color = CVector3::Zero();				//�f�B���N�V�������C�g�̐F�����߂�
	Player* m_player = nullptr;							//�v���C���[�N���X�̃|�C���^
	Level m_level;										//���x���f�U�C���̂��߂̃N���X
	PlayerStatus* m_playerstatus = nullptr;				//�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	CSprite m_sprite;									//�X�v���C�g�N���X
	Wall* m_wall = nullptr;								//�{�X�����O�ɐݒ肷���									
	CascadeShadowHandler* m_CascadeShadowmap = nullptr;	//�J�X�P�[�h�V���h�E
	Fade* m_fade = nullptr;								//�t�F�[�h
	GameData* m_gamedata = nullptr;						//�Q�[���f�[�^
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	int m_stagenumber;									//�X�e�[�W�̔ԍ�						
};

