#pragma once
#include "DemolisherWeapon/physics/character/CCharacterController.h"

class Sword;
class GameCamera;
class PlayerStatus;
//プレイヤーです
class Player:public IGameObject
{
public:
	//カリオストロちゃんモードを設定
	void Cagliostro()
	{
		m_cagliostro = true;
	}
	//カリオストロちゃんモードかどうかを取得
	bool isCagliostro()
	{
		return m_cagliostro;
	}
	Player();
	~Player();
	bool Start();
	void Update();
	//文字表示
	void PostRender()override;
	//ユニティちゃんを表示する時の処理
	void unityChan();
	//はぁーい☆美少女錬金術師のカリオストロだよ☆よろしくね☆
	void cagliostro();
	//プレイヤーステータスのクラスのメンバ変数をプレイヤーのステータスに反映
	void Status();
	//キャラクターの向きを計算
	void Turn();
	//キャラクターのアニメーションを再生
	void AnimationController();
	//特殊なキャラクターのアニメーションを決める
	void Animation();
	//キャラクターの移動を計算
	void Move();
	//攻撃関係
	void Kougeki();
	//アニメーションイベント
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	//攻撃の切り替え
	void SwitchWeapon();
	//武器の切り替えの際にステータスを反映させる
	void WeaponStatus();
	//プレイヤーステータスクラスのポインタを設定
	void SetPlayerStatus(PlayerStatus* ps)
	{
		m_playerstatus = ps;
	}
	//プレイヤーの座標をセット
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//プレイヤーの座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//プレイヤーのHPを取得
	int GetHP() const
	{ 
		return m_HP;
	}
	//ゲームオーバーかどうかを取得
	bool GetGameOver() const
	{
		return m_gameover;
	}
	//ゲームクリアかどうかを取得
	bool GetGameClear() const
	{
		return m_gameclear;
	}
	//カメラのポインタをセット
	void SetCamera(GameCamera* camera)
	{
		m_gamecamera = camera;
	}
	//プレイヤーがダメージを受けた時の処理
	void Damage(const int& attack);
private:
	bool m_cagliostro = false;
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
    SuicideObj::CCollisionObj* m_collision;                     //丸いコリジョン
	CFont m_font;                                               //文字表示クラス
	Bone* m_bone;                                               //骨
	PlayerStatus* m_playerstatus;                               //プレイヤーステータスのポインタ
	int m_bonehand;                                             //右手のboneの番号
	int m_bonecenter;                                           //centerの番号
	CVector3 m_savemovespeed;                                   //m_movespeedを記憶しておく
	Sword* m_sword;                                             //Swordクラスのポインタ
	GameCamera* m_gamecamera;                                   //カメラのポインタ
	CVector3 m_movespeed;                                       //移動速度
	CVector3 m_position = {0.0f,100.0f,00.0f};                  //ユニティちゃんの座標
	CVector3 m_playerheikou = { 0.0f,0.0f,0.0f };               //プレイヤーと平行なベクトル
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //大きさ
	int m_timer = 0;                                            //攻撃のクールタイム
	int m_timer2 = 0;                                           //ダメージのクールタイム
	bool m_gameover = false;                                    //ゲームオーバーかどうか
	bool m_gameclear = false;									//ゲームクリアかどうか
	bool m_isjump = false;                                      //ジャンプしているかどうか
	//自機の角度　初期は180度
	float m_degree = 180.0f;                                    //ユニティちゃんの向いてる角度
	float m_radian = 0;                                         //上記をラジアン単位に直したもの
	//移動速度乗算
	const float m_multiply = 400.0f;                            //ユニティちゃんの移動速度を調整する
	CQuaternion m_rotation;                                     //クォータニオン
	CCharacterController m_charaCon;                            //キャラクターの当たり判定とか移動とか
	const float m_r = 40.0f;                                    //コリジョンの半径
	const float m_collisionUp = 50.0f;                          //コリジョンの座標のyを加算
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_Clear,
		enAnimationClip_attack,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Jump,
		enState_Damage,
		enState_GameOver,
		enState_WaitStartGameClear,
		enState_GameClear,
		enState_Attack,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	//プレイヤーの色々なステータス
	int m_Level;                                                //レベル
	int m_Exp;                                                  //累計経験値
	int m_NextExp;                                              //次のレベルアップに必要な経験値
	int m_MaxHP;                                                //最大HP
	int m_HP;                                                   //HP
	int m_MaxPP;                                                //最大PP
	int m_PP;                                                   //PP
    int m_Attack;                                               //攻撃力
	int m_Mattack;                                              //魔法攻撃力
	int m_SwordId;                                              //装備中の武器の番号
	const wchar_t* m_SwordName;                                 //装備中の武器の名前
	int m_MagicId;                                              //使える魔法の番号
	bool m_damage = false;                                      //ダメージを受けた！
	bool m_isbutton = false;                                    //武器切り替えの時に使うやつ
};

