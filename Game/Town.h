#pragma once
class Ground;
class GameCamera;
class Player;
class Human;
class Stone;
class House;
class Stage1_Teleport;
class PlayerStatus;
//拠点となる町です
class Town:public IGameObject
{
public:
	Town();
	~Town();
	bool Start();
	void Update();
private:
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトのカラー
	Player* m_player;                                  //プレイヤークラスのポインタ
	Human* m_human;									   //ヒューマンクラスのポインタ
	Stage1_Teleport* m_stage1_teleport;                //ステージ1に遷移するためのクラスのポインタ
	Level m_level;                                     //レベルデザインのためのクラス
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	//各オブジェクトの可変長配列
	std::vector<Stone*> m_stoneList;                   //Stoneクラスのポインタを格納するための可変長配列
	std::vector<House*> m_houseList;                   //Stoneクラスのポインタを格納するための可変長配列
};

