#pragma once

#include <string>
#include "nlohmann/json.hpp"

/// <summary>
/// 한 개의 오디오(사운드) 클립
/// 
/// 물리적인 사운드 파일과 그 정보들
/// 네이밍은 유니티를 따랐다.
/// 
/// 2022.02.19 LeHideHome
/// </summary>
class AudioClip
{
public:
	AudioClip();
	~AudioClip();

public:
	// SoundClip 이름
	std::string m_SoundClipName;

	// 쌍을 이루는 json 파일의 위치
	std::string m_MetaFilePath;

	/// 사운드 파일의 메타데이터 (퀄리티, 샘플링 레이트 등 좀 더 raw한 것들)

	/// 속성 (반복여부, 무음, 피치, 볼륨, 3D/2D, 리버브, 에코 등 이펙트..)
	unsigned int m_Mode;
};

namespace nlohmann
{
	template <>
	struct adl_serializer<AudioClip>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, AudioClip& value)
		{
			value.m_SoundClipName = j["Name"].get<std::string>();
			value.m_MetaFilePath = j["FilePath"].get<std::string>();
			value.m_Mode = j["Mode"].get<unsigned int>();
		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const AudioClip& value)
		{
			j["Name"] = value.m_SoundClipName;
			j["FilePath"] = value.m_MetaFilePath;
			j["Mode"] = value.m_Mode;
		}
	};
}