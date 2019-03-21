#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Boss;
class Fade;
class GameData;
class Wall;
//ステージに関係するものを生成したり、管理したりするクラスです
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	//ステージの番号を設定
	void SetStageNumber(const int& number)
	{
		m_stagenumber = number;
	}
	//ゲームクリア！！
	void SetGameClear()
	{
		m_isgameclear = true;
	}
private:
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトの色を決める
	Player* m_player;                                  //プレイヤークラスのポインタ
	Level m_level;                                     //レベルデザインのためのクラス
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	CSprite m_sprite;								   //スプライトクラス
	Wall* m_wall;
	CascadeShadowHandler* m_CascadeShadowmap;
	Boss* m_boss;
	Fade* m_fade;
	GameData* m_gamedata;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	int m_stagenumber;
	bool m_isgameclear = false;
};

