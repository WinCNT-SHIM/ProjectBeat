#pragma once
#include "Component.h"
#include "Transform.h"
#include <map>

class SpriteAnimationClip;

// Fill�� ��������� ���� ���
enum class FillMode
{
    Simple,
    Fill
};

/// <summary>
/// ��������Ʈ �ִϸ����� ������Ʈ
/// ��������Ʈ �ִϸ��̼� Ŭ���� ���, ��Ʈ���ϴ� ������Ʈ
///   Ʈ������ �ִϸ��̼ǰ��� �޸�, ��������Ʈ ��Ʈ����
///   ��������Ʈ�� �����Ű�� ���� ������Ʈ��
/// Update���� �������� üũ�ؼ� �ִϸ��̼� Ŭ���� �������� ���ϰ�
/// Render�� �ִϸ��̼� Ŭ���� �� ����� �������Ѵ�
/// �ִϸ��̼� ����� �� ���� ����� ����Ʈ(�Լ��� ���� ����)
/// �ۼ���: 2022.02.08 �ɽ¼�
/// ������: 2022.02.11 �ɽ¼�
///   Init() �߰�
/// ������: 2022.02.14 �ɽ¼�
///   Fill ����(������ ��ġ��ŭ �޺κ��� �ڸ�) �߰�
/// </summary>
class SpriteAnimator :
	public Component
{
// ������ �� �ʱ�ȭ
public:
	SpriteAnimator(GameObject* _GameObject);
	virtual ~SpriteAnimator();
	// ��������Ʈ �ִϸ��̼��� �ʱ�ȭ �Լ�
	void Init();
// ����
private:
	// �ִϸ��̼� Ŭ���� ����
	std::map<string, SpriteAnimationClip*> m_AniClipCollection;
	// �ִϸ����� ��� ��ġ�� ���� Ʈ������
	Transform* m_tr;
	// ���� �ִϸ����Ϳ� ����/��� ���� �ִϸ��̼� Ŭ��
	SpriteAnimationClip* m_curAniClip;
	// ���� ��� ���� �ִϸ��̼� Ŭ���� ��������Ʈ�� �ε���
	int m_SpriteIndex;
	// ���� ��� ���� �ִϸ��̼� Ŭ���� �ִ� ����
	int m_SpriteMaxCnt;
	// ���� ������
	int m_CurFPS;
	// ��������Ʈ �ִϸ��̼��� �� ������ ������ ��������� ����
	int m_PlayFPS;
	// ��������Ʈ �ִϸ��̼��� ��������� ���� ����
	bool m_isPlaying;
	// ��������Ʈ �ִϸ��̼� ����� ���������� ���� ����
	bool m_isLoop;
	// ��������Ʈ�� ä�� ����
    Vector2D m_Fill;
    // ����
    float m_Ratio;
	// �� ���
	FillMode m_drawMode;
// �Լ�
public:
	virtual void SetName() { m_Name = "SpriteAniamtor"; }
	// ��������Ʈ �ִϸ��̼��� ��� �������� �����ϴ� �Լ�
	virtual void Update() override;
	// ��������Ʈ �ִϸ��̼� Ŭ���� ����ϴ� �Լ�
	virtual void Render(D2DEngine* _pEngine) override;
	// ����/����� �ִϸ��̼� Ŭ���� �߰��ϴ� �Լ�
	void AddAnimationClip(string _AniClipName, SpriteAnimationClip* _AniClip);
	// ����/����� �ִϸ��̼� Ŭ���� �����ϴ� �Լ�
	void SetAnimationClip(string _AniClipName);
	// �ִϸ��̼� ����� �����ϴ� �Լ�
	void StopAnimation();
	//�ִϸ��̼��� �ݺ� ��������� �����ϴ� �Լ�
	void SetLoopPlay(bool _isLoop);
	// �ִϸ��̼� ��� �Լ�.
	void Play();

	bool GetIsPlay() { return m_isPlaying; }
	// ��������Ʈ �ִϸ������� ������ �����ϴ� �Լ�
    void SetAnimatorRatio(float val) { m_Ratio = val; }
	// ��������Ʈ �ִϸ������� ä�� ������ �����ϴ� �Լ�(0~1)
	void SetFill(float _FillX, float _FillY);
	Vector2D GetFill() { return m_Fill; };
    /// <summary>
	/// Fill ��� ����(����Ʈ�� ��� �� ��)
	/// </summary>
	/// <param name="mode">DrawMode::Simple, DrawMode::Fill</param>
    void SetDrawMode(FillMode mode) { m_drawMode = mode; }
};

