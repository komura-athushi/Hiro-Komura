#pragma once
class Weapon;
class Enemy;
class Magic;
class GameData:public IGameObject
{
public:
	GameData();
	~GameData();
	bool Start();
	void Update();
	
private:
	static Weapon* m_weapons;
	static Enemy* m_enemies;
	static Magic* m_magics;
};

