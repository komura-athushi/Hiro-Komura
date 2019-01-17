#include "stdafx.h"
#include "BossAttack.h"


BossAttack::BossAttack() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances)
{
}


BossAttack::~BossAttack()
{
}

bool BossAttack::Start()
{
	//弾１のスキンモデルレンダーを表示
	m_bullet1skinModel = new GameObj::CSkinModelRender;
	m_bullet1skinModel->Init(L"Resource/modelData/Magic_Sample.cmo");
	////弾２のスキンモデルレンダーを表示
	//m_bullet2skinModel = new GameObj::CSkinModelRender;
	//m_bullet2skinModel->Init(L"Resource/modelData/bullet2.cmo");
	////弾３のスキンモデルレンダーを表示
	//m_bullet3skinModel = new GameObj::CSkinModelRender;
	//m_bullet3skinModel->Init(L"Resource/modelData/bullet3.cmo");
	return true;
}

void BossAttack::Attack1()
{
	//弾丸を移動させる。
	m_position += m_moveSpeed;
	//スキンモデルレンダーに座標を伝える。
	m_bullet1skinModel->SetPos(m_position);
	if (m_timer == 50) {
		//タイマーが50になったらインスタンスを削除する。
		DeleteGO(this);4
	}
}

void BossAttack::Attack2()
{

}

void BossAttack::Attack3()
{

}

void BossAttack::Update()
{
	//タイマーを加算する。
	m_timer++;
	Attack1();
}