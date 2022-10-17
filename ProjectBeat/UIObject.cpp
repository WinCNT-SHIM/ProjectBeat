#include "GamePCH.h"
#include "UIObject.h"
#include "CameraObject.h"

UIObject::UIObject(std::string _UIName, CameraObject* _CameraObject, string _SheetName, string _SpriteName, float _alpha /*= 1.f*/, float _ratio /*= 1.f*/) :
    GameObject()
{
    SetName("UIObject_" + _UIName);
    this->SetParent(_CameraObject);
    this->SetLayer(9999); // UI는 최상위 레이어에 위치
    m_UIRenderer = AddComponent<SpriteRenderer>();
    m_UIRenderer->Init(_SheetName, _SpriteName, _ratio);
    m_UIRenderer->SetAlpha(_alpha);
    
    m_tr->SetLocalTranslateVector(
        Vector2D((float)m_UIRenderer->_sprite->CenterPosX, (float)m_UIRenderer->_sprite->CenterPosY)
    );
    this->Init();
}

UIObject::~UIObject()
{
}

void UIObject::Init()
{
    m_UIRenderer->SetFill(1.f, 1.f);
    GetUIRenderer()->SetDrawMode(DrawMode::Fill);
}
