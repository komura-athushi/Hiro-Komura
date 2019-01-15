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
	}
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
				 mgml.s_position = mgml.s_effect->GetPos() + m_movespeed*GetDeltaTimeSec();
				 mgml.s_effect->SetPos(mgml.s_position);
				 mgml.s_collision->SetPosition(mgml.s_position);
				 mgml.s_timer += 1.0f;
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
 void ShotMagic::SetCollisionModel(const CVector3& pos, const float& scale,const int& id, const CVector3& scl, const int& number, bool damage)
 {
	 GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
	 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
	 //MagicModelクラスの可変長配列に生成したモデルとコリジョンを格納します
	 m_magicmocelList.push_back({ effect,attackCol });
	 //モデルを作成します
	 /*skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
	 skinModelRender->SetScale(m_scale);
	 skinModelRender->SetPos(pos);*/
	 effect->Play(L"Asset/effect/efk/magic_proj01.efk", 1.0f, pos, CQuaternion::Identity(),scl*12);
	 //攻撃判定の発生
	 attackCol->CreateSphere(pos, CQuaternion::Identity(),scale);
	 //寿命を設定
	 attackCol->SetTimer(enNoTimer);
	 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
		 if (param.EqualName(L"IEnemy")) {
			 IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
			 if (id == 5) {
				 ShotMagic* shotmagic = FindGO<ShotMagic>(L"ShotMagic");
				 CVector3 pos = shotmagic->GetPosition(number);
				 shotmagic->DeleteMagicModel(number);
				 GameObj::CSkinModelRender* skinModelRender = new GameObj::CSkinModelRender;
				 skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
				 skinModelRender->SetScale(m_scale * m_multiply5);
				 skinModelRender->SetPos(pos);
				 //攻撃判定の発生
				 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
				 attackCol->CreateSphere(pos, CQuaternion::Identity(), scale *m_multiply5);
				 //寿命を設定
				 attackCol->SetTimer(10);
				 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
					 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
					 if (param.EqualName(L"IEnemy")) {
						 IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
						 ShotMagic* shotmagic = FindGO<ShotMagic>(L"ShotMagic");
						 //エネミーにダメージ
						 enemy->Damage(shotmagic->GetDamage(), id);
						 //もしエネミーのHPが0以下になったら
						 if (enemy->GetDeath()) {
							 //エネミーの経験値をプレイヤーの経験値に加算
							 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
							 playerstatus->PlusExp(enemy->GetExp());
						 }
					 }
				 }
				 );
			 }
			 else if (id != 5) {
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
	 m_modelcount++;
 }

 void ShotMagic::Foie()
 {
	 m_deletetime = m_deletetime1;
	 m_modelnumber = m_modelnumber1;
	 m_scale = m_scale1;
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 SetCollisionModel(m_position,m_collisionscale1,m_id,m_scale);
	 m_movespeed = m_directionplayer * m_multiplyspeed1;
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
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * m_multiplyspeed1;
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::IrugraUpdate()
 {
	 if (m_modelcount != m_modelnumber) {
		 if (m_timer >= m_time2) {
			 SetCollisionModel(m_position, m_collisionscale2,m_id,m_scale);
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
	 SetCollisionModel(m_position, m_collisionscale3, m_id,m_scale);
	 m_movespeed = m_directionplayer * m_multiplyspeed3;
	 m_damage /= m_modelnumber;
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
	 SetCollisionModel(m_position, m_collisionscale4, m_id,m_scale);
	 m_movespeed = m_directionplayer * m_multiplyspeed4;
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
	 SetCollisionModelnoDamage(m_position, m_collisionscale5, m_id,m_scale, m_modelcount, false);
	 m_movespeed = m_directionplayer * m_multiplyspeed5;
	 m_damage /= m_modelnumber;
	
 }

 void ShotMagic::MagicSphereUpdate()
 {

 }

 void ShotMagic::DeleteMagicModel(const int& number)
 {
	 delete m_magicmocelList[number].s_effect;
	 m_magicmocelList[number].s_effect = nullptr;
	 DeleteGO(m_magicmocelList[number].s_collision);
	 m_magicmocelList[number].s_collision = nullptr;
	 m_magicmocelList[number].s_delete = true;
 }

 void ShotMagic::SetCollisionModelnoDamage(const CVector3& pos, const float& scale, const int& id, const CVector3& scl, const int& number, bool damage)
 {
	 SetCollisionModel(pos, scale, id, scl, m_number[number], damage);
 }