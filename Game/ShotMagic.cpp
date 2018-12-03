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
	}
	return true;
}

 void ShotMagic::Update()
{

	 switch (m_id) {
	 case 1:
		 FoieUpdate();
		 break;
	 }
	 int i = 0;
	 for (auto mgml : m_magicmocelList) {
		 i++;
		 if (mgml.s_delete) {
			 return;
		 }
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
			 mgml.s_timer = mgml.s_timer+1.0f;
		 }
	 }
}
 void ShotMagic::SetCollisionModel(const CVector3& pos, const float& scale)
 {
	 GameObj::CSkinModelRender* skinModelRender = new GameObj::CSkinModelRender;
	 skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
	 skinModelRender->SetScale(m_scale);
	 skinModelRender->SetPos(pos);
	 //�U������̔���
	 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
	 attackCol->CreateSphere(pos, CQuaternion::Identity(),scale);
	 //������ݒ�
	 attackCol->SetTimer(enNoTimer);
	 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
		 //�Փ˂�������̖��O��"IEnemy"�Ȃ�m_Attack�������_���[�W�^����
		 if (param.EqualName(L"IEnemy")) {
			 IEnemy* enemy = param.GetClass<IEnemy>();//����̔���ɐݒ肳��Ă���CEnemy�̃|�C���^���擾
			 //�G�l�~�[�Ƀ_���[�W
			 enemy->Damage(m_damage);
			 //�����G�l�~�[��HP��0�ȉ��ɂȂ�����
			 if (enemy->GetDeath()) {
				 //�G�l�~�[�̌o���l���v���C���[�̌o���l�ɉ��Z
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
	 SetCollisionModel(m_position,100.0f);
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
	 SetCollisionModel(m_position,50);
	 m_movespeed = m_directionplayer * 15.0f;
	 m_deletetime = 40;
	 m_modelnumber = 3;
 }

 void ShotMagic::IrugraUpdate()
 {
	 
 }

