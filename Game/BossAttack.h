#pragma once
class BossAttack : public IGameObject
{
public:
	BossAttack();
	~BossAttack();
	bool Start() override;
	void Update() override;
	void Attack1();
	void Attack2();
	void Attack3();
	//弾の座標をセット
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
	//攻撃のナンバーを取得
	void SetNumber(const int& number)
	{
		m_number = number;
	}
private:
	GameObj::CSkinModelRender* m_bullet1skinModel = nullptr;		//1スキンモデルレンダラー。
	GameObj::CSkinModelRender* m_bullet2skinModel = nullptr;		//2スキンモデルレンダラー。
	GameObj::CSkinModelRender* m_bullet3skinModel = nullptr;		//3スキンモデルレンダラー。
	CVector3 m_position = { 0.0f,0.0f,0.0f };	//座標。
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };	//移動速度。
	CVector3 m_bulletpos = { 0.0f,0.0f,0.0f };
	CVector3 m_scale = { 20.0f,20.0f,20.0f };						//弾のスケール
	CQuaternion m_rotation;											//クォータニオン
	int m_timer = 0;
	int m_number = 0;
	//const wchar_t m_name[] = L"bullet";
};

