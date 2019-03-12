#include "stdafx.h"
#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
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
	m_abilitylist.push_back(Ability(1 , L"HPアップ1"        ,   0,  0, 10,  0));
	m_abilitylist.push_back(Ability(2 , L"パワー1"          ,  10,  0,  0,  0));
	m_abilitylist.push_back(Ability(3 , L"テクニック1"      ,   0, 10,  0,  0));
	m_abilitylist.push_back(Ability(4 , L"PPアップ1"        ,   0,  0,  0, 10));
	m_abilitylist.push_back(Ability(5 , L"HPアップ2"        ,   0,  0, 30,  0));
	m_abilitylist.push_back(Ability(6 , L"パワー2"          ,  30,  0,  0,  0));
	m_abilitylist.push_back(Ability(7 , L"テクニック2"      ,   0, 30,  0,  0));
	m_abilitylist.push_back(Ability(8 , L"PPアップ2"        ,   0,  0,  0, 30));
	m_abilitylist.push_back(Ability(9 , L"HPアップ3"        ,   0,  0, 50,  0));
	m_abilitylist.push_back(Ability(10, L"パワー3"          ,  50,  0,  0,  0));
	m_abilitylist.push_back(Ability(11, L"テクニック3"      ,   0, 50,  0,  0));
	m_abilitylist.push_back(Ability(12, L"PPアップ3"        ,   0,  0,  0, 50));
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
	for (int i = 0; i < 10; i++) {
		CSprite* sprite = new CSprite;
		sprite->Init(m_filepathlist[i]);
		m_numberspritelist.push_back(sprite);
	}
	return true;
}

void GameData::Update()
{

}
