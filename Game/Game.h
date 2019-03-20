#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Oni;
class Skeleton2;
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
	bool Start();
	void Update();
	//�X�e�[�W�̔ԍ���ݒ�
	void SetStageNumber(const int& number)
	{
		m_stagenumber = number;
	}
	//�Q�[���N���A�I�I
	void SetGameClear()
	{
		m_isgameclear = true;
	}
private:
	Ground* m_ground;                                  //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera;                          //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig;                   //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color;                                  //�f�B���N�V�������C�g�̐F�����߂�
	Player* m_player;                                  //�v���C���[�N���X�̃|�C���^
	Level m_level;                                     //���x���f�U�C���̂��߂̃N���X
	PlayerStatus* m_playerstatus;                      //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	CSprite m_sprite;								   //�X�v���C�g�N���X
	Wall* m_wall;
	CascadeShadowHandler* m_CascadeShadowmap;
	std::vector<Oni*> m_oniList;
	std::vector<Skeleton2*> m_sk2List;
	Boss* m_boss;
	Fade* m_fade;
	GameData* m_gamedata;
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
	int m_stagenumber;
	bool m_isgameclear = false;
};

