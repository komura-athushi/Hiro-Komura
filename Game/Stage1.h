#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Oni;
//�X�e�[�W1�Ɋ֌W������̂𐶐�������A�Ǘ������肷��N���X�ł�
class Stage1:public IGameObject
{
public:
	Stage1();
	~Stage1();
	bool Start();
	void Update();
	//�v���C���[�X�e�[�^�X�N���X�̃|�C���^���󂯎��
	void SetPlayerStatus(PlayerStatus* ps)
	{
		m_playerstatus = ps;
	}
private:
	Ground* m_ground;                                  //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera;                          //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig;                   //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color;                                  //�f�B���N�V�������C�g�̐F�����߂�
	Player* m_player;                                  //�v���C���[�N���X�̃|�C���^
	Level m_level;                                     //���x���f�U�C���̂��߂̃N���X
	PlayerStatus* m_playerstatus;                      //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	std::vector<Oni*> m_oniList;                       //�S�N���X�̃|�C���^�̉ϒ��z��
	
};

