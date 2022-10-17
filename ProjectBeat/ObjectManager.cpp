#include "GamePCH.h"
#include "ObjectManager.h"
#include <algorithm>
ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	DeleteAll();
}



bool ObjectManager::cmp(GameObject* A, GameObject* B)
{
	return A->GetLayer() < B->GetLayer();
}

//��ü �߰�
void ObjectManager::InsertObject(GameObject* obj)
{
	if (!obj) return;
	m_vectorObjects.push_back(obj);

	if (obj->collider)
		m_AllColliderObjects.push_back(obj);

	obj->Start();
	for (auto iter : obj->m_Components)
	{
		iter->Start();
	}
	LayerSort();
}

void ObjectManager::InsertObjectAll(GameObject* parent)
{
	InsertObject(parent);

	for (auto child : *parent->GetChilds())
	{
		InsertObjectAll(child);
	}
}

void ObjectManager::LayerSort()
{
	std::sort(m_vectorObjects.begin(), m_vectorObjects.end(), cmp);
}

void ObjectManager::PushBackObject(GameObject* obj)
{
	if (!obj) return;
	m_InsertObjects.push_back(obj);
}
//Ư�� ��ü ����
void ObjectManager::DeleteObject(GameObject* obj)
{
	if (!obj) return;
	m_DeleteObjects.push_back(obj);
}

//������Ʈ�� �ݶ��̴� ���� ����
void ObjectManager::DeleteAll()
{
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		delete (*iter);
	}
	m_AllColliderObjects.clear();
	m_vectorObjects.clear();
}

void ObjectManager::Update()
{
	//��� ������Ʈ ������Ʈ ������
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		if ((*iter)->m_ActiveSelf)
			(*iter)->Update();
	}

	for (auto iter = m_AllColliderObjects.begin(); iter != m_AllColliderObjects.end(); iter++)
	{
		if (GameManager::Instance()->GetPause()) break;

		if ((*iter)->m_ActiveSelf)
			(*iter)->PhysicsUpdate();
	}

	for (auto iter = m_AllColliderObjects.begin(); iter != m_AllColliderObjects.end(); iter++)
	{
		if (GameManager::Instance()->GetPause()) break;
		//���߿� ����..
		if (!(*iter)->m_ActiveSelf) continue;

		for (auto iter2 = m_AllColliderObjects.begin(); iter2 != m_AllColliderObjects.end(); iter2++)
		{
			if (!(*iter)->m_ActiveSelf) continue;

			if ((*iter)->m_teg == " " || (*iter2)->m_teg == " " || (*iter)->m_teg != (*iter2)->m_teg)
			{
				if (iter != iter2)
				{
					if ((*iter)->collider->Check((*iter2)->collider))
					{
						Collider* A = (*iter)->collider;
						Collider* B = (*iter2)->collider;

						auto item = A->m_OtherCollider.find((*iter2));
						if (item == A->m_OtherCollider.end())
						{
							A->m_OtherCollider.insert(make_pair((*iter2), new CollisionBool()));
							A->m_OtherCollider[(*iter2)]->m_isCur = true;
						}
						else
						{
							A->m_OtherCollider[(*iter2)]->m_isCur = true;
						}
						//if ((*iter)->m_Pyhsics)
						//{
						//	(*iter)->OnColliderPhysics((*iter2));
						//}
					}
				}
			}
		}

	}





	for (auto iter = m_DeleteObjects.begin(); iter != m_DeleteObjects.end(); iter++)
	{

		for (auto iter2 = m_vectorObjects.begin(); iter2 != m_vectorObjects.end(); iter2++)
		{
			if (*iter == *iter2)
			{
				m_vectorObjects.erase(iter2);
				break;
			}
		}
		for (auto iter2 = m_AllColliderObjects.begin(); iter2 != m_AllColliderObjects.end(); iter2++)
		{
			if (*iter == *iter2)
			{
				m_AllColliderObjects.erase(iter2);
				break;
			}
		}

		delete* iter;
		m_DeleteObjects.erase(iter);
		break;
	}

	for (auto iter : m_InsertObjects)
	{
		InsertObject(iter);
	}
	if (!m_InsertObjects.empty())
		m_InsertObjects.clear();
}

//��� ������Ʈ ����
void ObjectManager::Render(D2DEngine* _pEngine)
{
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		//������Ʈ�� ���� ������
		for (auto iter2 : (*iter)->m_Components)
		{
			if ((*iter)->m_ActiveSelf)
				iter2->Render(_pEngine);
		}
	}
}
