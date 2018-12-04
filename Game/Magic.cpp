#include "stdafx.h"
#include "Magic.h"


Magic::Magic(const int& id, const wchar_t* name, const float& damageRate, const int& ppCost)
	:m_id(id),m_name(name),m_damageRate(damageRate),m_ppCost(ppCost)
{
}

Magic::Magic(const Magic& magic) : m_id(magic.m_id), m_name(magic.m_name), m_damageRate(magic.m_damageRate), m_ppCost(magic.m_ppCost)
{

}

Magic::~Magic()
{
}

bool Magic::Start()
{
	return true;
}

void Magic::Update()
{

}
