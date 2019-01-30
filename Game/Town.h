#pragma once
class Ground;
class GameCamera;
class Player;
class Human;
class Stone;
class House;
class Stage1_Teleport;
class PlayerStatus;
class Fade;
//拠点となる町です
class Town:public IGameObject
{
public:
	Town();
	~Town();
	bool Start();
	void Update();
	//街を発展
	void DevelopTown()
	{
		m_developtown = true;
	}
	//レベル構築
	void BuildLevel();
private:
	bool m_developtown = false;						   //街を発展させるかどうか
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトのカラー
	Player* m_player;                                  //プレイヤークラスのポインタ
	Human* m_human;									   //ヒューマンクラスのポインタ
	Stage1_Teleport* m_stage1_teleport;                //ステージ1に遷移するためのクラスのポインタ
	Level m_level;                                     //レベルデザインのためのクラス
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	ShadowMapHandler* m_shadowMap;					   //シャドウマップ
	//各オブジェクトの可変長配列
	std::vector<Stone*> m_stoneList;                   //Stoneクラスのポインタを格納するための可変長配列
	std::vector<House*> m_houseList;				   //Houseクラスのポインタの可変長配列
	Fade* m_fade;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	//画面の切り替え先を分岐させる
	enum State {
		enTown,
		enCga,
		enSt1,
	};
	State m_state;
};

