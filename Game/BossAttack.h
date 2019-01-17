#pragma once
#include "IEnemy.h"
class BossAttack : public IEnemy
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
	//弾の速度を取得
	CVector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
private:
	GameObj::CSkinModelRender* m_bullet1skinModel = nullptr;		//1スキンモデルレンダラー。
	GameObj::CSkinModelRender* m_bullet2skinModel = nullptr;		//2スキンモデルレンダラー。
	GameObj::CSkinModelRender* m_bullet3skinModel = nullptr;		//3スキンモデルレンダラー。
	CVector3 m_position = { 0.0f,0.0f,0.0f };	//座標。
	CVector3 m_moveSpeed = { 0.0f,0.0f,0.0f };	//移動速度。
	CVector3 m_bulletpos = { 0.0f,0.0f,0.0f };
	int m_timer = 0;
	static const int m_EXP = 500;                               //経験値
};

