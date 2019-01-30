#include "stdafx.h"
#include "IEnemy.h"
#include "DropItem.h"
#include "DropMaterial.h"
#include "Player.h"
#include "GameCamera.h"
const float IEnemy::m_frame = 40.0f; 
IEnemy::IEnemy(const int& h,const int& a,const int& e,const int dropchances[Weapon::m_HighestRarity],const int dropmaterialchances[Material::m_HighestRarity],const int& meseta):m_HP(h),m_Attack(a),m_Exp(e),m_dropmeseta(meseta)
{
	/*for (int i = 0; i < Weapon::m_HighestRarity; i++) {
		m_dropChances[i] = *dropchances;
		dropchances++;
	}*/
	memcpy(m_dropChances, dropchances, sizeof(dropchances));
	memcpy(m_dropmaterialChances, dropmaterialchances, sizeof(dropmaterialchances));
	m_gamecamera = FindGO<GameCamera>();
}

IEnemy::~IEnemy()
{
	if (m_death) {
		Drop();
	}
	else {
		m_collision->Delete();
	}
}

void IEnemy::CCollision(const CVector3& pos,const float& l,const float& r)
{
	//くらい判定の作成
	//m_collision = std::make_unique<SuicideObj::CCollisionObj>();
	m_collision = new SuicideObj::CCollisionObj;
	//形状の作成
	m_collision->CreateSphere(pos + CVector3::AxisY()*l, CQuaternion::Identity(),r);
	//寿命を設定
	m_collision->SetTimer(enNoTimer);//enNoTimerで寿命なし
	//名前を設定
	m_collision->SetName(L"IEnemy");
	//クラスのポインタを設定
	m_collision->SetClass(this);
}

void IEnemy::SetCCollision(const CVector3& pos,const float& l)
{
	if (m_displayfont) {
		m_fonttimer += m_frame*GetDeltaTimeSec();
		if (m_fonttimer >= 20) {
			m_fonttimer = 0;
			m_displayfont = false;
		}
	}
	else {
		m_fontposition = pos + CVector3::AxisY()*l;
	}
	if (m_death) {
		return;
	}
	m_collision->SetPosition(pos + CVector3::AxisY()*l);
	m_position = pos;
	m_collisionposition = pos + CVector3::AxisY()*l;
	m_timer += m_frame * GetDeltaTimeSec();
	m_timer1 += m_frame * GetDeltaTimeSec();
	m_timer2 += m_frame * GetDeltaTimeSec();
	m_timer3 += m_frame * GetDeltaTimeSec();
	m_timer5 += m_frame * GetDeltaTimeSec();
}

void IEnemy::Damage(const int& attack,int number)
{
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
	case 1:
		if (m_timer1 >= 40) {		//フォイエ
			m_HP -= attack;
			m_timer1 = 0;
			m_damage = true;
		}
		break;
	case 2:
		if (m_timer2 >= 12) {		//イルグランツ
			m_HP -= attack;
			m_timer2 = 0;
			m_damage = true;
		}
		break;
	case 3:
		if (m_timer3 >= 25) {		//ザンバース
			m_HP -= attack;
			m_timer3 = 0;
			m_damage = true;
		}
		break;
	case 4:							//シフタ(ダメージ無し)
		break;
	case 5:							
		if (m_timer5 >= 20) {		//マジスフィ
			m_HP -= attack;
			m_timer5 = 0;
			m_damage = true;
		}
		break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
		                                                                                    
	}
	if (m_HP <= 0) {
		m_death = true;
		m_collision->Delete();
	}
	if (m_damage) {
		m_damagecount = attack;
		m_displayfont = true;
	}
}

void IEnemy::PostRender()
{
	if (!m_displayfont) {
		return;
	}
	if (m_gamecamera != nullptr) {
	    wchar_t output[256];
	    //swprintf_s(output, L"HP   %d\natk  %d\nドロップ  %d\n", m_HP,m_Attack,m_dropChances[1]);
	    swprintf_s(output, L"%d\n", m_damagecount);
		CVector2 pos = m_gamecamera->GetCamera()->CalcScreenPosFromWorldPos(m_fontposition);
		//m_font.DrawScreenPos(output,pos);
		m_font.Draw(output, pos, CVector4(225.0f, 00.0f, 00.0f, 0.8f));
	}
}

void IEnemy::Drop()
{
	int rad = rand() % 100;
	int rpos = rand() % 10 + 30;
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

