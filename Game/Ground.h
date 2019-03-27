#pragma once
#include "DemolisherWeapon/physics/PhysicsStaticObject.h"
//�X�e�[�W�̏��Ƃ��ǂƂ��𐶐�����N���X�ł�
class Ground : public IGameObject
{
public:
	Ground();
	~Ground();
	bool Start() override;
	void Update() override;
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�X�e�[�W�̏���ݒ�
	void SetStage(const int& stage)
	{
		m_stage = stage;
	}
	//��]��ݒ�
	void SetRot(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	//�傫����ݒ�
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	GameObj::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	GameObj::CSkinModelRender* m_skinModelRender2 = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position;                                        //���W
	CVector3 m_scale = CVector3::One();                         //�傫��
	CQuaternion m_rotation = CQuaternion::Identity();           //�N�I���e�[�V����
	PhysicsStaticObject m_staticobject;                         //�ÓI�I�u�W�F�N�g
	PhysicsStaticObject m_staticobject2;                        //�ÓI�I�u�W�F�N�g
	int m_stage = 0;											//�X�e�[�W���
};																

