#pragma once
class Player;
//こいつに話しかけると街を発展できる(設定)
class Human:public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	//アニメーション
	void AnimationController();
	//回転
	void Turn();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_scale = { 2.0f,2.0f,2.0f };
	CVector3 m_position = { 300.0f,200.0f,0.0f };
	float m_animationspeed = 0.7f;
	CQuaternion m_rotation;
	//アニメーション関係
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_num,
	};
	//アニメーション分岐
	enum EnState {
		enState_Idle,
	};
	AnimationClip m_animClip[enAnimationClip_num];
	EnState m_state = enState_Idle;
	Player* m_player;
};

