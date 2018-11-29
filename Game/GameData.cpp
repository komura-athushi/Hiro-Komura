#include "stdafx.h"
#include "GameData.h"
#include "Enemy.h"
#include "Magic.h"
GameData::GameData()
{
}


GameData::~GameData()
{
}

bool GameData::Start()
{
	m_weaponlist.push_back(Weapon(0 , L"ソード"					, 0, 10, 20, 0));
	m_weaponlist.push_back(Weapon(1 , L"ファイアソード"			, 1, 30, 40, 1));
	m_weaponlist.push_back(Weapon(2 , L"アイスソード"			, 1, 30, 40, 2));
	m_weaponlist.push_back(Weapon(3 , L"ウィンドソード"			, 1, 30, 40, 3));
	m_weaponlist.push_back(Weapon(4 , L"グレイトソード"			, 2, 50, 50, 4));
	m_weaponlist.push_back(Weapon(5 , L"ブルーライトソード"		, 3, 60, 70, 5));
	
	m_magics = new Magic[6]{
		Magic(0 ,"斬撃"                  ,1.5f ,30),
		Magic(1 ,"ファイアボール"        ,1.7f ,40),
		Magic(2 ,"アイスボール"          ,1.9f ,40),
		Magic(3 ,"ウィンド"              ,1.6f ,40),
		Magic(4 ,"超斬撃"                ,2.1f ,50),
		Magic(5 ,"トゥインクルスター"    ,2.3f ,60)
	};
	return true;
}

void GameData::Update()
{

}