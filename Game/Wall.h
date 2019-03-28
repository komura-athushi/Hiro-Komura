#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
class Boss;
//��
class Wall:public IGameObject
{
public:
	Wall();
	~Wall();
	bool Start() override;
	void Update() override;
	//���W���Z�b�g
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = { 0.0f,0.0f,0.0f };                   //���W
	CVector3 m_scale = { 1.0f,1.0f,1.0f };                      //�傫��
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	bool m_iscreatstaticobject = false;							//�ÓI�I�u�W�F�N�g�𐶐��������ǂ���			
	Boss* m_boss = nullptr;										//�{�X
};

