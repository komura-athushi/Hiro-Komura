#include "stdafx.h"
#include "GameData.h"
#include "Enemy.h"

GameData::GameData()
{
}


GameData::~GameData()
{
}

bool GameData::Start()
{
<<<<<<< HEAD
	m_weapons = new Weapon[6]{
		Weapon(0 ,"ソード"                ,0  ,10 ,20 ,0),
		Weapon(1 ,"ファイアソード"        ,1  ,30 ,40 ,1),
		Weapon(2 ,"アイスソード"          ,1  ,30 ,40 ,2),
		Weapon(3 ,"ウィンドソード"        ,1  ,30 ,40 ,3),
		Weapon(4 ,"グレイトソード"        ,2  ,50 ,50 ,4),
		Weapon(5 ,"ブルーライトソード"    ,3  ,60 ,70 ,5)
	};
	/*m_enemies = new Enemy[2]{
		Enemy(0 ,"Bone Soldier"          ,50  ,20 ,20  ,new float[4]{0,10,0,0 }),
	    Enemy(1, "ボス"                  ,500 ,40 ,400 ,new float[4]{ 0,0,0,0})
	};*/
	m_magics = new Magic[6]{
		Magic(0 ,"斬撃"                  ,1.5f ,30),
		Magic(1 ,"ファイアボール"        ,1.7f ,40),
		Magic(2 ,"アイスボール"          ,1.9f ,40),
		Magic(3 ,"ウィンド"              ,1.6f ,40),
		Magic(4 ,"超斬撃"                ,2.1f ,50),
		Magic(5 ,"トゥインクルスター"    ,2.3f ,60)
	};
=======
	//Weaponクラスのインスタンスを生成
	m_weaponlist.push_back(Weapon(0 , L"ソード"				    , 0, 10, 20, 0));
	m_weaponlist.push_back(Weapon(1 , L"ファイアソード"			, 1, 30, 40, 1));
	m_weaponlist.push_back(Weapon(2 , L"アイスソード"			, 1, 30, 40, 2));
	m_weaponlist.push_back(Weapon(3 , L"ウィンドソード"			, 1, 30, 40, 3));
	m_weaponlist.push_back(Weapon(4 , L"グレイトソード"			, 2, 50, 50, 4));
	m_weaponlist.push_back(Weapon(5 , L"クリスタルエッジ"		, 3, 60, 70, 5));
	//Magicクラスのインスタンスを生成
	m_magiclist.push_back(Magic(0 , L"無し"					    , 0.0f, 30));
	m_magiclist.push_back(Magic(1 , L"フォイエ"		  	        , 1.7f, 40));
	m_magiclist.push_back(Magic(2 , L"イル・グランツ"			, 1.9f, 40));
	m_magiclist.push_back(Magic(3 , L"ザンバース"				, 1.6f, 40));
	m_magiclist.push_back(Magic(4 , L"シフタ"					, 0.0f, 50));
	m_magiclist.push_back(Magic(5 , L"マジックスフィア"		    , 2.3f, 60));
	//Materialクラスのインスタンスを生成
	m_materiallist.push_back(Material(L"藁"					, 0));
	m_materiallist.push_back(Material(L"土"					, 0));
	m_materiallist.push_back(Material(L"石材"				, 1));
>>>>>>> 4621d4808865101770bd6c9e39b60f3ff6afe2b0
	return true;
}

void GameData::Update()
{

}