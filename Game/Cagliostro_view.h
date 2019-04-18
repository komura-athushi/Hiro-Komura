#pragma once
class Ground;
class GameCamera;
class Player;
class PlayerStatus;
class Fade;
//カリオストロちゃんモード発動☆
class Cagliostro_view:public IGameObject
{
public:
	Cagliostro_view();
	~Cagliostro_view();
	bool Start() override;
	void Update() override;
private:
	Ground* m_ground = nullptr;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera = nullptr;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig = nullptr;                   //ディレクションライトクラスのポインタ
	CVector3 m_color = CVector3::Zero();                         //ディレクションライトのカラー
	Player* m_player = nullptr;                                  //プレイヤークラスのポインタ
	PlayerStatus* m_playerstatus = nullptr;                      //プレイヤーステータスクラスのポインタ
	CVector3 m_position = CVector3::Zero();
	ShadowMapHandler* m_shadowMap = nullptr; 					 //シャドウマップ
	Fade* m_fade = nullptr;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
};

