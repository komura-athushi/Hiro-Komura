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
	m_weaponlist.push_back(Weapon(0 , L"�\�[�h"					, 0, 10, 20, 0));
	m_weaponlist.push_back(Weapon(1 , L"�t�@�C�A�\�[�h"			, 1, 30, 40, 1));
	m_weaponlist.push_back(Weapon(2 , L"�A�C�X�\�[�h"			, 1, 30, 40, 2));
	m_weaponlist.push_back(Weapon(3 , L"�E�B���h�\�[�h"			, 1, 30, 40, 3));
	m_weaponlist.push_back(Weapon(4 , L"�O���C�g�\�[�h"			, 2, 50, 50, 4));
	m_weaponlist.push_back(Weapon(5 , L"�u���[���C�g�\�[�h"		, 3, 60, 70, 5));
	
	m_magics = new Magic[6]{
		Magic(0 ,"�a��"                  ,1.5f ,30),
		Magic(1 ,"�t�@�C�A�{�[��"        ,1.7f ,40),
		Magic(2 ,"�A�C�X�{�[��"          ,1.9f ,40),
		Magic(3 ,"�E�B���h"              ,1.6f ,40),
		Magic(4 ,"���a��"                ,2.1f ,50),
		Magic(5 ,"�g�D�C���N���X�^�["    ,2.3f ,60)
	};
	return true;
}

void GameData::Update()
{

}