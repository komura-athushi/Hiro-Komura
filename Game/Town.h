#pragma once
class Ground;
class GameCamera;
class Player;
class Human;
class Merchant;
class Stage1_Teleport;
class Stage2_Teleport;
class Stage3_Teleport;
class PlayerStatus;
class Fade;
class GameData;
//拠点となる町です
class Town:public IGameObject
{
public:
	Town();
	~Town();
	bool Start() override;
	void Update() override;
	//レベル構築
	void BuildLevel();
	//街を発展
	void DevelopTown()
	{
		m_developtown = true;
	}
private:
	bool m_developtown = false;						   //街を発展させるかどうか
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトのカラー
	Player* m_player;                                  //プレイヤークラスのポインタ
	Human* m_human;									   //ヒューマンクラスのポインタ
	Merchant* m_merchant;							   //マーチャントクラスのポインタ
	Stage1_Teleport* m_stage1_teleport = nullptr;                //ステージ1に遷移するためのクラスのポインタ
	Stage2_Teleport* m_stage2_teleport = nullptr;				   //ステージ2に遷移するためのクラスのポインタ
	Stage3_Teleport* m_stage3_teleport = nullptr;
	Level m_level;                                     //レベルデザインのためのクラス
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	GameData* m_gamedata;
	CascadeShadowHandler* m_CascadeShadowmap;
	Fade* m_fade;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	//画面の切り替え先を分岐させる
	enum State {
		enSt1 = 1,
		enSt2,
		enSt3,
		enTown,
		enCga,
	};
	State m_state;
};

