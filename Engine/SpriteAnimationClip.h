#pragma once

//class ISprite;
class D2DSprite;
class Transform;

/// <summary>
/// ��������Ʈ �ִϸ��̼� Ŭ�� Ŭ����
///   ��������Ʈ �ִϸ����� ������Ʈ����
///   �ִϸ��̼� Ŭ������ �����ϱ� ���� ������ Ÿ�����μ��� Ŭ����
///   �ִϸ����� ���ο��� ����ü ���� ���� �Ǿ�����,
///   ���� �̸��� �������� ���� ���� Ŭ������ �и���
/// 2022.02.08 �ɽ¼�
/// </summary>
class SpriteAnimationClip
{
// ������
public:
    /// <summary>
    /// ��������Ʈ Ŭ���� ������
    /// </summary>
    /// <param name="_AniClipName">������ ��������Ʈ Ŭ���� �̸�(�ȱ�, ���� ��)</param>
    /// <param name="m_PlayFPS"></param>
    SpriteAnimationClip(string _AniClipName, int m_PlayFPS);
    ~SpriteAnimationClip();

// ����
public:
    // �ִϸ��̼� Ŭ���� ���� �̸� �� �ε���
    string AniClipName;
private:
    // ��������Ʈ �ִϸ��̼��� �� ������ ������ ��������� ����
    int m_PlayFPS;
    vector<D2DSprite*> m_SpriteCollection;
// �Լ�
public:
    // ��������Ʈ Ŭ���� ��������Ʈ�� �߰���
    void AddSprite(D2DSprite* _sprite);
    void AddSprite(string _spritesheet, string _sprite);
	// �ִϸ��̼� Ŭ���� ��� ������ ������ ��ȯ
    int GetPlayFPS() const { return m_PlayFPS; }
    void SetPlayFPS(int val) { m_PlayFPS = val; }
    // �ִϸ��̼� Ŭ���� ��������Ʈ ������ ��ȯ
    int GetSpriteMaxCnt() { return m_SpriteCollection.size(); };
    // �ִϸ��̼� Ŭ������ ��������Ʈ�� ����ϴ� �Լ�
    void DrawAniSnap(D2DEngine* _pEngine, Transform* _tr, int _SpriteIndex, float _Ratio = 1.f, Vector2D _Fill = Vector2D(1, 1));
};
