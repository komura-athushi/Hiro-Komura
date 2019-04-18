#pragma once
class Player;
class GameData;
class PlayerStatus;
//こいつに話しかけると街を発展できる(設定)
class Human:public IGameObject
{
public:
	Human();
	~Human();
	bool Start() override;
	void Update() override;
	//アニメーション
	void AnimationController();
	//回転
	void Turn();
	//街を発展させる！
	void SetLevelUpTown();
	//文字表示
	void PostRender() override;
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//街を発展できるかどうか
	bool isLevelUpTown()
	{
		return m_developtown;
	}
	//トークをオンにする
	void OnTalk()
	{
		m_ontalk = true;
	}
	//トークをオフにする
	void OffTalk()
	{
		m_ontalk = false;
	}
	//トーク状態を取得
	bool GetTalk() const
	{
		return m_ontalk;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_scale = { 2.0f,2.0f,2.0f };						//モデルの大きさ
	CVector3 m_position = { 300.0f,200.0f,0.0f };			    //モデルの座標
	CSprite m_sprite;											//画像
	float m_animationspeed = 0.7f;								//アニメーションの再生速度
	CQuaternion m_rotation;										//回転
	bool m_developtown = false;								    //街を発展できるかどうか
	bool m_leveluptown = false;								    //街を発展させます
	int m_townlevel = 0;									    //街の発展レベル
	CFont m_font;                                               //文字表示クラス
	bool m_ontalk = false;									    //トークオン
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
	};
	static const int m_necessarymaterial = 10;				    //街の発展に必要な素材の数
	AnimationClip m_animClip[enAnimationClip_num];	
	EnState m_state = enState_Idle;								//ステート
	Player* m_player = nullptr;									//プレイヤー
	PlayerStatus* m_playerstatus = nullptr;						//プレイヤーステータス
	GameData* m_gamedata = nullptr;								//ゲームデータ
	bool m_istalk = true;										//話してる？
};

