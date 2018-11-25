#include "stdafx.h"
#include "Magic.h"


Magic::Magic(const int& id, const std::string& name, const float& damageRate, const int& ppCost)
	:m_id(id),m_name(name),m_damageRate(damageRate),m_ppCost(ppCost)
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
