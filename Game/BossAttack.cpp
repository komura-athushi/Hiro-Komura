#include "stdafx.h"
#include "BossAttack.h"


BossAttack::BossAttack()
{
}


BossAttack::~BossAttack()
{
	delete  m_bullet1skinModel;
	delete  m_bullet2skinModel;
	delete  m_bullet3skinModel;
}

bool BossAttack::Start()
{
	if (m_number==1) {
		//弾１のスキンモデルレンダーを表示
		m_bullet1skinModel = new GameObj::CSkinModelRender;
		m_bullet1skinModel->Init(L"Resource/modelData/Magic_Sample.cmo");
	}
	else if (m_number==2) {
		//弾２のスキンモデルレンダーを表示
		m_bullet2skinModel = new GameObj::CSkinModelRender;
		m_bullet2skinModel->Init(L"Resource/modelData/bullet2.cmo");
		m_bullet2skinModel->SetScale(m_scale);
	}else{
		//弾３のスキンモデルレンダーを表示
		m_bullet3skinModel = new GameObj::CSkinModelRender;
		m_bullet3skinModel->Init(L"Resource/modelData/bullet3.cmo");
	}
	return true;
}

void BossAttack::Attack1()
{
	//弾丸を移動させる。
	m_position += m_moveSpeed;
	//スキンモデルレンダーに座標を伝える。
	m_bullet1skinModel->SetPos(m_position);
}

void BossAttack::Attack2()
{
	//プレイヤーの方向に向かせる。
	CVector3 moveplayer = m_moveSpeed;
	moveplayer.y = 0.0f;
	moveplayer.Normalize();
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveplayer.x, moveplayer.z));
	m_bullet2skinModel->SetRot(m_rotation);
	//弾丸を移動させる。ff
	m_position += m_moveSpeed;
	//スキンモデルレンダーに座標を伝える。
	m_bullet2skinModel->SetPos(m_position);
}

void BossAttack::Attack3()
{
	//プレイヤーの方向に向かせる。
	CVector3 moveplayer = m_moveSpeed;
	moveplayer.y = 0.0f;
	moveplayer.Normalize();
	m_rotation.SetRotation({ 0.0f,1.0f,0.0f }, atan2f(moveplayer.x, moveplayer.z));
	m_bullet3skinModel->SetRot(m_rotation);
	//弾丸を移動させる。ff
	m_position += m_moveSpeed;
	//スキンモデルレンダーに座標を伝える。
	m_bullet3skinModel->SetPos(m_position);
}

void BossAttack::Update()
{
	//タイマーを加算する。
	m_timer++;
	if (m_number==1) {
		Attack1();
	}
	else if (m_number==2) {
		Attack2();
	}
	else {
		Attack3();
	}
	if (m_timer == 50) {
		//タイマーが50になったらインスタンスを削除する。
		delete this;
	}
}