#include "stdafx.h"
#include "IEnemy.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "Player.h"
#include "GameCamera.h"
#include "FontNumber.h"
const float IEnemy::m_frame = 40.0f; 
IEnemy::IEnemy(const int& h,const int& a,const int& e,const int dropchances[Weapon::m_HighestRarity],const int dropmaterialchances[Material::m_HighestRarity],const int& meseta):m_HP(h),m_Attack(a),m_Exp(e),m_dropmeseta(meseta)
{
	for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		m_dropChances[i] = *dropchances;
		dropchances++;
	}
	for (int i = 0; i < Material::m_HighestRarity; i++) {
		m_dropmaterialChances[i] = *dropmaterialchances;
		dropmaterialchances++;
	}
	m_gamecamera = FindGO<GameCamera>();
}

IEnemy::~IEnemy()
{
	if (m_death) {
		Drop();
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->Play(L"Asset/effect/drop/drop.efk", 1.0f, m_position, CQuaternion::Identity(), { 30.0f*(m_r/70.0f),30.0f*(m_r / 70.0f),30.0f*(m_r / 70.0f) });
		effect->SetSpeed(1.0f);
	}
	else {
		m_collision->Delete();
	}
}

void IEnemy::CCollision(const CVector3& pos,const float& l,const float& r)
{
	m_collision = new SuicideObj::CCollisionObj;
	//形状の作成
	m_collision->CreateSphere(pos + CVector3::AxisY()*l, CQuaternion::Identity(),r);
	m_r = r;
	//寿命を設定
	m_collision->SetTimer(enNoTimer);//enNoTimerで寿命なし
	//名前を設定
	m_collision->SetName(L"IEnemy");
	//クラスのポインタを設定
	m_collision->SetClass(this);
}

void IEnemy::SetCCollision(const CVector3& pos,const float& l)
{
	m_fontposition = pos + CVector3::AxisY()*l;
	if (m_death) {
		return;
	}
	m_collision->SetPosition(pos + CVector3::AxisY()*l);
	m_position = pos;
	m_collisionposition = pos + CVector3::AxisY()*l;
	m_timer += m_frame * GetDeltaTimeSec();
	m_timer8 += m_frame * GetDeltaTimeSec();
}

void IEnemy::Damage(const int& attack,int number)
{
	int HP = m_HP;
	switch (number) {
	case 0:
		if (m_timer >= 15) {		//通常攻撃
			m_HP -= attack;
			m_timer = 0;
			m_damage = true;
			//プレイヤーのPPを回復
			Player* player = FindGO<Player>(L"Player");
			player->RecoveryPP();
		}
		break;
	case 8:
		if (m_timer8 >= 100) {		//モルガン
			m_HP -= attack;
			m_timer8 = 0;
			m_damage = true;
		}
		break;
	default:
		m_HP -= attack;
		m_damage = true;
		break;
	}
	if (HP != m_HP) {
		//SE
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/damage.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(500.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtrue
		GameObj::Suicider::CEffekseer* effect = new GameObj::Suicider::CEffekseer;
		effect->Play(L"Asset/effect/hit/hit.efk", 1.0f, m_collisionposition, CQuaternion::Identity(), { 15.0f,15.0f,15.0f });
		effect->SetSpeed(1.0f);
		m_displayfont = true;
		m_damagecount = attack;
	}
	if (m_HP <= 0) {
		m_death = true;
		m_collision->Delete();
	}
	if (!m_displayfont) {
		return;
	}
	else {
		FontNumber* fn = new FontNumber;
		fn->SetNumber(m_damagecount);
		fn->SetPosition(m_fontposition);
		m_displayfont = false;
	}
	//ランダムでエネミーの被ダメ時の行動を制限する
	int rn = rand() % 100 + 1;
	if (rn <= 70) {
		m_damage = false;
	}
}

void IEnemy::PostRender()
{
	
}

void IEnemy::Drop()
{
	int rad = rand() % 100+1;
	int rpos = rand() % 30 + 10;
	//武器のドロップ
	for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		if (m_dropChances[i] >= rad) {
			DropItem* dropitem = new DropItem;
			dropitem->SetRarity(i);
			CVector3 pos = m_position;
			pos.x += rpos * 1.5f;
			pos.z += rpos * 1.5f;
			dropitem->SetPosition(pos);
			dropitem->SetName(L"DropItem");
			dropitem->SetisWeapon();
			m_isdropWeapon = true;
			break;
		}
	}
	//武器のドロップが無い場合、メセタをドロップ
	if (!m_isdropWeapon) {
		DropItem* dropitem = new DropItem;
		if (rad >= 50) {
			m_dropmeseta += rand() % m_dropmeseta / m_mesetarand;
		}
		else {
			m_dropmeseta -= rand() % m_dropmeseta / m_mesetarand;
		}
		dropitem->SetMeseta(m_dropmeseta);
		CVector3 pos = m_position;
		pos.x += rpos * 1.5f;
		pos.z += rpos * 1.5f;
		dropitem->SetPosition(pos);
		dropitem->SetName(L"DropItem");
	}
	//素材をドロップ
	for (int i = 0; i < Material::m_HighestRarity; i++) {
		if (m_dropmaterialChances[i] >= rad) {
			DropMaterial* dropmaterial = new DropMaterial;
			dropmaterial->SetRarity(i);
			CVector3 pos = m_position;
			pos.x -= rpos * 1.5f;
			pos.z -= rpos * 1.5f;
			dropmaterial->SetPosition(pos);
			dropmaterial->SetName(L"DropMaterial");
			break;
		}
	}
}

