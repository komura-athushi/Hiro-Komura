#include "stdafx.h"
#include "ShotMagic.h"
#include "PlayerStatus.h"
#include "Player.h"
#include "IEnemy.h"
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
				 delete mgml.s_skinModelReder;
				 mgml.s_skinModelReder = nullptr;
				 delete mgml.s_collision;
				 mgml.s_collision = nullptr;
				 mgml.s_delete = true;
			 }
			 else {
				 //モデルとコリジョンを動かします
				 mgml.s_position = mgml.s_skinModelReder->GetPos() + m_movespeed;
				 mgml.s_skinModelReder->SetPos(mgml.s_position);
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
 void ShotMagic::SetCollisionModel(const CVector3& pos, const float& scale,const int& id, const int& number, bool damage)
 {
	 GameObj::CSkinModelRender* skinModelRender = new GameObj::CSkinModelRender;
	 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
	 //MagicModelクラスの可変長配列に生成したモデルとコリジョンを格納します
	 m_magicmocelList.push_back({ skinModelRender,attackCol });
	 //モデルを作成します
	 skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
	 skinModelRender->SetScale(m_scale);
	 skinModelRender->SetPos(pos);
	 //攻撃判定の発生
	 attackCol->CreateSphere(pos, CQuaternion::Identity(),scale);
	 //寿命を設定
	 attackCol->SetTimer(enNoTimer);
	 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
		 if (param.EqualName(L"IEnemy")) {
			 IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
			 if (id!= 5) {
				 //エネミーにダメージ
				 enemy->Damage(m_damage, id);
				 //もしエネミーのHPが0以下になったら
				 if (enemy->GetDeath()) {
					 //エネミーの経験値をプレイヤーの経験値に加算
					 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
					 playerstatus->PlusExp(enemy->GetExp());
				 }
			 }
			 else if (id == 5) {
				 ShotMagic* shotmagic = FindGO<ShotMagic>(L"ShotMagic");
				 CVector3 pos = shotmagic->GetPosition(number);
				 shotmagic->DeleteMagicModel(number);
				 GameObj::CSkinModelRender* skinModelRender = new GameObj::CSkinModelRender;
				 skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
				 skinModelRender->SetScale(m_scale * 4.0f);
				 skinModelRender->SetPos(pos);
				 //攻撃判定の発生
				 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
				 attackCol->CreateSphere(pos, CQuaternion::Identity(), scale * 4.0f);
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
		 }
	 }
	 );
	 m_modelcount++;
 }

 void ShotMagic::Foie()
 {
	 m_deletetime = 30.0f;
	 m_modelnumber = 1;
	 m_scale = { 2.0f,2.0f,2.0f };
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 SetCollisionModel(m_position,90.0f,m_id);
	 m_movespeed = m_directionplayer * 15.0f;
 }
 void ShotMagic::FoieUpdate()
 {
	
 }

 void ShotMagic::Irugra()
 {
	 m_deletetime = 50;
	 m_modelnumber = 3;
	 m_scale = { 1.0f,1.0f,1.0f };
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * 30.0f;
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::IrugraUpdate()
 {
	 if (m_modelcount != m_modelnumber) {
		 if (m_timer >= 12) {
			 SetCollisionModel(m_position, 50,m_id);
			 m_timer = 0;
		 }
	 }
	 m_timer++;
 }

 void ShotMagic::Zanbas()
 {
	 m_deletetime = 10;
	 m_modelnumber = 1;
	 m_scale = { 5.0f,5.0f,5.0f };
	 m_position = m_position; //+ CVector3::AxisY()*60.0f;
	 m_movespeed = { CVector3::Zero() };
	 SetCollisionModel(m_position, 225.0f,m_id);
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::ZanbasUpdate()
 {

 }
 
 void ShotMagic::Shihuta()
 {
	 m_deletetime = 10;
	 m_modelnumber = 1;
	 m_scale = { 3.0f,3.0f,3.0f };
	 m_position = m_position; //+ CVector3::AxisY()*60.0f;
	 m_movespeed = { CVector3::Zero() };
	 SetCollisionModel(m_position, 0,m_id);
	 m_damage /= m_modelnumber;
	 Player* player = FindGO<Player>(L"Player");
	 player->SetShihuta();
 }
	
 void ShotMagic::ShihutaUpdate()
 {
	
 }

 void ShotMagic::MagicSphere()
 {
	 m_deletetime = 30.0f;
	 m_modelnumber = 1;
	 m_scale = { 0.5f,0.5f,0.5f };
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 //SetCollisionModel(m_position, 28.0f, m_id, m_modelcount,false);
	 SetCollisionModelnoDamage(m_position, 28.0f, m_id, m_modelcount, false);
	 m_movespeed = m_directionplayer * 15.0f;
	
 }

 void ShotMagic::MagicSphereUpdate()
 {

 }

 void ShotMagic::DeleteMagicModel(const int& number)
 {
	 delete m_magicmocelList[number].s_skinModelReder;
	 m_magicmocelList[number].s_skinModelReder = nullptr;
	 DeleteGO(m_magicmocelList[number].s_collision);
	 m_magicmocelList[number].s_collision = nullptr;
	 m_magicmocelList[number].s_delete = true;
 }

 void ShotMagic::SetCollisionModelnoDamage(const CVector3& pos, const float& scale, const int& id, const int& number, bool damage)
 {
	 SetCollisionModel(pos, scale, id, m_number[number], damage);
 }