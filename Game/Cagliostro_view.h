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
	bool Start() override;
	void Update() override;
private:
	Ground* m_ground = nullptr;                                  //Ground�N���X�̃|�C���^
	GameCamera* m_gamecamera = nullptr;                          //GameCamera�N���X�̃|�C���^
	GameObj::CDirectionLight* m_lig = nullptr;                   //�f�B���N�V�������C�g�N���X�̃|�C���^
	CVector3 m_color = CVector3::Zero();                         //�f�B���N�V�������C�g�̃J���[
	Player* m_player = nullptr;                                  //�v���C���[�N���X�̃|�C���^
	PlayerStatus* m_playerstatus = nullptr;                      //�v���C���[�X�e�[�^�X�N���X�̃|�C���^
	CVector3 m_position = CVector3::Zero();
	ShadowMapHandler* m_shadowMap = nullptr; 					 //�V���h�E�}�b�v
	Fade* m_fade = nullptr;
	//true�Ȃ��ʐ؂�ւ�����
	bool m_isWaitFadeout = false;
};

