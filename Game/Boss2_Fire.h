#pragma once
class Boss2;
class Boss2_Fire : public IGameObject
{
public:
	Boss2_Fire();
	~Boss2_Fire();
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
private:
	GameObj::Suicider::CEffekseer* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero();						//弾の座標
	CQuaternion m_rotation;
	const CVector3 m_scale = { 30.0f,30.0f,30.0f };				//弾の大きさ
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };					//移動速度。
	int m_damage = 0;
	const float m_frame = 40.0f;
	Boss2* m_boss2;												//Boss2クラスのポインタ
};