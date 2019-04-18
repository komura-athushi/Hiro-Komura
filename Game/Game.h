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
	bool Start() override;
	void Update() override;
	//ステージの番号を設定
	void SetStageNumber(const int& number)
	{
		m_stagenumber = number;
	}
private:
	Ground* m_ground = nullptr;							//Groundクラスのポインタ
	GameCamera* m_gamecamera = nullptr;					//GameCameraクラスのポインタ
	GameObj::CDirectionLight* m_lig = nullptr;			//ディレクションライトクラスのポインタ
	CVector3 m_color = CVector3::Zero();				//ディレクションライトの色を決める
	Player* m_player = nullptr;							//プレイヤークラスのポインタ
	Level m_level;										//レベルデザインのためのクラス
	PlayerStatus* m_playerstatus = nullptr;				//プレイヤーステータスクラスのポインタ
	CSprite m_sprite;									//スプライトクラス
	Wall* m_wall = nullptr;								//ボス部屋前に設定する壁									
	CascadeShadowHandler* m_CascadeShadowmap = nullptr;	//カスケードシャドウ
	Fade* m_fade = nullptr;								//フェード
	GameData* m_gamedata = nullptr;						//ゲームデータ
	//trueなら画面切り替えする
	bool m_isWaitFadeout = false;
	int m_stagenumber;									//ステージの番号						
};

