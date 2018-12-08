#pragma once
class Ground;
class GameCamera;
class Player;
class Human;
class Stone;
class House;
class Stage1_Teleport;
class PlayerStatus;
//���_�ƂȂ钬�ł�
class Town:public IGameObject
{
public:
	Town();
	~Town();
	bool Start();
	void Update();
private:
	Ground* m_ground;                                  //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera;                          //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig;                   //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color;                                  //�f�B���N�V�������C�g�̃J���[
	Player* m_player;                                  //�v���C���[�N���X�̃|�C���^
	Human* m_human;									   //�q���[�}���N���X�̃|�C���^
	Stage1_Teleport* m_stage1_teleport;                //�X�e�[�W1�ɑJ�ڂ��邽�߂̃N���X�̃|�C���^
	Level m_level;                                     //���x���f�U�C���̂��߂̃N���X
	PlayerStatus* m_playerstatus;                      //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	//�e�I�u�W�F�N�g�̉ϒ��z��
	std::vector<Stone*> m_stoneList;                   //Stone�N���X�̃|�C���^���i�[���邽�߂̉ϒ��z��
	std::vector<House*> m_houseList;                   //Stone�N���X�̃|�C���^���i�[���邽�߂̉ϒ��z��
};

