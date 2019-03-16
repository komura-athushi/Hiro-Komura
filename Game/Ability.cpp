#include "stdafx.h"
#include "Ability.h"


Ability::Ability(const int& id, const wchar_t* name, const int& group, const int& weight, const int& power, const int& mpower, const int& hp, const int& pp)
	:m_id(id), m_abilityname(name), m_group(group), m_weight(weight), m_power(power), m_mpower(mpower), m_hp(hp), m_pp(pp)
{

}

Ability::Ability(const int& power, const int& mpower, const int& hp, const int& pp)
	: m_power(power), m_mpower(mpower), m_hp(hp), m_pp(pp)
{

}

Ability::Ability(const Ability& ab)
	: m_id(ab.m_id), m_abilityname(ab.m_abilityname), m_power(ab.m_power), m_mpower(ab.m_mpower), m_hp(ab.m_hp), m_pp(ab.m_pp)
{

}

Ability::~Ability()
{
}
