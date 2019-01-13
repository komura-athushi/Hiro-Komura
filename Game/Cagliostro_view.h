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
	bool Start();
	void Update();
private:
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトのカラー
	Player* m_player;                                  //プレイヤークラスのポインタ
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	CVector3 m_position = { 0.0f,0.0f,0.0f };
	Fade* m_fade;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
};

