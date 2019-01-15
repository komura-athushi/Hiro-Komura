#pragma once
class Ground;
class GameCamera;
class Player;
class PlayerStatus;
class Fade;
//�J���I�X�g������񃂁[�h������
class Cagliostro_view:public IGameObject
{
public:
	Cagliostro_view();
	~Cagliostro_view();
	bool Start();
	void Update();
private:
	Ground* m_ground;                                  //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera;                          //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig;                   //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color;                                  //�f�B���N�V�������C�g�̃J���[
	Player* m_player;                                  //�v���C���[�N���X�̃|�C���^
	PlayerStatus* m_playerstatus;                      //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	CVector3 m_position = { 0.0f,0.0f,0.0f };
	Fade* m_fade;
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
};

