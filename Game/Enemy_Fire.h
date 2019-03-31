#pragma once
class Enemy_Fire : public IGameObject
{
public:
	Enemy_Fire();
	~Enemy_Fire();
	bool Start() override;
	void Update() override;
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
	//弾の移動方向をセット
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
	//削除する時間を変更
	void SetDeleteTime(const float& time)
	{
		m_time = time;
	}
	//移動速度を変更
	void SetSpeed(const float& speed)
	{
		m_speed = speed;
	}
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;			//エフェクト
	CVector3 m_position = CVector3::Zero();						//弾の座標
	CQuaternion m_rotation;										//エフェクトの回転
	const CVector3 m_scale = { 24.0f,24.0f,24.0f };				//弾の大きさ
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };					//移動速度。
	int m_damage = 0;											//接触した際に与えるダメージ
	const float m_frame = 40.0f;
	//コリジョン関係
	SuicideObj::CCollisionObj* m_attackCol;						//コリジョン
	const float m_attack3r = 90.0f;                             //攻撃したときに発生させるコリジョンの半径
	int m_attack = 30;							                //ファイヤーの攻撃力、デフォルトで30
	float m_timer = 0.0f;									    //タイマー
	float m_time = 100.0f;									    //削除するタイミング
	float m_speed = 1.0f;									    //速さ
};