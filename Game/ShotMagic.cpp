#include "stdafx.h"
#include "ShotMagic.h"
#include "PlayerStatus.h"
#include "Player.h"
#include "IEnemy.h"
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
	}
	return true;
}

 void ShotMagic::Update()
{
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
	 }
	 int i = 0;
	 for (auto& mgml : m_magicmocelList) {
		 if (mgml.s_delete) {
			 i++;
		 }
		 else {
			 if (mgml.s_timer >= m_deletetime) {
				 delete mgml.s_skinModelReder;
				 mgml.s_skinModelReder = nullptr;
				 delete mgml.s_collision;
				 mgml.s_collision = nullptr;
				 mgml.s_delete = true;
				 if (i == m_modelnumber) {
					 delete this;
				 }
			 }
			 else {
				 CVector3 pos = mgml.s_skinModelReder->GetPos() + m_movespeed;
				 mgml.s_skinModelReder->SetPos(pos);
				 mgml.s_collision->SetPosition(pos);
				 mgml.s_timer += 1.0f;
			 }
		 }
	 }
	
}
 void ShotMagic::SetCollisionModel(const CVector3& pos, const float& scale,const int& id)
 {
	 GameObj::CSkinModelRender* skinModelRender = new GameObj::CSkinModelRender;
	 skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
	 skinModelRender->SetScale(m_scale);
	 skinModelRender->SetPos(pos);
	 //攻撃判定の発生
	 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
	 attackCol->CreateSphere(pos, CQuaternion::Identity(),scale);
	 //寿命を設定
	 attackCol->SetTimer(enNoTimer);
	 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		 //衝突した判定の名前が"IEnemy"ならm_Attack分だけダメージ与える
		 if (param.EqualName(L"IEnemy")) {
			 IEnemy* enemy = param.GetClass<IEnemy>();//相手の判定に設定されているCEnemyのポインタを取得
			 //エネミーにダメージ
			 enemy->Damage(m_damage);
			 //もしエネミーのHPが0以下になったら
			 if (enemy->GetDeath()) {
				 //エネミーの経験値をプレイヤーの経験値に加算
				 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
				 playerstatus->PlusExp(enemy->GetExp());
			 }
		 }
	 }
	 );
	 m_magicmocelList.push_back({skinModelRender,attackCol});
 }

 void ShotMagic::Foie()
 {
	 m_scale = { 2.0f,2.0f,2.0f };
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 SetCollisionModel(m_position,90.0f,m_id);
	 m_movespeed = m_directionplayer * 15.0f;
	 m_deletetime = 30.0f;
	 m_modelnumber = 1;
 }
 void ShotMagic::FoieUpdate()
 {
	
 }

 void ShotMagic::Irugra()
 {
	 m_scale = { 1.0f,1.0f,1.0f };
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 m_movespeed = m_directionplayer * 30.0f;
	 m_deletetime = 50;
	 m_modelnumber = 3;
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::IrugraUpdate()
 {
	 if (m_modelcount != m_modelnumber) {
		 if (m_timer >= 12) {
			 SetCollisionModel(m_position, 50,m_id);
			 m_modelcount++;
			 m_timer = 0;
		 }
	 }
	 m_timer++;
 }

 void ShotMagic::Zanbas()
 {
	 m_scale = { 4.0f,4.0f,4.0f };
	 m_position = m_position; //+ CVector3::AxisY()*60.0f;
	 m_movespeed = { CVector3::Zero() };
	 SetCollisionModel(m_position, 180.0f,m_id);
	 m_deletetime = 10;
	 m_modelnumber = 1;
	 m_damage /= m_modelnumber;
 }

 void ShotMagic::ZanbasUpdate()
 {

 }
 
 void ShotMagic::Shihuta()
 {
	 m_scale = { 3.0f,3.0f,3.0f };
	 m_position = m_position; //+ CVector3::AxisY()*60.0f;
	 m_movespeed = { CVector3::Zero() };
	 SetCollisionModel(m_position, 0,m_id);
	 m_deletetime = 10;
	 m_modelnumber = 1;
	 m_damage /= m_modelnumber;
	 Player* player = FindGO<Player>(L"Player");
	 player->SetShihuta();
 }
	
 void ShotMagic::ShihutaUpdate()
 {

 }