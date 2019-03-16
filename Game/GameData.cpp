#include "stdafx.h"
#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
	for (int i = 0; i < m_abilitylist.size(); i++) {
		delete m_abilitylist[i];
	}
}

bool GameData::Start()
{
	//コンストラクタを使って各データクラスの生成および、各ステータスの設定をします
	//Weaponクラスのインスタンスを生成
	m_weaponlist.push_back(Weapon(0 , L"もこうスラッシュ"		, 1, 25, 25, 0,  100));
	m_weaponlist.push_back(Weapon(1 , L"ファイアソード"			, 2, 30, 40, 1,  500));
	m_weaponlist.push_back(Weapon(2 , L"アイスソード"			, 2, 30, 40, 2,  500));
	m_weaponlist.push_back(Weapon(3 , L"ウィンドソード"			, 2, 30, 40, 3,  500));
	m_weaponlist.push_back(Weapon(4 , L"グレイトソード"			, 3, 50, 50, 4, 1000));
	m_weaponlist.push_back(Weapon(5 , L"クリスタルエッジ"		, 4, 60, 70, 5, 1500));
	m_weaponlist.push_back(Weapon(6 , L"バトルブレード"         , 5, 80, 80, 6, 2000));
	m_weaponlist.push_back(Weapon(7 , L"バンデッドソード"       , 6,120, 70, 7, 5000));
	m_weaponlist.push_back(Weapon(8 , L"エクスカリバーモルガン" , 7,150,150, 8,10000));
	//Magicクラスのインスタンスを生成
	m_magiclist.push_back(Magic(0 , L"無し"					    , 0.0f,999));
	m_magiclist.push_back(Magic(1 , L"フォイエ"		  	        , 1.7f, 40));
	m_magiclist.push_back(Magic(2 , L"イル・グランツ"			, 1.9f, 40));
	m_magiclist.push_back(Magic(3 , L"ザンバース"				, 1.6f, 40));
	m_magiclist.push_back(Magic(4 , L"シフタ"					, 0.0f, 50));
	m_magiclist.push_back(Magic(5 , L"マジックスフィア"		    , 2.0f, 60));
	m_magiclist.push_back(Magic(6 , L"レスタ"                   , 0.6f, 40));
	m_magiclist.push_back(Magic(7 , L"覇王斬"                   , 2.0f, 60));
	m_magiclist.push_back(Magic(8 , L"約束された勝利の剣"       , 2.3f, 60));
	//Materialクラスのインスタンスを生成
	m_materiallist.push_back(Material(L"木"					, 1));
	m_materiallist.push_back(Material(L"石"					, 2));
	m_materiallist.push_back(Material(L"レンガ"				, 3));
	//アビリティクラスのインスタンスを作成
	m_abilitylist.push_back(new Ability(1 , L"HPアップ1"        , 1, 6,   0,  0, 10,  0));
	m_abilitylist.push_back(new Ability(2 , L"HPアップ2"        , 1, 4,   0,  0, 20,  0));
	m_abilitylist.push_back(new Ability(3 , L"HPアップ3"        , 1, 2,   0,  0, 30,  0));
	m_abilitylist.push_back(new Ability(4 , L"PPアップ1"        , 2, 6,   0,  0,  0, 10));
	m_abilitylist.push_back(new Ability(5 , L"PPアップ2"        , 2, 4,   0,  0,  0, 20));
	m_abilitylist.push_back(new Ability(6 , L"PPアップ3"        , 2, 2,   0,  0,  0, 30));
	m_abilitylist.push_back(new Ability(7 , L"パワー1"          , 3, 6,  10,  0,  0,  0));
	m_abilitylist.push_back(new Ability(8 , L"パワー2"          , 3, 4,  15,  0,  0,  0));
	m_abilitylist.push_back(new Ability(9 , L"パワー3"          , 3, 2,  20,  0,  0,  0));
	m_abilitylist.push_back(new Ability(10, L"テクニック1"      , 4, 6,   0,  5,  0,  0));
	m_abilitylist.push_back(new Ability(11, L"テクニック2"      , 4, 4,   0, 10,  0,  0));
	m_abilitylist.push_back(new Ability(12, L"テクニック3"      , 4, 2,   0, 15,  0,  0));
	m_abilitylist.push_back(new Ability(13, L"オール1"          , 5, 3,   5,  5,  5,  5));
	m_abilitylist.push_back(new Ability(14, L"オール2"          , 5, 2,  10, 10, 10, 10));
	m_abilitylist.push_back(new Ability(15, L"オール3"          , 5, 1,  15, 15, 15, 15));
	m_abilitylist.push_back(new Ability(16, L"アーチャー"       , 6, 2,  10, 20, 10, 20));
	m_abilitylist.push_back(new Ability(17, L"ランサー"         , 6, 2,  30,  0, 30,  0));
	m_abilitylist.push_back(new Ability(18, L"セイバー"         , 6, 1,  20, 15, 20, 15));
	for (int i = 0; i < m_abilitylist.size(); i++) {
		m_totalabilityweight += m_abilitylist[i]->GetWeight();
		if (m_abilitygroupnumber != m_abilitylist[i]->GetGroup()) {
			m_abilitygroupnumber++;
			m_totalabilitygroupweightlist.push_back(m_abilitylist[i]->GetWeight());
		}
		else {
			m_totalabilitygroupweightlist[m_abilitygroupnumber - 1] += m_abilitylist[i]->GetWeight();
		}
	}
	//ファイルパスを設定
	m_filepathlist.push_back(L"Resource/sprite/number00.dds");
	m_filepathlist.push_back(L"Resource/sprite/number01.dds");
	m_filepathlist.push_back(L"Resource/sprite/number02.dds");
	m_filepathlist.push_back(L"Resource/sprite/number03.dds");
	m_filepathlist.push_back(L"Resource/sprite/number04.dds");
	m_filepathlist.push_back(L"Resource/sprite/number05.dds");
	m_filepathlist.push_back(L"Resource/sprite/number06.dds");
	m_filepathlist.push_back(L"Resource/sprite/number07.dds");
	m_filepathlist.push_back(L"Resource/sprite/number08.dds");
	m_filepathlist.push_back(L"Resource/sprite/number09.dds");
	//数字の画像を読み込む
	for (int i = 0; i < m_filepathlist.size(); i++) {
		CSprite* sprite = new CSprite;
		sprite->Init(m_filepathlist[i]);
		m_numberspritelist.push_back(sprite);
	}
	return true;
}

void GameData::Update()
{

}
