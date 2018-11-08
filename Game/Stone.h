#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//TDN�΂ł�
class Stone:public IGameObject
{
public:
	Stone();
	~Stone();
	bool Start();
	void Update();
	//���W���Z�b�g
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:        
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = {0.0f,0.0f,0.0f};                     //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
};

