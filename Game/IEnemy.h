#pragma once
class IEnemy : public IGameObject
{
public:
	IEnemy();
	~IEnemy();
	virtual void Attack()=0;
};

