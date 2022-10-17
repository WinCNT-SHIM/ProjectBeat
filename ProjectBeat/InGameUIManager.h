#pragma once
#include "UIObject.h"
#include <vector>
#include <map>
//#include <list>

class CameraObject; // ī�޶�
enum class Player
{
	player1,
	player2
};

/// <summary>
/// UI �Ŵ��� Ŭ����
/// �ַ� InGameScene���� ���� ����
/// 2022.02.17 �ɽ¼�
/// </summary>
class InGameUIManager
{
// ������ �� �ʱ�ȭ
public:
	InGameUIManager(CameraObject* _SceneCamera);
	~InGameUIManager();
	void Init(int _CharaInxP1 = 0 /*�巳*/, int _CharaInxP2 = 0, /*�巳*/ float _TimerPosX = 960.f, float _TimerPosY = 60.f);

// ����
private:
	// UI�� ī�޶� ������Ʈ ����
	CameraObject* m_SceneCamera;
	
	// ĳ���� ������ UI
	UIObject* m_CharaIconP1;
	UIObject* m_CharaIconP2;

	// ü�¹� UI ������Ʈ(�÷��̾�, ä�¹�)
	UIObject* _PlayerHpBack[2]; // ü�¹� �޺κ�
	map<Player, UIObject*> m_PlayerHp; // ü�¹� �κ�
	map<Player, vector<pair<UIObject*, UIObject*>>> m_HpTempo; // ü�¹� ��ǥ �κ�
	
	// ���� �ð� UI
	UIObject* m_RoundTimeUI_TenDigit[10];
	UIObject* m_RoundTimeUI_OneDigit[10];
	
	// �¸� ���� ī��Ʈ UI
	const int m_MaxScoreCount = 3;
	map<Player, vector<UIObject*>> m_ScoreCountUI;

	// �޺� ����Ʈ UI
	// �÷��̾ ���� �޺��� ����ߴ��� �ƴ����� UI�� ��Ÿ��
	// list�� ù��° UIObject�� ���(��Ƽ��)�ߴٴ� UI
	// list�� �ι�° UIObject�� �̻��(���Ƽ��)�ߴٴ� UI
	map<Player, list<pair<UIObject*, UIObject*>>> m_ComboListUI;
	// �޺� ����Ʈ�� �ִ� ����
	const int m_ComboListMax = 4;

	// ���� ���� UI
	vector<UIObject*> m_CurRoundUI; // ���� ���� ǥ��
	GameObject* m_RoundStartUI;		// Start

	// ���� ���� UI
	map<Player, vector<UIObject*>> m_RoundWinUI;	// ��� �÷��̾� ǥ��
	GameObject* m_RoundEndUI;							// KO ǥ��
// �Լ�
public:
	/// <summary>
	/// ĳ���� �������� ǥ���ϴ� �Լ�
	/// </summary>
	void SetCharaterIcon(bool _IsShow);
	/// <summary>
	/// �÷��̾��� ü�� �������� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Player">��� �÷��̾�</param>
	/// <param name="_ratio">ü�� ������ ����</param>
	void SetHPRatio(Player _Player, float _ratio, bool _IsShow = true);
	/// <summary>
	/// ���� ���� �ð��� UI�� ���� �Ѵ� �Լ�
	/// </summary>
	void SetRoundTimeUI(int _CurRoundTime, bool _IsShow = true);
	/// <summary>
	/// �÷��̾� ���ھ�(�¸� ���� ��)�� UI�� �����ϴ� �Լ�
	/// </summary>
	void SetRoundCountUI(Player _Player, int _playerScore, bool _IsShow = true);
	/// <summary>
	/// �޺� ����Ʈ UI�� ���/�̻������ ��ü�ϴ� �Լ�
	/// </summary>
	void SetComboList(Player _Player, bool _Combo[] = nullptr);
	/// <summary>
	/// ���� ���� UI�� ���� �Ѵ� �Լ�
	/// </summary>
	/// <param name="_CurRound">���� ����</param>
	void SetCurRoundUI(int _CurRound, bool _IsShow = true);
	/// <summary>
	/// ���� ���� UI�� ���� �Ѵ� �Լ�
	/// </summary>
	void SetCurRoundUI(bool _IsShow = true);
	/// <summary>
	/// ���� ����(KO ��)�� UI�� ���� �Ѵ� �Լ�
	/// </summary>
	void PlayRoundEndUI(int _PlayerIndex);
	/// <summary>
	/// ���� ��ŸƮ�� UI ���� �Ѵ� �Լ�.
	/// </summary>
	void PlayRoundStartUI();
};

