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
	Weapon* m_weapons;
    Enemy* m_enemies;
	Magic* m_magics;
};

