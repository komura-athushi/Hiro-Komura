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
	//�R���X�g���N�^���g���Ċe�f�[�^�N���X�̐�������сA�e�X�e�[�^�X�̐ݒ�����܂�
	//Weapon�N���X�̃C���X�^���X�𐶐�
	m_weaponlist.push_back(Weapon(0 , L"�m�[�r�X�\�[�h"		    , 1, 25, 40, 6,  100));
	m_weaponlist.push_back(Weapon(1 , L"�t�@�C�A�\�[�h"			, 2, 45, 80, 1,  500));
	m_weaponlist.push_back(Weapon(2 , L"�A�C�X�\�[�h"			, 2, 45, 80, 2,  500));
	m_weaponlist.push_back(Weapon(3 , L"�E�B���h�\�[�h"			, 2, 45, 80, 3,  500));
	m_weaponlist.push_back(Weapon(4 , L"�O���C�g�\�[�h"			, 3, 60,100, 4, 1000));
	m_weaponlist.push_back(Weapon(5 , L"�N���X�^���G�b�W"		, 4, 80,120, 5, 1500));
	m_weaponlist.push_back(Weapon(6 , L"�o�g���u���[�h"         , 5, 80, 80, 6, 2000));
	m_weaponlist.push_back(Weapon(7 , L"�o���f�b�h�\�[�h"       , 6,120, 70, 7, 5000));
	m_weaponlist.push_back(Weapon(8 , L"�G�N�X�J���o�[�����K��" , 7,150,150, 8,10000));
	//Magic�N���X�̃C���X�^���X�𐶐�
	m_magiclist.push_back(Magic(0 , L"����"					    , 0.0f,999));
	m_magiclist.push_back(Magic(1 , L"�t���C���A���["		  	, 1.2f, 30));
	m_magiclist.push_back(Magic(2 , L"�t���[�Y�V���b�g"			, 1.8f, 30));
	m_magiclist.push_back(Magic(3 , L"�G�A���o�[�X�g"			, 1.0f, 30));
	m_magiclist.push_back(Magic(4 , L"�V�t�^"					, 0.0f, 30));
	m_magiclist.push_back(Magic(5 , L"�}�W�b�N�X�t�B�A"		    , 2.0f, 40));
	m_magiclist.push_back(Magic(6 , L"�q�[��"                   , 0.5f, 30));
	m_magiclist.push_back(Magic(7 , L"�e���a"                   , 2.0f, 60));
	m_magiclist.push_back(Magic(8 , L"�񑩂��ꂽ�����̌�"       , 2.3f, 60));
	//Material�N���X�̃C���X�^���X�𐶐�
	m_materiallist.push_back(Material(L"��"					, 1));
	m_materiallist.push_back(Material(L"��"					, 2));
	m_materiallist.push_back(Material(L"�����K"				, 3));
	//�A�r���e�B�N���X�̃C���X�^���X���쐬
	m_abilitylist.push_back(new Ability(1 , L"HP�A�b�v1"        , 1, 6,   0,  0, 10,  0));
	m_abilitylist.push_back(new Ability(2 , L"HP�A�b�v2"        , 1, 4,   0,  0, 20,  0));
	m_abilitylist.push_back(new Ability(3 , L"HP�A�b�v3"        , 1, 2,   0,  0, 30,  0));
	m_abilitylist.push_back(new Ability(4 , L"PP�A�b�v1"        , 2, 6,   0,  0,  0, 10));
	m_abilitylist.push_back(new Ability(5 , L"PP�A�b�v2"        , 2, 4,   0,  0,  0, 20));
	m_abilitylist.push_back(new Ability(6 , L"PP�A�b�v3"        , 2, 2,   0,  0,  0, 30));
	m_abilitylist.push_back(new Ability(7 , L"�p���[1"          , 3, 6,  10,  0,  0,  0));
	m_abilitylist.push_back(new Ability(8 , L"�p���[2"          , 3, 4,  15,  0,  0,  0));
	m_abilitylist.push_back(new Ability(9 , L"�p���[3"          , 3, 2,  20,  0,  0,  0));
	m_abilitylist.push_back(new Ability(10, L"�e�N�j�b�N1"      , 4, 6,   0,  5,  0,  0));
	m_abilitylist.push_back(new Ability(11, L"�e�N�j�b�N2"      , 4, 4,   0, 10,  0,  0));
	m_abilitylist.push_back(new Ability(12, L"�e�N�j�b�N3"      , 4, 2,   0, 15,  0,  0));
	m_abilitylist.push_back(new Ability(13, L"�I�[��1"          , 5, 3,   5,  5,  5,  5));
	m_abilitylist.push_back(new Ability(14, L"�I�[��2"          , 5, 2,  10, 10, 10, 10));
	m_abilitylist.push_back(new Ability(15, L"�I�[��3"          , 5, 1,  15, 15, 15, 15));
	m_abilitylist.push_back(new Ability(16, L"�o�[�T�[�J�["     , 6, 1,  60,  0,-40,  0));
	m_abilitylist.push_back(new Ability(17, L"�L���X�^�["       , 6, 1,   0, 40,-40,  0));
	m_abilitylist.push_back(new Ability(18, L"�Z�C�o�["         , 6, 1,  25,  0, 25,  0));
	m_abilitylist.push_back(new Ability(19, L"�e�N�^�["         , 6, 1,   0, 25, 25,  0));
	//����\�͂̐F�X�Ȓl���v�Z
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
	//�t�@�C���p�X��ݒ�
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
	//�����̉摜��ǂݍ���
	for (int i = 0; i < m_filepathlist.size(); i++) {
		CSprite* sprite = new CSprite;
		sprite->Init(m_filepathlist[i]);
		m_numberspritelist.push_back(sprite);
	}
	//�����Lv�������ɕK�v�ȑf�ސ���ݒ�
	m_weaponreleaserequirednumber.push_back(new MaterialNumber{ 1, 1, 15 });
	m_weaponreleaserequirednumber.push_back(new MaterialNumber{ 1, 2, 10 });
	m_weaponreleaserequirednumber.push_back(new MaterialNumber{ 2, 2, 15 });
	m_weaponreleaserequirednumber.push_back(new MaterialNumber{ 2, 3, 10 });
	m_weaponreleaserequirednumber.push_back(new MaterialNumber{ 3, 3, 25 });
	//��L�̗l�X�Ȓl���v�Z
	for (int i = 0; i < m_weaponreleaserequirednumber.size(); i++) {
		if (m_weaponlimitstagematerialtype.size() != m_weaponreleaserequirednumber[i]->s_llimitstage) {
			m_weaponlimitstagematerialtype.push_back(1);
		}
		else {
			m_weaponlimitstagematerialtype[m_weaponreleaserequirednumber[i]->s_llimitstage - 1] += 1;
		}
		if (m_weaponlimit < m_weaponreleaserequirednumber[i]->s_llimitstage + 1) {
			m_weaponlimit = m_weaponreleaserequirednumber[i]->s_llimitstage + 1;
		}
	}
	return true;
}

void GameData::Update()
{

}

//����Lv�̉���i�K��i�߂�邩�ǂ���
bool GameData::GetisUpWeaponLimitStage() const
{
	if (m_weaponlimit == m_weaponlimitstage) {
		return false;
	}
	else {
		return true;
	}
}
