#include "stdafx.h"
#include "Morugan.h"
#include "Player.h"
#include "IEnemy.h"
#include "PlayerStatus.h"
Morugan::Morugan()
{
}


Morugan::~Morugan()
{
	delete m_effect;
}

bool Morugan::Start()
{
    m_effect = new GameObj::Suicider::CEffekseer;
	m_effect->Play(L"Asset/effect/Effects/efk/magic_laser.efk", 1.0f, m_position, m_rotation, m_scale);
	//m_effect->Play(L"Asset/effect/morugan/efk/morugan.efk", 1.0f, m_position, m_rotation, m_scale);
	m_player = FindGO<Player>(L"Player");
	//エフェクトをプレイヤーの向きに回転
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_player->GetFront().x, -m_player->GetFront().z));
	m_effect->SetRot(qRot);
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	return true;
}

void Morugan::Update()
{
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), atan2f(-m_player->GetFront().x, -m_player->GetFront().z));
	m_effect->SetRot(qRot);
	m_effect->SetSpeed(m_frame * GetDeltaTimeSec());
	if (m_timer >= m_time) {
		//Aベクトル(単位ベクトル)、モルガンの正面のベクトル
		CVector3 front = m_player->GetFront();
		QueryGOs<IEnemy>(L"Enemy", [&](IEnemy* enemy)
		{
			//エネミーが死んでいたら処理を終了します
			if (enemy->GetDeath()) {
				return true;
			}
			//Bベクトル、エネミーの座標からモルガンの座標を引いたベクトル
			CVector3 pos = enemy->GetPosition() - m_position;
			//AベクトルとBベクトルの内積を求める
			//これにより「BベクトルからAベクトルに垂直ベクトル」と「Aベクトル」の交わる座標からAベクトルの始点までの長さが求まる
			float ip = front.Dot(pos);
			//内積が0未満なら処理を終了する
			if (ip < 0) {
				return true;
			}
			//内積がモルガンの長さより長い場合、処理を終了する
			else if (ip > m_length) {
				return true;
			}
			//Aベクトルに求めた内積をかけて、「BベクトルからAベクトルに垂直ベクトル」と「Aベクトル」の交わる座標のCベクトルを求める
			CVector3 c = front * ip;
			//CベクトルとBベクトルの距離の距離の2乗が一定以下(敵のコリジョンの半径＋モルガンのえんちうの半径の2乗)ならエネミーにダメージを与える
			CVector3 pos2 = pos - c;
			if (pos2.LengthSq() <= std::pow((enemy->GetRadius() + m_r), 2.0f)) {
				enemy->Damage(m_damage);
				//もしエネミーのHPが0以下になったら
				if (enemy->GetDeath()) {
					//エネミーの経験値をプレイヤーの経験値に加算
					PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
					playerstatus->PlusExp(enemy->GetExp());
				}
			}
			return true;
		});
	}
	m_timer += m_frame * GetDeltaTimeSec();
	//プレイヤーが詠唱中でないなら自身を削除する
	if (!m_player->GetAria()) {
		delete this;
	}
}


