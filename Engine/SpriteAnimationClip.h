#pragma once

//class ISprite;
class D2DSprite;
class Transform;

/// <summary>
/// 스프라이트 애니메이션 클립 클래스
///   스프라이트 애니메이터 컴포넌트에서
///   애니메이션 클립들을 보관하기 위한 데이터 타입으로서의 클래스
///   애니메이터 내부에서 구조체 등을 만들어도 되었지만,
///   파일 이름의 직관성을 위해 따로 클래스로 분리함
/// 2022.02.08 심승수
/// </summary>
class SpriteAnimationClip
{
// 생성자
public:
    /// <summary>
    /// 스프라이트 클립의 생성자
    /// </summary>
    /// <param name="_AniClipName">생성할 스프라이트 클립의 이름(걷기, 공격 등)</param>
    /// <param name="m_PlayFPS"></param>
    SpriteAnimationClip(string _AniClipName, int m_PlayFPS);
    ~SpriteAnimationClip();

// 변수
public:
    // 애니메이션 클립에 대한 이름 겸 인덱스
    string AniClipName;
private:
    // 스프라이트 애니메이션이 몇 프레임 단위로 재생될지를 설정
    int m_PlayFPS;
    vector<D2DSprite*> m_SpriteCollection;
// 함수
public:
    // 스프라이트 클립에 스프라이트를 추가함
    void AddSprite(D2DSprite* _sprite);
    void AddSprite(string _spritesheet, string _sprite);
	// 애니메이션 클립의 재생 프레임 단위를 반환
    int GetPlayFPS() const { return m_PlayFPS; }
    void SetPlayFPS(int val) { m_PlayFPS = val; }
    // 애니메이션 클립의 스프라이트 개수를 반환
    int GetSpriteMaxCnt() { return m_SpriteCollection.size(); };
    // 애니메이션 클립에서 스프라이트를 출력하는 함수
    void DrawAniSnap(D2DEngine* _pEngine, Transform* _tr, int _SpriteIndex, float _Ratio = 1.f, Vector2D _Fill = Vector2D(1, 1));
};
