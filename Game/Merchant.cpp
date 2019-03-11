#include "stdafx.h"
#include "Merchant.h"
#include "Player.h"
#include "PlayerStatus.h"
Merchant::Merchant()
{
}


Merchant::~Merchant()
{
	delete m_skinModelRender;
	for (int i = 0; i < m_playerstatus->GetEquipmentNumber(); i++) {
		delete m_spritelist[i];
		delete m_spritefont[i];
	}
}

bool Merchant::Start()
{
	//アニメーションファイルをロード
	m_animClip[enAnimationClip_idle].Load(L"Asset/animData/idle.tka", true);
	m_skinModelRender = new GameObj::CSkinModelRender;
	m_skinModelRender->Init(L"Resource/modelData/zunko.cmo", m_animClip, enAnimationClip_num);
	m_skinModelRender->SetPos(m_position);
	m_skinModelRender->SetScale(m_scale);
	//m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_protrotation = m_rotation;
	m_skinModelRender->SetRot(m_rotation);
	m_playerstatus = FindGO<PlayerStatus>(L"PlayerStatus");
	m_gamedata = FindGO<GameData>(L"GameData");
	m_equipmentnumber = m_playerstatus->GetEquipmentNumber();
 	for (int i = 0; i < m_equipmentnumber; i++) {
		CSprite* sprite = new CSprite;
		sprite->Init(m_playerstatus->GetSpriteName(m_playerstatus->GetWeaponNumber(i)));
		m_spritelist.push_back(sprite);
		m_spritefont.push_back(new CFont);
	}
	m_cursor.Init(L"Resource/sprite/cursor.dds");
	m_sprite2.Init(L"Resource/sprite/window.dds");
	m_sprite3.Init(L"Resource/sprite/upgradewindow.dds");
	m_back.Init(L"Resource/sprite/upgrade_back.dds");
	m_equipment.Init(L"Resource/sprite/equipment.dds");
	m_base.Init(L"Resource/sprite/base.dds");
	m_mesetasprite.Init(L"Resource/sprite/upgrade_mesetawindow.dds");
	return true;
}

void Merchant::Update()
{
	if (m_player == nullptr) {
		m_player = FindGO<Player>();
		return;
	}
	Turn();
	m_skinModelRender->GetAnimCon().Play(enAnimationClip_idle, 0.2f);
}

void Merchant::Turn()
{
	CVector3 pos = m_player->GetPosition() - m_position;
	//プレイヤーが一定距離以内に居たらプレイヤーの方向を向くようにする
	if (pos.Length() <= 300.0f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(pos.x, pos.z));
	}
	//プレイヤーが一定距離以外に居たら回転をもとに戻す
	else if (pos.Length() >= 1500.0f) {
		m_rotation = m_protrotation;
	}
	m_skinModelRender->SetRot(m_rotation);
}

void Merchant::BackState()
{
	switch (m_state) {
	case enState_Material:
		m_state = enState_Base;
		break;
	case enState_Decision:
		m_state = enState_Material;
		break;
	case enState_Upgrade:
		m_state = enState_Base;
		break;
	}
}

void Merchant::Base()
{
	wchar_t output[256];
	swprintf_s(output, L"どの武器を強化しますか？\n");
	//武器のアイコン表示
	CVector2 pos = m_aiconposition;
	pos.y -= m_swordid2 * 70.0f;
	for (int i = 0; i < m_playerstatus->GetEquipmentNumber(); i++) {
		m_spritelist[i]->DrawScreenPos(pos, m_aiconscale);
		if (m_swordid1 == i) {
			m_equipment.DrawScreenPos(pos, m_aiconscale, CVector2::Zero(),
				0.0f,
				{1.0f,1.0f,1.0f,1.0f},
				DirectX::SpriteEffects_None,
				0.3f);
		}
		wchar_t output[50];
		if (m_playerstatus->GetEuipment(i)->GetLv() != 5) {
			swprintf_s(output, L"武器Lv %d\n強化費用 %dM\n", m_playerstatus->GetEuipment(i)->GetLv(), m_playerstatus->GetEuipment(i)->GetCost());
		}
		else {
			swprintf_s(output, L"武器Lv %d\n", m_playerstatus->GetEuipment(i)->GetLv());
		}
		CVector2 pos2 = pos;
		pos2.x += 100.0f;
		m_spritefont[i]->DrawScreenPos(output, pos2, CVector4::White(), { 0.7f,0.7f });
		pos.y += 70.0f;
	}
	m_cursor.DrawScreenPos(m_aiconposition, m_aiconscale, CVector2::Zero(),
		0.0f,
		CVector4::White(),
		DirectX::SpriteEffects_None,
		0.4f);
	int number = m_swordid2;
	if (Pad(0).GetButton(enButtonUp) && m_button) {
		number--;
		m_button = false;
	}
	else if (Pad(0).GetButton(enButtonDown) && m_button) {
		number++;
		m_button = false;
	}
	else {
		if (!Pad(0).GetButton(enButtonUp) && !Pad(0).GetButton(enButtonDown) && !Pad(0).GetButton(enButtonA)) {
			m_button = true;
		}
	}
	//上ボタン
	if (m_swordid2 > number) {
		if (m_swordid2 != 0) {
			m_swordid2 = number;
		}
	}
	//下ボタン
	else if (m_swordid2< number) {
		if (m_swordid2 != m_playerstatus->GetEquipmentNumber() - 1) {
			m_swordid2 = number;
		}
	}
	if (Pad(0).GetButton(enButtonA) && m_button) {
		if (m_playerstatus->GetEuipment(m_swordid2)->GetLv() == 5) {
		}
		else {
			m_state = enState_Material;
		}
		m_button = false;
	}
	m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	m_sprite2.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_sprite3.DrawScreenPos({ 780.0f,0.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.8f);
}

void Merchant::Material()
{
	wchar_t output[256];
	swprintf_s(output, L"どの武器を素材にしますか？\n");
	//武器のアイコン表示
	CVector2 pos = m_aiconposition;
	pos.y -= m_swordid3 * 70.0f;
	for (int i = 0; i < m_playerstatus->GetEquipmentNumber(); i++) {
		m_spritelist[i]->DrawScreenPos(pos, m_aiconscale);
		if (m_swordid2 == i) {
			m_base.DrawScreenPos(pos, m_aiconscale, CVector2::Zero(),
				0.0f,
				{ 1.0f,1.0f,1.0f,1.0f },
				DirectX::SpriteEffects_None,
				0.3f);
		}
		else if(m_swordid1 == i){
			m_equipment.DrawScreenPos(pos, m_aiconscale, CVector2::Zero(),
				0.0f,
				{ 1.0f,1.0f,1.0f,1.0f },
				DirectX::SpriteEffects_None,
				0.3f);
		}
		wchar_t output[30];
		if (m_playerstatus->GetEuipment(i)->GetLv() != 5) {
			swprintf_s(output, L"武器Lv %d\n経験値 +%d\n", m_playerstatus->GetEuipment(i)->GetLv(), m_playerstatus->GetEuipment(i)->GetMaterialExp());
		}
		else {
			swprintf_s(output, L"武器Lv %d\n", m_playerstatus->GetEuipment(i)->GetLv());
		}
		CVector2 pos2 = pos;
		pos2.x += 100.0f;
		m_spritefont[i]->DrawScreenPos(output, pos2, CVector4::White(), { 0.7f,0.7f });
		pos.y += 70.0f;
	}
	m_cursor.DrawScreenPos(m_aiconposition, m_aiconscale, CVector2::Zero(),
		0.0f,
		CVector4::White(),
		DirectX::SpriteEffects_None,
		0.4f);
	int number = m_swordid3;
	if (Pad(0).GetButton(enButtonUp) && m_button) {
		number--;
		m_button = false;
	}
	else if (Pad(0).GetButton(enButtonDown) && m_button) {
		number++;
		m_button = false;
	}
	else {
		if (!Pad(0).GetButton(enButtonUp) && !Pad(0).GetButton(enButtonDown) && !Pad(0).GetButton(enButtonA)) {
			m_button = true;
		}
	}
	//上ボタン
	if (m_swordid3 > number) {
		if (m_swordid3 != 0) {
			m_swordid3 = number;
		}
	}
	//下ボタン
	else if (m_swordid3 < number) {
		if (m_swordid3 != m_playerstatus->GetEquipmentNumber() - 1) {
			m_swordid3 = number;
		}
	}
	if (Pad(0).GetButton(enButtonA) && m_button) {
		if (!m_playerstatus->GetisEquippedto(m_swordid3) && m_swordid3 != m_swordid2) {
			m_state = enState_Decision;
		}
		m_button = false;
	}
	m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	m_sprite2.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_sprite3.DrawScreenPos({ 780.0f,0.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.8f);
}

void Merchant::Decision()
{
	if (!m_isspriteInit) {
		m_basesprite.Init(m_playerstatus->GetSpriteName(m_playerstatus->GetWeaponNumber(m_swordid2)));
		m_materialsprite.Init(m_playerstatus->GetSpriteName(m_playerstatus->GetWeaponNumber(m_swordid3)));
		m_upgradesprite.Init(m_playerstatus->GetSpriteName(m_playerstatus->GetWeaponNumber(m_swordid2)));
		int ep = m_playerstatus->GetEuipment(m_swordid3)->GetMaterialExp();
		m_playerstatus->GetEuipment(m_swordid2)->KariPlusExp(ep);
		m_level = m_playerstatus->GetEuipment(m_swordid2)->GetKariLv();
		m_isspriteInit = true;
	}
	//ベース
	wchar_t output2[10];
	swprintf_s(output2, L"ベース\n");
	m_font.DrawScreenPos(output2, { 150.0f,20.0f }, { 225.0f,000.0f,000.0,1.0f }, { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);
	m_back.DrawScreenPos({ 150.0f,50.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_basesprite.DrawScreenPos({ 150.0f,50.0f }, {0.313f,0.3f}, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.7f);
	wchar_t output4[150];
	swprintf_s(output4, L"武器Lv.%d\n打  %d\n法  %d\n１  %ls\n２  %ls\n３  %ls\n経験値\n累計      %d\n次Lvまで  %d\n",m_playerstatus->GetEuipment(m_swordid2)->GetLv(), m_playerstatus->GetEuipment(m_swordid2)->GetAtk(), m_playerstatus->GetEuipment(m_swordid2)->GetMatk(),
		m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(1), m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(2), m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(3), m_playerstatus->GetEuipment(m_swordid2)->GetExp(), m_playerstatus->GetEuipment(m_swordid2)->GetNextExp());
	m_font.DrawScreenPos(output4, { 150.0f,200.0f },CVector4::White(), { 0.5f,0.5f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	//素材
	wchar_t output3[10];
	swprintf_s(output3, L"素材\n");
	m_font.DrawScreenPos(output3, { 500.0f,20.0f }, { 200.0f,200.0f,200.0,1.0f }, { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);
	m_back.DrawScreenPos({ 500.0f,50.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_materialsprite.DrawScreenPos({ 500.0f,50.0f }, {0.313f,0.3f}, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.7f);
	wchar_t output5[150];
	swprintf_s(output5, L"武器Lv.%d\n打  %d\n法  %d\n１  %ls\n２  %ls\n３  %ls\n経験値   +%d\n", m_playerstatus->GetEuipment(m_swordid3)->GetLv(), m_playerstatus->GetEuipment(m_swordid3)->GetAtk(), m_playerstatus->GetEuipment(m_swordid3)->GetMatk(),
		m_playerstatus->GetEuipment(m_swordid3)->GetAbilityName(1), m_playerstatus->GetEuipment(m_swordid3)->GetAbilityName(2), m_playerstatus->GetEuipment(m_swordid3)->GetAbilityName(3), m_playerstatus->GetEuipment(m_swordid3)->GetMaterialExp());
	m_font.DrawScreenPos(output5, { 500.0f,200.0f }, CVector4::White(), { 0.5f,0.5f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	//強化結果
	wchar_t output7[10];
	swprintf_s(output7, L"結果予測\n");
	m_font.DrawScreenPos(output7, { 1000.0f,20.0f }, { 200.0f,200.0f,200.0,1.0f }, { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);
	m_back.DrawScreenPos({ 1000.0f,50.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_upgradesprite.DrawScreenPos({ 1000.0f,50.0f }, { 0.313f,0.3f }, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.7f);
	wchar_t output6[200];
	swprintf_s(output6, L"武器Lv.%d\n打  %d\n法  %d\n１  %ls\n２  %ls\n３  %ls\n経験値\n累計      %d\n次Lvまで  %d\n", m_playerstatus->GetEuipment(m_swordid2)->GetKariLv(),m_playerstatus->GetEuipment(m_swordid2)->GetKariAtk(), m_playerstatus->GetEuipment(m_swordid2)->GetKariMatk(),
		m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(1), m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(2), m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(3), m_playerstatus->GetEuipment(m_swordid2)->GetKariExp(), m_playerstatus->GetEuipment(m_swordid2)->GetKariNextExp());
	m_font.DrawScreenPos(output6, { 1000.0f,200.0f }, CVector4::White(), { 0.5f,0.5f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
 	wchar_t output[20];
	if (m_playerstatus->GetEuipment(m_swordid2)->GetCost() < m_playerstatus->GetHaveMeseta()) {
		swprintf_s(output, L"強化しますか？\n");
		m_isstrength = true;
	}
	else {
		swprintf_s(output, L"メセタが足りません\n");
		m_isstrength = false;
	}
	m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	m_sprite2.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	wchar_t output9[50];
	swprintf_s(output9, L"所持メセタ  %dM\n強化費用    %dM",m_playerstatus->GetHaveMeseta(), m_playerstatus->GetEuipment(m_swordid2)->GetCost());
	m_font.DrawScreenPos(output9, { 750.0f,392.0f }, CVector4::White(), { 0.5f,0.5f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	m_mesetasprite.DrawScreenPos({ 745.0f,387.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		DirectX::SpriteEffects_None,
		0.8f);
	if (!Pad(0).GetButton(enButtonUp) && !Pad(0).GetButton(enButtonDown) && !Pad(0).GetButton(enButtonA)) {
		m_button = true;
	}
	if (Pad(0).GetButton(enButtonA) && m_button && m_isstrength) {
		m_playerstatus->GetEuipment(m_swordid2)->PlusExp(m_playerstatus->GetEuipment(m_swordid3)->GetMaterialExp());
		m_playerstatus->CutMeseta(m_playerstatus->GetEuipment(m_swordid2)->GetCost());
		m_playerstatus->DeleteEquipment(m_swordid3);
		m_playerstatus->SetStatus();
		m_player->SetStatus();
		CSprite* sp = m_spritelist[m_swordid3];
		m_spritelist.erase(m_spritelist.begin() + m_swordid3);
		delete sp;
		m_swordid1 = m_playerstatus->GetSwordId();
		m_swordid2 = m_swordid1;
		m_swordid3 = m_swordid1;
		m_button = false;
		m_state = enState_Upgrade;
	}
}

void Merchant::Upgrade()
{
	//強化結果
	wchar_t output7[10];
	swprintf_s(output7, L"強化結果\n");
	m_font.DrawScreenPos(output7, { 600.0f,20.0f }, { 200.0f,200.0f,200.0,1.0f }, { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		1.0f
	);
	m_back.DrawScreenPos({ 600.0f,50.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	m_upgradesprite.DrawScreenPos({ 600.0f,50.0f }, { 0.313f,0.3f }, CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.7f);
	wchar_t output6[150];
	swprintf_s(output6, L"武器Lv.%d\n打  %d\n法  %d\n１  %ls\n２  %ls\n３  %ls\n経験値\n累計      %d\n次Lvまで  %d\n", m_playerstatus->GetEuipment(m_swordid2)->GetLv(), m_playerstatus->GetEuipment(m_swordid2)->GetAtk(), m_playerstatus->GetEuipment(m_swordid2)->GetMatk(),
		m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(1), m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(2), m_playerstatus->GetEuipment(m_swordid2)->GetAbilityName(3), m_playerstatus->GetEuipment(m_swordid2)->GetExp(), m_playerstatus->GetEuipment(m_swordid2)->GetNextExp());
	m_font.DrawScreenPos(output6, { 600.0f,200.0f }, CVector4::White(), { 0.5f,0.5f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	wchar_t output[20];
	swprintf_s(output, L"強化に成功しました\n");
	m_font.DrawScreenPos(output, { 300.0f,450.0f }, CVector4::White(), { 0.6f,0.6f },
		CVector2::Zero(),
		0.0f,
		DirectX::SpriteEffects_None,
		0.7f
	);
	m_sprite2.DrawScreenPos({ 290.0f,440.0f }, CVector3::One(), CVector2::Zero(),
		0.0f,
		{ 1.0f, 1.0f, 1.0f, 0.7f },
		DirectX::SpriteEffects_None,
		0.8f);
	if (!Pad(0).GetButton(enButtonUp) && !Pad(0).GetButton(enButtonDown) && !Pad(0).GetButton(enButtonA)) {
		m_button = true;
	}
	if (Pad(0).GetButton(enButtonA) && m_button) {
		m_button = false;
		m_state = enState_Base;
	}
}

void Merchant::PostRender()
{
	if (m_state == enState_Free) {
		m_button = false;
		m_swordid1 = m_playerstatus->GetSwordId();
		m_swordid2 = m_swordid1;
		m_swordid3 = m_swordid1;
		return;
	}
	State state = m_state;
	switch (m_state) {
	case enState_Base:
		Base();
		m_isspriteInit = false;
		break;
	case enState_Material:
		m_isspriteInit = false;
		Material();
		break;
	case enState_Decision:
		Decision();
		break;
	case enState_Upgrade:
		Upgrade();
		m_isspriteInit = false;
		break;
	}
	if (state != m_state) {
		SuicideObj::CSE* se = NewGO<SuicideObj::CSE>(L"Asset/sound/se/kettei.wav");
		se->Play(); //再生(再生が終わると削除されます)
		se->SetVolume(m_sevolume);
		//3D再生
		se->SetPos(m_position);//音の位置
		se->SetDistance(500.0f);//音が聞こえる範囲
		se->Play(true); //第一引数をtru
	}
}

