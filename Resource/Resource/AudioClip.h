#pragma once

#include <string>
#include "nlohmann/json.hpp"

/// <summary>
/// �� ���� �����(����) Ŭ��
/// 
/// �������� ���� ���ϰ� �� ������
/// ���̹��� ����Ƽ�� ������.
/// 
/// 2022.02.19 LeHideHome
/// </summary>
class AudioClip
{
public:
	AudioClip();
	~AudioClip();

public:
	// SoundClip �̸�
	std::string m_SoundClipName;

	// ���� �̷�� json ������ ��ġ
	std::string m_MetaFilePath;

	/// ���� ������ ��Ÿ������ (����Ƽ, ���ø� ����Ʈ �� �� �� raw�� �͵�)

	/// �Ӽ� (�ݺ�����, ����, ��ġ, ����, 3D/2D, ������, ���� �� ����Ʈ..)
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