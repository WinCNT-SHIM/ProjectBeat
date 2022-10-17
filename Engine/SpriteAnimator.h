#pragma once
#include "Component.h"
#include "Transform.h"
#include <map>

class SpriteAnimationClip;

// Fill를 사용할지에 대한 모드
enum class FillMode
{
    Simple,
    Fill
};

/// <summary>
/// 스프라이트 애니메이터 컴포넌트
/// 스프라이트 애니메이션 클립을 재생, 컨트롤하는 컴포넌트
///   트랜스폼 애니메이션과는 달리, 스프라이트 시트에서
///   스프라이트를 재생시키기 위한 컴포넌트임
/// Update에서 프레임을 체크해서 애니메이션 클립을 변경할지 정하고
/// Render는 애니메이션 클립의 한 장면을 렌더링한다
/// 애니메이션 재생은 한 번만 재생이 디폴트(함수로 변경 가능)
/// 작성일: 2022.02.08 심승수
/// 수정일: 2022.02.11 심승수
///   Init() 추가
/// 수정일: 2022.02.14 심승수
///   Fill 팩터(지정된 수치만큼 뒷부분을 자름) 추가
/// </summary>
class SpriteAnimator :
	public Component
{
// 생성자 및 초기화
public:
	SpriteAnimator(GameObject* _GameObject);
	virtual ~SpriteAnimator();
	// 스프라이트 애니메이션의 초기화 함수
	void Init();
// 변수
private:
	// 애니메이션 클립의 모음
	std::map<string, SpriteAnimationClip*> m_AniClipCollection;
	// 애니메이터 재생 위치에 관한 트랜스폼
	Transform* m_tr;
	// 현재 애니메이터에 지정/재생 중인 애니메이션 클립
	SpriteAnimationClip* m_curAniClip;
	// 현재 출력 중인 애니메이션 클립의 스프라이트의 인덱스
	int m_SpriteIndex;
	// 현재 출력 중인 애니메이션 클립의 최대 개수
	int m_SpriteMaxCnt;
	// 현재 프레임
	int m_CurFPS;
	// 스프라이트 애니메이션이 몇 프레임 단위로 재생될지를 설정
	int m_PlayFPS;
	// 스프라이트 애니메이션을 재생할지에 대한 변수
	bool m_isPlaying;
	// 스프라이트 애니메이션 재생이 루프인지에 대한 변수
	bool m_isLoop;
	// 스프라이트의 채움 비율
    Vector2D m_Fill;
    // 비율
    float m_Ratio;
	// 필 모드
	FillMode m_drawMode;
// 함수
public:
	virtual void SetName() { m_Name = "SpriteAniamtor"; }
	// 스프라이트 애니메이션의 재생 프레임을 제어하는 함수
	virtual void Update() override;
	// 스프라이트 애니메이션 클립을 재생하는 함수
	virtual void Render(D2DEngine* _pEngine) override;
	// 지정/재생할 애니메이션 클립을 추가하는 함수
	void AddAnimationClip(string _AniClipName, SpriteAnimationClip* _AniClip);
	// 지정/재생할 애니메이션 클립을 설정하는 함수
	void SetAnimationClip(string _AniClipName);
	// 애니메이션 재생을 정지하는 함수
	void StopAnimation();
	//애니메이션을 반복 재생할지를 설정하는 함수
	void SetLoopPlay(bool _isLoop);
	// 애니메이션 재생 함수.
	void Play();

	bool GetIsPlay() { return m_isPlaying; }
	// 스프라이트 애니메이터의 비율을 설정하는 함수
    void SetAnimatorRatio(float val) { m_Ratio = val; }
	// 스프라이트 애니메이터의 채움 비율을 설정하는 함수(0~1)
	void SetFill(float _FillX, float _FillY);
	Vector2D GetFill() { return m_Fill; };
    /// <summary>
	/// Fill 모드 설정(디폴트는 사용 안 함)
	/// </summary>
	/// <param name="mode">DrawMode::Simple, DrawMode::Fill</param>
    void SetDrawMode(FillMode mode) { m_drawMode = mode; }
};

