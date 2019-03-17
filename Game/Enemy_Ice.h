#pragma once
class Enemy_Ice:public IGameObject
{
public:
	Enemy_Ice();
	~Enemy_Ice();
	bool Start();
	void Update();
	//ダメージを設定
	void SetDamage(const int& mattack, const float& damagerate)
	{
		m_damage = int(mattack*damagerate);
	}
	//回転を設定
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//弾の速度をセット
	void SetMoveSpeed(const CVector3& pos)
	{
		m_moveSpeed = pos;
	}
	//弾の座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//ファイヤーの攻撃力を設定
	void SetAttack(const int& attack)
	{
		m_attack = attack;
	}
	//弾の速度を変化させる
	void SetSpeed(const float& speed)
	{
		m_speed = speed;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero();						//弾の座標
	CQuaternion m_rotation;
	const CVector3 m_scale = { 24.0f,24.0f,24.0f };				//弾の大きさ
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };					//移動速度。
	float m_speed = 1.0f;							            //弾のスピード
	int m_damage = 0;
	const float m_frame = 60.0f;
	//コリジョン関係
	SuicideObj::CCollisionObj* m_attackCol;
	const float m_attack3r = 75.0f;                            //攻撃したときに発生させるコリジョンの半径
	const float m_collisionheight = 20.0f;
	int m_attack = 30;							               //ファイヤーの攻撃力、デフォルトで30
	float m_timer = 0.0f;
	const float m_time = 120.0f;
	bool m_hitplayer = false;
};

