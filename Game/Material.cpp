#include "stdafx.h"
#include "Material.h"
const int Material::m_raritynumber[Material::m_HighestRarity] = { 1,1,1};
Material::Material(const wchar_t* name,const int rarity)
	:m_name(name),m_rarity(rarity)
{
}
Material::Material()
{
}


Material::~Material()
{
}
