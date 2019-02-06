#pragma once
class Player;
class Ground;
class GameCamera;
class PlayerStatus;
class Oni;
class Boss;
class Fade;
//ステージ1に関係するものを生成したり、管理したりするクラスです
class Game:public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	Ground* m_ground;                                  //Groundクラスのポインタ
	GameCamera* m_gamecamera;                          //GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig;                   //ディレクションライトクラスのポインタ
	CVector3 m_color;                                  //ディレクションライトの色を決める
	Player* m_player;                                  //プレイヤークラスのポインタ
	Level m_level;                                     //レベルデザインのためのクラス
	PlayerStatus* m_playerstatus;                      //プレイヤーステータスクラスのポインタ
	CSprite m_sprite;								   //スプライトクラス
	ShadowMapHandler* m_shadowMap;
	std::vector<Oni*> m_oniList;
	Boss* m_boss;
	Fade* m_fade;
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
};

