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
	m_weaponlist.push_back(Weapon(0 , L"もこうスラッシュ"		, 1, 10, 20, 0,  100));
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
	m_magiclist.push_back(Magic(5 , L"マジックスフィア"		    , 2.3f, 60));
	m_magiclist.push_back(Magic(6 , L"マジックスフィア"         , 2.3f, 60));
	m_magiclist.push_back(Magic(7 , L"マジックスフィア"         , 2.3f, 60));
	m_magiclist.push_back(Magic(8 , L"マジックスフィア"         , 2.3f, 60));
	//Materialクラスのインスタンスを生成
	m_materiallist.push_back(Material(L"木"					, 1));
	m_materiallist.push_back(Material(L"石"					, 2));
	m_materiallist.push_back(Material(L"レンガ"				, 3));

	return true;
}

void GameData::Update()
{

}
