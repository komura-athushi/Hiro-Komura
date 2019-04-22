#include "stdafx.h"
#include "Equipment.h"
#include "GameData.h"
const float Equipment::m_multiply = 1.15f;
const float Equipment::m_costmultiply = 1.2f;
Equipment::Equipment(const int& number):m_SwordId(number)
{
	//GameData�N���X���o�R���Ċe�X�e�[�^�X���擾����
	m_gamedata = &GameData::GetInstance();
	//���ꂼ��̃X�e�[�^�X��ݒ�
	SetWeaponStatus();
	SetMagicStatus();
	//�t�^���ꂽ�A�r���e�B�̃O���[�v���L��j���Ă���
	std::vector <int> abilitygroupnumberlist;
	//�t�^���ꂽ�A�r���e�B�̐�
	int abilitynumber = 0;
	//�S�A�r���e�B�̃E�F�C�g���g�[�^��
	int totalabilityweight = m_gamedata->GetTotalWeight();
	if (m_SwordId != 0) {
		//�ō�3��܂œ���\�͂�t�^���܂�
		for (int i = 0; i < m_slotlimitnumber; i++) {
			int rn = rand() % 100 + 1;
			//�K��̒l��藐�����傫����Γ���\�͂�t�^���܂��A2�A3��ڂ͊m�����Ⴍ�Ȃ�܂�
			if (rn < m_probability[abilitynumber]) {
				//�E�F�C�g�l�����߂܂�
				int rn2 = rand() % totalabilityweight;
				//����\�͂����ɕt�^���Ă��邩���Ă��Ȃ����ŏ����𕪂��܂�
				if (m_ishaveability) {
					int i = 0;
					while (true) {
						bool isgroup = false;
						for (int j = 0; j < abilitynumber; j++) {
							//���Ɏ擾���Ă������\�͂̃O���[�v�͔�����悤�ɂ��܂�
							if (abilitygroupnumberlist[j] == m_gamedata->GetAbility(i)->GetGroup()) {
								isgroup = true;
								i++;
								break;
							}
						}
						if (!isgroup) {
							//�E�F�C�g�l���e����\�͂̃E�F�C�g�l���������Z���܂�
							if ((rn2 -= m_gamedata->GetAbility(i)->GetWeight()) > 0) {
								i++;
							}
							else {
								//�E�F�C�g�l��0�ȉ��ɂȂ�΂��̎��̓���\�͂�t�^���܂�
								m_abilitylist.push_back(m_gamedata->GetAbility(i));
								abilitygroupnumberlist.push_back(m_gamedata->GetAbility(i)->GetGroup());
								abilitynumber++;
								totalabilityweight -= m_gamedata->GetTotalGroupWeight(m_gamedata->GetAbility(i)->GetGroup());
								m_ishaveability = true;
								break;
							}
						}
					}
				}
				else {
					int i = 0;
					while (true) {
						//�E�F�C�g�l���e����\�͂̃E�F�C�g�l���������Z���܂�
						if ((rn2 -= m_gamedata->GetAbility(i)->GetWeight()) > 0) {
							i++;
						}
						else {
							//�E�F�C�g�l��0�ȉ��ɂȂ�΂��̎��̓���\�͂�t�^���܂�
							m_abilitylist.push_back(m_gamedata->GetAbility(i));
							abilitygroupnumberlist.push_back(m_gamedata->GetAbility(i)->GetGroup());
							abilitynumber++;
							totalabilityweight -= m_gamedata->GetTotalGroupWeight(m_gamedata->GetAbility(i)->GetGroup());
							//�n�߂ē���\�͂�t�^�����ꍇ�A����\�͎擾�t���O���I���ɂ��܂�
							m_ishaveability = true;
							break;
						}
					}
				}
			}
			//����\�͕t�^�Ɏ��s�����ꍇ�A���̎��_�Ń��[�v�𔲂��܂�
			else {
				break;
			}
		}
	}
	//���x���A�b�v�ɕK�v�Ȍo���l��ݒ肵�܂�
	m_NextExp = pow(2.0f, m_Rarity) * m_weaponextend * (m_weaponextend + 9) / 2;
	m_LevelExp = m_NextExp;
	int attack = 0, mattack = 0, hp = 0, pp = 0;
	//�t�^���ꂽ����\�͂̒l���܂Ƃ߂�Ability�N���X�𐶐����܂�
	if (m_ishaveability) {
		for (int i = 0; i < m_abilitylist.size(); i++) {
			attack += m_abilitylist[i]->GetPower();
			mattack += m_abilitylist[i]->GetMpower();
			hp += m_abilitylist[i]->GetHP();
			pp += m_abilitylist[i]->GetPP();
		}
	}
	m_ability = new Ability(attack, mattack, hp, pp);
}

Equipment::~Equipment()
{
	delete m_ability;
}


void Equipment::SetWeaponStatus()
{
	//GameData�N���X����Y���̔ԍ��̕���̃f�[�^���擾���܂�
	if (m_weaponextend == 1) {
		m_weapon = m_gamedata->GetWeapon(m_SwordId);
		m_SwordMattack = m_weapon->GetMatk();
		m_protSwordMattack = m_SwordMattack;
		m_Mattack = m_SwordMattack;
		m_SwordAttack = m_weapon->GetAtk();
		m_protSwordAattack = m_SwordAttack;
		m_Attack = m_SwordAttack;
		m_MagicId = m_weapon->GetMagicId();
		m_Rarity = m_weapon->GetRarity();
		m_SwordName = m_weapon->GetName();
		m_meseta = m_weapon->GetMeseta();
	}
	m_Attack = m_SwordAttack;
	m_Mattack = m_SwordMattack;
}

void Equipment::SetMagicStatus()
{
	//GameData�N���X����Y���̔ԍ��̖��@�̃f�[�^���擾���܂�
	m_magic = m_gamedata->GetMagic(m_MagicId);
	m_MagicName = m_magic->GetName();
	m_DamageRate = m_magic->GetDamageRate();
	m_PPCost = m_magic->GetPPCost();
}

const wchar_t* Equipment::GetAbilityName(const int& number)
{
	//����\�͂��t�^����Ă��Ȃ��ꍇ�A"����"�ƕ\�L���܂�
	if (!m_ishaveability) {
		return L"����";
	}
	else {
		if (number <= m_abilitylist.size()) {
			return m_abilitylist[number - 1]->GetName();
		}
		else {
			return L"����";
		}
	}
}

void Equipment::PlusExp(const int& exp)
{
	int ep = exp;
	//�o���l�����Z
	m_Exp += ep;
	//���x���A�b�v�ɕK�v�ȗ݌v�o���l���v���C���[�̗݌v�o���l���傫���Ȃ�܂Ń��[�v
	while (m_LevelExp <= m_Exp) {
		ep -= m_NextExp;
		m_weaponextend += 1;
		m_NextExp = pow(2.0f, m_Rarity) * m_weaponextend * (m_weaponextend + 9) / 2;
		m_LevelExp += m_NextExp;
		m_SwordAttack = m_protSwordAattack * (1 + (m_weaponextend + 4) * (m_weaponextend - 1) * 0.01) + 5 * (m_weaponextend - 1);
		m_SwordMattack = m_protSwordMattack * (1 + (m_weaponextend + 4) * (m_weaponextend - 1) * 0.01) + 5 * (m_weaponextend - 1);
		SetWeaponStatus();
		if (m_gamedata->GetWeaponLimitLv() == m_weaponextend) {
			return;
		}
	}
	m_NextExp -= ep;
}

void Equipment::KariPlusExp(const int& exp)
{
	m_kariExp = m_Exp;
	m_kariNextExp = m_NextExp;                              
	m_kariLevelExp = m_LevelExp;                          
	m_kariSwordMattack = m_SwordMattack;                          
	m_kariSwordAttack = m_SwordAttack;                        
	m_kariweaponextend = m_weaponextend;
	m_kariAttack = m_kariSwordAttack;
	m_kariMattack = m_kariSwordMattack;
	int ep = exp;
	//�o���l�����Z
	m_kariExp += ep;
	//���x���A�b�v�ɕK�v�ȗ݌v�o���l���v���C���[�̗݌v�o���l���傫���Ȃ�܂Ń��[�v
	while (m_kariLevelExp <= m_kariExp) {
		ep -= m_kariNextExp;
		m_kariweaponextend += 1;
		m_kariNextExp = pow(2.0f, m_Rarity) * m_kariweaponextend * (m_kariweaponextend + 9) / 2;
		m_kariLevelExp += m_kariNextExp;
		m_kariSwordAttack = m_protSwordAattack * (1 + (m_kariweaponextend + 4) * (m_kariweaponextend - 1) * 0.01) + 5 * (m_kariweaponextend - 1);
		m_kariSwordMattack = m_protSwordMattack * (1 + (m_kariweaponextend + 4) * (m_kariweaponextend - 1) * 0.01) + 5 * (m_kariweaponextend - 1);
		m_kariAttack = m_kariSwordAttack;
		m_kariMattack = m_kariSwordMattack;
		if (m_gamedata->GetWeaponLimitLv() == m_kariweaponextend) {
			return;
		}
	}
	m_kariNextExp -= ep;
}

int Equipment::GetMaterialExp(const int& id) const
{
	//��������\��̕���Ǝ��g��������ނ̕��킾�����ꍇ�A�f�ނƂ��Ă̌o���l���{�ɂ��܂�
	if(m_SwordId == id) {
		return pow(2.0f, m_Rarity) * (20 + 5 * m_weaponextend) * 2.0f;
	}
	else {
		return pow(2.0f, m_Rarity) * (20 + 5 * m_weaponextend);
	}
}