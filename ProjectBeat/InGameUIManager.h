#pragma once
#include "UIObject.h"
#include <vector>
#include <map>
//#include <list>

class CameraObject; // 카메라
enum class Player
{
	player1,
	player2
};

/// <summary>
/// UI 매니저 클래스
/// 주로 InGameScene에서 쓰일 예정
/// 2022.02.17 심승수
/// </summary>
class InGameUIManager
{
// 생성자 및 초기화
public:
	InGameUIManager(CameraObject* _SceneCamera);
	~InGameUIManager();
	void Init(int _CharaInxP1 = 0 /*드럼*/, int _CharaInxP2 = 0, /*드럼*/ float _TimerPosX = 960.f, float _TimerPosY = 60.f);

// 변수
private:
	// UI의 카메라 오브젝트 숏컷
	CameraObject* m_SceneCamera;
	
	// 캐릭터 아이콘 UI
	UIObject* m_CharaIconP1;
	UIObject* m_CharaIconP2;

	// 체력바 UI 오브젝트(플레이어, 채력바)
	UIObject* _PlayerHpBack[2]; // 체력바 뒷부분
	map<Player, UIObject*> m_PlayerHp; // 체력바 부분
	map<Player, vector<pair<UIObject*, UIObject*>>> m_HpTempo; // 체력바 음표 부분
	
	// 라운드 시간 UI
	UIObject* m_RoundTimeUI_TenDigit[10];
	UIObject* m_RoundTimeUI_OneDigit[10];
	
	// 승리 라운드 카운트 UI
	const int m_MaxScoreCount = 3;
	map<Player, vector<UIObject*>> m_ScoreCountUI;

	// 콤보 리스트 UI
	// 플레이어에 따라 콤보를 사용했는지 아닌지를 UI로 나타냄
	// list의 첫번째 UIObject가 사용(액티브)했다는 UI
	// list의 두번째 UIObject가 미사용(언액티브)했다는 UI
	map<Player, list<pair<UIObject*, UIObject*>>> m_ComboListUI;
	// 콤보 리스트의 최대 개수
	const int m_ComboListMax = 4;

	// 라운드 시작 UI
	vector<UIObject*> m_CurRoundUI; // 현재 라운드 표시
	GameObject* m_RoundStartUI;		// Start

	// 라운드 종료 UI
	map<Player, vector<UIObject*>> m_RoundWinUI;	// 우승 플레이어 표시
	GameObject* m_RoundEndUI;							// KO 표시
// 함수
public:
	/// <summary>
	/// 캐릭터 아이콘을 표시하는 함수
	/// </summary>
	void SetCharaterIcon(bool _IsShow);
	/// <summary>
	/// 플레이어의 체력 게이지를 설정하는 함수
	/// </summary>
	/// <param name="_Player">대상 플레이어</param>
	/// <param name="_ratio">체력 게이지 비율</param>
	void SetHPRatio(Player _Player, float _ratio, bool _IsShow = true);
	/// <summary>
	/// 라운드 제한 시간의 UI를 끄고 켜는 함수
	/// </summary>
	void SetRoundTimeUI(int _CurRoundTime, bool _IsShow = true);
	/// <summary>
	/// 플레이어 스코어(승리 라운드 수)의 UI를 설정하는 함수
	/// </summary>
	void SetRoundCountUI(Player _Player, int _playerScore, bool _IsShow = true);
	/// <summary>
	/// 콤보 리스트 UI를 사용/미사용으로 교체하는 함수
	/// </summary>
	void SetComboList(Player _Player, bool _Combo[] = nullptr);
	/// <summary>
	/// 현재 라운드 UI를 끄고 켜는 함수
	/// </summary>
	/// <param name="_CurRound">현재 라운드</param>
	void SetCurRoundUI(int _CurRound, bool _IsShow = true);
	/// <summary>
	/// 현재 라운드 UI를 끄고 켜는 함수
	/// </summary>
	void SetCurRoundUI(bool _IsShow = true);
	/// <summary>
	/// 게임 엔드(KO 등)의 UI를 끄고 켜는 함수
	/// </summary>
	void PlayRoundEndUI(int _PlayerIndex);
	/// <summary>
	/// 게임 스타트의 UI 끄고 켜는 함수.
	/// </summary>
	void PlayRoundStartUI();
};

