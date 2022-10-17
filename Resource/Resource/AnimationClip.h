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
	// AnimationClip 이름
	std::string _animationClipName;
	// 쌍을 이루는 json 파일의 위치
	std::string _metaFilePath;

	bool _loop = true;
	bool _isPlay = true;
	float _lastAnimationTime = 0.f;
	vector<AnimationSnap> _animationSnaps;
public:
	/// <summary>
	/// AnimationSnap에 오브젝트를 붙여줌
	/// </summary>
	/// <param name="objects">오브젝트 이름과 오브젝트 포인터로 이루어진 맵</param>
	void AttachObject(map<string, GameObject*>& objects);

	/// <summary>
	/// Animation Snap를 _animationSnaps 에 push
	/// </summary>
	/// <param name="animationSnap">애니메이션 스냅</param>
	void AddAnimationSnap(AnimationSnap animationSnap);

	/// <summary>
	/// 초기화 작업
	/// 1. 비어있는 스냅 데이터를 선형 보간으로 만들어줌
	/// 2. 벡터를 프레임 순서대로 sort
	/// </summary>
	void Init();

	/// <summary>
	/// 현재 프레임 혹은 시간에 맞는 애니메이션 스냅을 적용시켜줌
	/// </summary>
	void Update(float& currTimer, int& currFrame);

	/// <summary>
	/// 애니메이션 클립를 선형보간으로 재생
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