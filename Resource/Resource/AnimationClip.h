#pragma once
#include "AnimationSnap.h"
#include <map>

class SnapFrame
{
	SnapFrame() {}
	~SnapFrame() {}
	int positionFrame = 0;
	int rotateFrame = 0;
	int scaleFrame = 0;
	int spriteFrame = 0;
	int eventFrame = 0;
};

class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();

public:
	// AnimationClip �̸�
	std::string _animationClipName;
	// ���� �̷�� json ������ ��ġ
	std::string _metaFilePath;

	bool _loop = true;
	bool _isPlay = true;
	float _lastAnimationTime = 0.f;
	vector<AnimationSnap> _animationSnaps;
public:
	/// <summary>
	/// AnimationSnap�� ������Ʈ�� �ٿ���
	/// </summary>
	/// <param name="objects">������Ʈ �̸��� ������Ʈ �����ͷ� �̷���� ��</param>
	void AttachObject(map<string, GameObject*>& objects);

	/// <summary>
	/// Animation Snap�� _animationSnaps �� push
	/// </summary>
	/// <param name="animationSnap">�ִϸ��̼� ����</param>
	void AddAnimationSnap(AnimationSnap animationSnap);

	/// <summary>
	/// �ʱ�ȭ �۾�
	/// 1. ����ִ� ���� �����͸� ���� �������� �������
	/// 2. ���͸� ������ ������� sort
	/// </summary>
	void Init();

	/// <summary>
	/// ���� ������ Ȥ�� �ð��� �´� �ִϸ��̼� ������ ���������
	/// </summary>
	void Update(float& currTimer, int& currFrame);

	/// <summary>
	/// �ִϸ��̼� Ŭ���� ������������ ���
	/// </summary>
	void Play(float& currTimer, int& currFrame);

	void AnimationEvent(SnapData& snapData);
};

namespace nlohmann
{
	template <>
	struct adl_serializer<AnimationClip>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, AnimationClip& value)
		{
			value._animationClipName = j["Name"].get<std::string>();
			value._loop = j["Loop"].get<bool>();
			value._animationSnaps = j["AnimationSnaps"].get<vector<AnimationSnap>>();
		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const AnimationClip& animationClip)
		{
			j["Name"] = animationClip._animationClipName;
			j["Loop"] = animationClip._loop;
			j["AnimationSnaps"] = json(animationClip._animationSnaps);
		}
	};
}