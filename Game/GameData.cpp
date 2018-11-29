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
	//Weapon�N���X�̃C���X�^���X�𐶐�
	m_weaponlist.push_back(Weapon(0 , L"�\�[�h"					, 0, 10, 20, 0));
	m_weaponlist.push_back(Weapon(1 , L"�t�@�C�A�\�[�h"			, 1, 30, 40, 1));
	m_weaponlist.push_back(Weapon(2 , L"�A�C�X�\�[�h"			, 1, 30, 40, 2));
	m_weaponlist.push_back(Weapon(3 , L"�E�B���h�\�[�h"			, 1, 30, 40, 3));
	m_weaponlist.push_back(Weapon(4 , L"�O���C�g�\�[�h"			, 2, 50, 50, 4));
	m_weaponlist.push_back(Weapon(5 , L"�u���[���C�g�\�[�h"		, 3, 60, 70, 5));
	//Magic�N���X�̃C���X�^���X�𐶐�
	m_magiclist.push_back(Magic(0 , L"�a��"						, 1.5f, 30));
	m_magiclist.push_back(Magic(1 , L"�t�@�C�A�{�[��"			, 1.7f, 40));
	m_magiclist.push_back(Magic(2 , L"�A�C�X�{�[��"				, 1.9f, 40));
	m_magiclist.push_back(Magic(3 , L"�E�B���h"					, 1.6f, 40));
	m_magiclist.push_back(Magic(4 , L"���a��"					, 2.1f, 50));
	m_magiclist.push_back(Magic(5 , L"�g�D�C���N���X�^�["		, 2.3f, 60));
	return true;
}

void GameData::Update()
{

}