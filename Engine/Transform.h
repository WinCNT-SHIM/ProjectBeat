#pragma once
#include "Component.h"
#include "CBase.h"
#include <d2d1.h>

class GameObject;

class Transform : public Component
{
public:
	Transform(GameObject* _GameObject);
	virtual ~Transform();

	Transform* m_Parents;
public:
	//������ǥ ���� �Լ�
	void SetLocalTranslateVector(float x, float y);
	void SetLocalTranslateVector(Vector2D _vector);
	void AddLocalTranslateVector(float x, float y);
	
	void SetLocalRotateVector(float x, float y);
	void SetLocalRotateVector(Vector2D _vector);
    /// <summary>
    /// ������ ȸ���� �Է��ϴ� �Լ� �߰�
	/// 2022.02.11 �ɽ¼�
    /// </summary>
    void SetLocalRotateVector(float Degree);

	void SetLocalScaleVector(float x, float y);
	void SetLocalScaleVector(Vector2D _vector);

	void SetWorldTranslateVector(Vector2D _vector);
	void SetWorldRotateVector(Vector2D _vector);
	void SetWorldScaleVector(Vector2D _vector);


	//������ǥ �޾ƿ���
	Vector2D& GetLocalTranslate() { return m_TranslateVector; }
	Vector2D& GetLocalRotate() { return m_RotateVector; }
	Vector2D& GetLocalScale() { return m_ScaleVector; }

	//������ǥ �޾ƿ���
	Vector2D& GetWorldTranslate() { return m_WorldTranslateVector; }
	Vector2D& GetWorldRotate() { return m_WorldRotateVector; }
	Vector2D& GetWorldScale() { return m_WorldScaleVector; }

	D2D1_MATRIX_3X2_F GetWorldMt() { return m_WorldMt; }

	//�ǹ��� ������
	Vector2D m_Pivot;

	void SetTransform(Vector2D _pos = Vector2D(0, 0), Vector2D _Rotate = Vector2D(1, 0), Vector2D _Scale = Vector2D(1, 1), Vector2D _Pivot = Vector2D(0, 0));

	void SetTransformParent(Transform* _Parents); // ���������� �θ� ����
	virtual void Update();
public:
	//����� translate, rotate, scale�ϳ��� ��ȯ
	static D2D1_MATRIX_3X2_F MakeTranslateMt(Vector2D m_TranslateVector);
	static D2D1_MATRIX_3X2_F MakeRotateMt(Vector2D m_RotateVector);
	static D2D1_MATRIX_3X2_F MakeScaleMt(Vector2D m_ScaleVector);

	//����� translate, rotate, scale �θ���� ���ļ� ��ȯ


	//���� transform ��ȯ
	void SetReservationWorldTranslateVector(Vector2D _vector);
	void SetReservationLocalTranslateVector(Vector2D _vector);
private:
Vector2D m_ReservationWorldTranslateVector;
Vector2D m_ReservationLocalTranslateVector;
private:

	D2D1_MATRIX_3X2_F MakeRST();
	//���ο��� �����ϱ����� �Լ���
	void UpdateTransform(D2D1::Matrix3x2F _mt);
	void UpdateTranslate(D2D1::Matrix3x2F _mt);
	void UpdateRotate(D2D1::Matrix3x2F _mt);
	void UpdateScale(D2D1::Matrix3x2F _mt);

	D2D1::Matrix3x2F RevertToMtrix(D2D1_MATRIX_3X2_F _mt);

	//���ο��� �����ϱ����� �Լ���
	Vector2D GetWorldTranslateVector();
	Vector2D GetWorldRotateVector();
	Vector2D GetWorldScaleVector();
	D2D1_MATRIX_3X2_F GetWorldScaleMt(Transform* _tr);

	void FindLastChild();
private:
	//�̰��� ������ǥ
	Vector2D m_WorldTranslateVector;
	Vector2D m_WorldRotateVector;
	Vector2D m_WorldScaleVector;
	//�̰��� ������ǥ
	Vector2D m_TranslateVector;
	Vector2D m_RotateVector;
	Vector2D m_ScaleVector;

	D2D1_MATRIX_3X2_F m_WorldMt;
public:
	virtual void SetName() { m_Name = "Transform"; }

};

