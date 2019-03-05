#include "stdafx.h"
#include "Boss3.h"
#define _USE_MATH_DEFINES //M_PI 円周率呼び出し
#include <math.h> 
#include "Game.h"
#include "Player.h"
#include "BossAttack.h"
#include "GameCamera.h"
#include "Teleport.h"
//cppでエネミーのレア度ごとのドロップ率を設定
const int Boss3::m_dropChances[Weapon::m_HighestRarity] = { 0,0,0,100,0,0,0 };
const int Boss3::m_dropmaterialChances[Material::m_HighestRarity] = { 0.0f,100.0f,0.0f };
//ボス3()です
Boss3::Boss3() : IEnemy(m_MaxHP, m_Attack, m_EXP, m_dropChances, m_dropmaterialChances, m_meseta)
{

}

Boss3::~Boss3()
{
	delete m_skinModelRender;
	Teleport* tl = new Teleport;
	tl->SetPosition(m_position);
	tl->SetName(L"Teleport");
}

bool Boss3::Start()
{
	IEnemy::CCollision(m_position, m_collisionheight, m_r);
	//アニメーション
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/boss2/boss2_idle.tka");
	/*m_animClip[enAnimationClip_run].Load(L"Asset/animData/boss2/boss2_run.tka");
	m_animClip[enAnimationClip_hikkaki].Load(L"Asset/animData/boss2/boss2_hikkaki.tka");
	m_animClip[enAnimationClip_fire].Load(L"Asset/animData/boss2/boss2_fire.tka");
	m_animClip[enAnimationClip_press].Load(L"Asset/animData/boss2/boss2_press.tka");
	m_animClip[enAnimationClip_damage].Load(L"Asset/animData/boss2/boss2_damage.tka");
	m_animClip[enAnimationClip_death].Load(L"Asset/animData/boss2/boss2_death.tka");*/
	m_animClip[enAnimationClip_idle].SetLoopFlag(true);
	/*m_animClip[enAnimationClip_run].SetLoopFlag(true);
	m_animClip[enAnimationClip_hikkaki].SetLoopFlag(false);
	m_animClip[enAnimationClip_fire].SetLoopFlag(false);
	m_animClip[enAnimationClip_press].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_death].SetLoopFlag(false);*/
	//ドラゴンのスキンモデルレンダーを表示
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/boss3.cmo", m_animClip, enAnimationClip_num);
	
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPos(m_position);
	CQuaternion rot = CQuaternion::Identity();
	CVector3 pos = m_position;
	//pos.y += 500.0f;
	m_staticobject.CreateSphere(pos, rot, 150.0f);
	//unityChanのボーンを検索
	//m_bonehead = m_skinModelRender->FindBoneID(L"Bone016");
	return true;
}
void Boss3::Update()
{}