#include "stdafx.h"
#include "ShotMagic.h"
#include "PlayerStatus.h"
#include "Player.h"
#include "IEnemy.h"
#include "Effekseer.h"

const int ShotMagic::m_number[10] = { 0,1,2,3,4,5,6,7,8,9 };
ShotMagic::ShotMagic(const int& id, const wchar_t* name, const float& damageRate, const int& ppCost)
	:m_id(id), m_name(name), m_damageRate(damageRate), m_ppCost(ppCost)
{
}

ShotMagic::ShotMagic(const ShotMagic& magic) : m_id(magic.m_id), m_name(magic.m_name), m_damageRate(magic.m_damageRate), m_ppCost(magic.m_ppCost)
{

}

ShotMagic::ShotMagic()
{
}


ShotMagic::~ShotMagic()
{
	
}

bool ShotMagic::Start()
{
	m_damage = m_damage * (m_randDamage + rand() % 10) / 100;
	//魔法の番号によって処理を変えます
	switch (m_id) {
	case 1:
		Foie();
		break;
	case 2:
		Irugra();
		break;
	case 3:
		Zanbas();
		break;
	case 4:
		Shihuta();
		break;
	case 5:
		MagicSphere();
		break;
	case 6:
		Resta();
		break;
	case 7:
		Haou();
	}
	m_movespeed *= m_speed;
	return true;
}

 void ShotMagic::Update()
{
	 //魔法の番号によって処理を変えます
	 switch (m_id) {
	 case 1:
		 FoieUpdate();
		 break;
	 case 2:
		 IrugraUpdate();
		 break;
	 case 3:
		 ZanbasUpdate();
		 break;
	 case 4:
		 ShihutaUpdate();
		 break;
	 case 5:
		 MagicSphereUpdate();
		 break;
	 }
	 int i = 0;
	 //MagciModel構造体の可変長配列にアクセスします
	 for (auto& mgml : m_magicmocelList) {
		 if (mgml.s_delete) {
			 i++;
		 }
		 else {
			 //削除する時間を超えていたらモデルとコリジョンを削除します
			 if (mgml.s_timer >= m_deletetime) {
				 delete mgml.s_effect;
				 mgml.s_effect = nullptr;
				 delete mgml.s_collision;
				 mgml.s_collision = nullptr;
				 mgml.s_delete = true;
			 }
			 else {
				 //モデルとコリジョンを動かします
				 mgml.s_position = mgml.s_effect->GetPos() + m_movespeed * GetDeltaTimeSec();
				 mgml.s_effect->SetPos(mgml.s_position);
				 mgml.s_effect->SetSpeed(m_frame * GetDeltaTimeSec());
				 mgml.s_collision->SetPosition(mgml.s_position);
				 mgml.s_timer += 60.0f*GetDeltaTimeSec();
				 mgml.s_hittimer += 40.0f * GetDeltaTimeSec();
			 }
		 }
	 }
	 //生成したコリジョンとモデルが全て削除されていれば、自身を削除します
	 if (i == m_modelnumber) {
		 m_timer1++;
	 }
	 if (m_timer1 >= 100) {
		 delete this;
	 }
}
 void ShotMagic::SetCollisionModel(const CVector3& pos, const float& scale,const int& id, const CVector3& scl, const int& number, bool damage, float time)
 {
	 GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
	 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
	 //MagicModelクラスの可変長配列に生成したモデルとコリジョンを格納します
	 m_magicmocelList.push_back({ effect,attackCol });
	 switch (m_id) {
	 case 1:
		 effect->Play(L"Asset/effect/Effects/efk/magic_fire.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 case 2:
		 effect->Play(L"Asset/effect/Effects/efk/magic_ice.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 case 3:
		 effect->Play(L"Asset/effect/Effects/efk/magic_wind.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 case 4:
		 effect->Play(L"Asset/effect/powerup/powerup.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 case 5:
		 effect->Play(L"Asset/effect/Effects/efk/magic_sphere.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 case 6:
		 effect->Play(L"Asset/effect/resta/resta.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 case 7:
		 //effect->Play(L"Asset/effect/haou/haou.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 effect->Play(L"Asset/effect/Effects/efk/magic_sword.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
		 break;
	 }
	 CVector3 topos = m_movespeed;
	 topos.Normalize();
	 float degree = atan2f(topos.x, topos.z);
	 CQuaternion qRot;
	 qRot.SetRotation(CVector3::AxisY(), degree);
	 effect->SetRot(qRot);
	 //攻撃判定の発生
	 attackCol->CreateSphere(pos, CQuaternion::Identity(),scale);
	 //寿命を設定
	 attackCol->SetTimer(enNoTimer);
	 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		 //エネミーからの魔法
		 if (m_isenemy) {
			 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
			 if (param.EqualName(L"Player")) {
				 Player* player = param.GetClass<Player>();//相手の判定に設定されているCEnemyのポインタを取得
				 if (id == 5) {
					 ShotMagic* shotmagic = FindGO<ShotMagic>(L"ShotMagic");
					 CVector3 pos = shotmagic->GetPosition(number);
					 shotmagic->DeleteMagicModel(number);
					 GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
					 effect->Play(L"Asset/effect/explosion/explosion.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);
					 //攻撃判定の発生
					 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
					 attackCol->CreateSphere(pos, CQuaternion::Identity(), scale *m_multiply5);
					 //寿命を設定
					 attackCol->SetTimer(30);
					 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
						 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
						 if (param.EqualName(L"Player")) {
							 Player* player = param.GetClass<Player>();//相手の判定に設定されているCEnemyのポインタを取得
							 if (m_magicmocelList[number].s_enemyidlist.count(PLAYERNUMBER) == 0) {
								 m_magicmocelList[number].s_enemyidlist[PLAYERNUMBER] = m_magicmocelList[number].s_hittimer;
								 //エネミーにダメージ
								 player->Damage(m_damage);
							 }
						 }
					 }
					 );
				 }
				 else if (id == 3) {
					 if (m_magicmocelList[number].s_enemyidlist.count(PLAYERNUMBER) == 0) {
						 m_magicmocelList[number].s_enemyidlist[PLAYERNUMBER] = m_magicmocelList[number].s_hittimer;
						 //エネミーにダメージ
						 player->Damage(m_damage);
					 }
					 else if ((m_magicmocelList[number].s_enemyidlist[PLAYERNUMBER] + m_hittime3) <= m_magicmocelList[number].s_hittimer) {
						 m_magicmocelList[number].s_enemyidlist[PLAYERNUMBER] = m_magicmocelList[number].s_hittimer;
						 //エネミーにダメージ
						 player->Damage(m_damage);
					 }
				 }
				 else {
					 if (m_magicmocelList[number].s_enemyidlist.count(PLAYERNUMBER) == 0) {
						 m_magicmocelList[number].s_enemyidlist[PLAYERNUMBER] = m_magicmocelList[number].s_hittimer;
						 //エネミーにダメージ
						 player->Damage(m_damage);
					 }
				 }
			 }
		 }
		 //プレイヤーからの魔法
		 else {
			 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
			 if (param.EqualName(L"IEnemy")) {
				 IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
				 if (id == 5) {
					 ShotMagic* shotmagic = FindGO<ShotMagic>(L"ShotMagic");
					 CVector3 pos = shotmagic->GetPosition(number);
					 shotmagic->DeleteMagicModel(number);
					 GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
					 effect->Play(L"Asset/effect/explosion/explosion.efk", 1.0f, pos, CQuaternion::Identity(), scl * 12);

					 //攻撃判定の発生
					 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
					 attackCol->CreateSphere(pos, CQuaternion::Identity(), scale *m_multiply5);
					 //寿命を設定
					 attackCol->SetTimer(30);
					 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
						 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
						 if (param.EqualName(L"IEnemy")) {
							 IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
							 if (m_magicmocelList[number].s_enemyidlist.count(enemy->GetNumber()) == 0) {
								 m_magicmocelList[number].s_enemyidlist[enemy->GetNumber()] = m_magicmocelList[number].s_hittimer;
								 //エネミーにダメージ
								 enemy->Damage(m_damage, id);
								 //もしエネミーのHPが0以下になったら
								 if (enemy->GetDeath()) {
									 //エネミーの経験値をプレイヤーの経験値に加算
									 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
									 playerstatus->PlusExp(enemy->GetExp());
								 }

							 }
						 }
					 }
					 );
				 }
				 else if (id == 3) {
					 if (m_magicmocelList[number].s_enemyidlist.count(enemy->GetNumber()) == 0) {
						 m_magicmocelList[number].s_enemyidlist[enemy->GetNumber()] = m_magicmocelList[number].s_hittimer;
						 //エネミーにダメージ
						 enemy->Damage(m_damage, id);
						 //もしエネミーのHPが0以下になったら
						 if (enemy->GetDeath()) {
							 //エネミーの経験値をプレイヤーの経験値に加算
							 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
							 playerstatus->PlusExp(enemy->GetExp());
						 }

					 }
					 else if ((m_magicmocelList[number].s_enemyidlist[enemy->GetNumber()] + m_hittime3) <= m_magicmocelList[number].s_hittimer) {
						 m_magicmocelList[number].s_enemyidlist[enemy->GetNumber()] = m_magicmocelList[number].s_hittimer;
						 //エネミーにダメージ
						 enemy->Damage(m_damage, id);
						 //もしエネミーのHPが0以下になったら
						 if (enemy->GetDeath()) {
							 //エネミーの経験値をプレイヤーの経験値に加算
							 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
							 playerstatus->PlusExp(enemy->GetExp());
						 }
					 }
				 }
				 else {
					 if (m_magicmocelList[number].s_enemyidlist.count(enemy->GetNumber()) == 0) {
						 m_magicmocelList[number].s_enemyidlist[enemy->GetNumber()] = m_magicmocelList[number].s_hittimer;
						 //エネミーにダメージ
						 enemy->Damage(m_damage, id);
						 //もしエネミーのHPが0以下になったら
						 if (enemy->GetDeath()) {
							 //エネミーの経験値をプレイヤーの経験値に加算
							 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
							 playerstatus->PlusExp(enemy->GetExp());
						 }

					 }
				 }
			 }
		 }
	 }
	 );
	 m_modelcount++;
 }

 void ShotMagic::Foie()
 {
	 m_deletetime = m_deletetime1;
	 m_modelnumber = m_modelnumber1;
	 m_scale = m_scale1;
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * m_multiplyspeed1;
	 SetCollisionModelnoDamage(m_position, m_collisionscale1, m_id, m_scale, m_modelcount, true);
	 m_damage /= m_modelnumber;
 }
 void ShotMagic::FoieUpdate()
 {
	
 }

 void ShotMagic::Irugra()
 {
	 m_deletetime = m_deletetime2;
	 m_modelnumber = m_modelnumber2;
	 m_scale = m_scale2;
	 m_movespeed = m_directionplayer * m_multiplyspeed2;
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::IrugraUpdate()
 {
	 if (m_modelcount != m_modelnumber) {
		 if (m_timer >= m_time2) {
			 SetCollisionModelnoDamage(m_position, m_collisionscale2, m_id, m_scale, m_modelcount, true);
			 m_timer = 0;
		 }
	 }
	 m_timer++;
 }

 void ShotMagic::Zanbas()
 {
	 m_deletetime = m_deletetime3;
	 m_modelnumber = m_modelnumber3;
	 m_scale = m_scale3;
	 m_position = m_position; //+CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * m_multiplyspeed3;
	 SetCollisionModelnoDamage(m_position, m_collisionscale3, m_id, m_scale, m_modelcount, true,m_hittime3);
	 m_damage /= m_modelnumber;
	 m_damage /= m_multihit;
 }

 void ShotMagic::ZanbasUpdate()
 {

 }
 
 void ShotMagic::Shihuta()
 {
	 m_deletetime = m_deletetime4;
	 m_modelnumber = m_modelnumber4;
	 m_scale = m_scale4;
	 m_position = m_position; //+CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * m_multiplyspeed4;
	 SetCollisionModelnoDamage(m_position, m_collisionscale4, m_id, m_scale, m_modelcount, false);
	 m_damage /= m_modelnumber;
	 Player* player = FindGO<Player>(L"Player");
	 player->SetShihuta();
 }
	
 void ShotMagic::ShihutaUpdate()
 {
	
 }

 void ShotMagic::MagicSphere()
 {
	 m_deletetime = m_deletetime5;
	 m_modelnumber = m_modelnumber5;
	 m_scale = m_scale5;
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * m_multiplyspeed5;
	 SetCollisionModelnoDamage(m_position, m_collisionscale5, m_id,m_scale, m_modelcount, false);
	 m_damage /= m_modelnumber;
	
 }

 void ShotMagic::MagicSphereUpdate()
 {

 }

 void ShotMagic::Resta()
 {
	 m_deletetime = m_deletetime6;
	 m_modelnumber = m_modelnumber6;
	 m_scale = m_scale6;
	 m_position = m_position; //+CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * m_multiplyspeed6;
	 SetCollisionModelnoDamage(m_position, m_collisionscale6, m_id, m_scale, m_modelcount,false);
	 m_damage /= m_modelnumber;
	 Player* player = FindGO<Player>(L"Player");
	 player->Resta(m_damage);
 }

 void ShotMagic::Haou()
 {
	 m_deletetime = m_deletetime7;
	 m_modelnumber = m_modelnumber7;
	 m_scale = m_scale7;
	 m_position = m_position;
	 m_movespeed = m_directionplayer * m_multiplyspeed7;
	 SetCollisionModelnoDamage(m_position, m_collisionscale1, m_id, m_scale, m_modelcount, true);
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::DeleteMagicModel(const int& number)
 {
	 delete m_magicmocelList[number].s_effect;
	 m_magicmocelList[number].s_effect = nullptr;
	 DeleteGO(m_magicmocelList[number].s_collision);
	 m_magicmocelList[number].s_collision = nullptr;
	 m_magicmocelList[number].s_delete = true;
 }

 void ShotMagic::SetCollisionModelnoDamage(const CVector3& pos, const float& scale, const int& id, const CVector3& scl, const int& number, bool damage, float time)
 {
	 SetCollisionModel(pos, scale, id, scl, m_number[number], damage, time);
 }