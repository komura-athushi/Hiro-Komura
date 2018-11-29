#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Oni;
//ステージ1に関係するものを生成したり、管理したりするクラスです
class Stage1:public IGameObject
{
public:
	Stage1();
	~Stage1();
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
	CVector3 m_color;                                  //ディレクションライトの色を決める
	Player* m_player;                                  //プレイヤークラスのポインタ
	Level m_level;                                     //レベルデザインのためのクラス
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	std::vector<Oni*> m_oniList;                       //鬼クラスのポインタの可変長配列
	
};

