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
	//���@�̔ԍ��ɂ���ď�����ς��܂�
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
	 //���@�̔ԍ��ɂ���ď�����ς��܂�
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
	 //MagciModel�\���̂̉ϒ��z��ɃA�N�Z�X���܂�
	 for (auto& mgml : m_magicmocelList) {
		 if (mgml.s_delete) {
			 i++;
		 }
		 else {
			 //�폜���鎞�Ԃ𒴂��Ă����烂�f���ƃR���W�������폜���܂�
			 if (mgml.s_timer >= m_deletetime) {
				 delete mgml.s_skinModelReder;
				 mgml.s_skinModelReder = nullptr;
				 delete mgml.s_collision;
				 mgml.s_collision = nullptr;
				 mgml.s_delete = true;
				 //���������R���W�����ƃ��f�����S�č폜����Ă���΁A���g���폜���܂�
				 if (i == m_modelnumber) {
					 delete this;
				 }
			 }
			 else {
				 //���f���ƃR���W�����𓮂����܂�
				 CVector3 pos = mgml.s_skinModelReder->GetPos() + m_movespeed;
				 mgml.s_skinModelReder->SetPos(pos);
				 mgml.s_collision->SetPosition(pos);
				 mgml.s_timer += 1.0f;
			 }
		 }
	 }
	
}
 void ShotMagic::SetCollisionModel(const CVector3& pos, const float& scale,const int& id,bool damage)
 {
	 //���f�����쐬���܂�
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
			 if (damage) {
				 //�G�l�~�[�Ƀ_���[�W
				 enemy->Damage(m_damage, id);
				 //�����G�l�~�[��HP��0�ȉ��ɂȂ�����
				 if (enemy->GetDeath()) {
					 //�G�l�~�[�̌o���l���v���C���[�̌o���l�ɉ��Z
					 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
					 playerstatus->PlusExp(enemy->GetExp());
				 }
			 }
			 else {

				 if (id == 5) {
					 CVector3 pos = enemy->GetPosition();
					 GameObj::CSkinModelRender* skinModelRender = new GameObj::CSkinModelRender;
					 skinModelRender->Init(L"Resource/modelData/Magic_Sample.cmo");
					 skinModelRender->SetScale(m_scale * 2);
					 skinModelRender->SetPos(pos);
					 //�U������̔���
					 SuicideObj::CCollisionObj* attackCol = NewGO<SuicideObj::CCollisionObj>();
					 attackCol->CreateSphere(pos, CQuaternion::Identity(), scale * 2);
					 //������ݒ�
					 attackCol->SetTimer(5);
					 attackCol->SetCallback([&](SuicideObj::CCollisionObj::SCallbackParam& param) {
						 //�Փ˂�������̖��O��"IEnemy"�Ȃ�m_Attack�������_���[�W�^����
						 if (param.EqualName(L"IEnemy")) {
							 IEnemy* enemy = param.GetClass<IEnemy>();//����̔���ɐݒ肳��Ă���CEnemy�̃|�C���^���擾
								 //�G�l�~�[�Ƀ_���[�W
							 enemy->Damage(m_damage, id);
							 //�����G�l�~�[��HP��0�ȉ��ɂȂ�����
							 if (enemy->GetDeath()) {
								 //�G�l�~�[�̌o���l���v���C���[�̌o���l�ɉ��Z
								 PlayerStatus* playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
								 playerstatus->PlusExp(enemy->GetExp());
							 }
						 }
					 }
					 );
				 }
			 }
		 }
	 }
	 );
	 //MagicModel�N���X�̉ϒ��z��ɐ����������f���ƃR���W�������i�[���܂�
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
	 m_scale = { 5.0f,5.0f,5.0f };
	 m_position = m_position; //+ CVector3::AxisY()*60.0f;
	 m_movespeed = { CVector3::Zero() };
	 SetCollisionModel(m_position, 225.0f,m_id);
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

 void ShotMagic::MagicSphere()
 {
	 m_scale = { 1.5f,1.5f,1.5f };
	 m_position = m_position + CVector3::AxisY()*60.0f;
	 SetCollisionModel(m_position, 75.0f, m_id,false);
	 m_movespeed = m_directionplayer * 15.0f;
	 m_deletetime = 30.0f;
	 m_modelnumber = 1;
 }

 void ShotMagic::MagicSphereUpdate()
 {

 }