#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Oni;
class Boss;
class Fade;
//�X�e�[�W1�Ɋ֌W������̂𐶐�������A�Ǘ������肷��N���X�ł�
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	Ground* m_ground;                                  //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera;                          //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig;                   //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color;                                  //�f�B���N�V�������C�g�̐F�����߂�
	Player* m_player;                                  //�v���C���[�N���X�̃|�C���^
	Level m_level;                                     //���x���f�U�C���̂��߂̃N���X
	PlayerStatus* m_playerstatus;                      //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	CSprite m_sprite;								   //�X�v���C�g�N���X
	ShadowMapHandler* m_shadowMap;
	std::vector<Oni*> m_oniList;
	Boss* m_boss;
	Fade* m_fade;
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
};

