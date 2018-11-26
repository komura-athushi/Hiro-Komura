#pragma once
class Ground;
class GameCamera;
class Player;
class PlayerStatus;
class Cagliostro_view:public IGameObject
{
public:
	Cagliostro_view();
	~Cagliostro_view();
	bool Start();
	void Update();
	//プレイヤーステータスクラスのポインタを受け取る
	void SetPlayerStatus(PlayerStatus* ps)
	{
		m_playerstatus = ps;
	}
private:
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトのカラー
	Player* m_player;                                  //プレイヤークラスのポインタ
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	CVector3 m_position = { 0.0f,0.0f,0.0f };
};

