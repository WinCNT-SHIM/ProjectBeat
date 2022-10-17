#include "JsonParse.h"
#include <fstream>
#include "D2DSpriteSheet.h"
#include "AnimatorController.h"
#include "AnimationClip.h"
#include "AudioClip.h"


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

JsonParse::JsonParse()
{
}

JsonParse::~JsonParse()
{
}

void JsonParse::LoadAllSpriteSheetMeta(string filepath, std::map<string, D2DSpriteSheet*>& spriteSheetMeta)
{
	std::ifstream stream;
	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);
		D2DSpriteSheet* spriteSheet;
		for (auto& iter : jsonData)
		{
			spriteSheet = LoadSpriteSheetMeta(iter.get<std::string>());
			spriteSheetMeta.insert({ spriteSheet->_sheetName , spriteSheet });
		}
	}

	stream.close();
}

void JsonParse::SaveAllSpriteSheetMetaFilePath(string filepath, std::map<string, D2DSpriteSheet*>& spriteSheetMeta)
{
	std::ofstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json json_File_Path;
		for (auto iter : spriteSheetMeta)
		{
			json_File_Path.push_back(iter.second->_metaFilePath);
		}
		stream << json_File_Path << std::endl;
	}

	stream.close();
}

void JsonParse::SaveAllSpriteSheetMeta(std::map<string, D2DSpriteSheet*>& spriteSheetMeta)
{
	for (auto iter : spriteSheetMeta)
	{
		SaveSpriteSheetMeta(iter.second->_metaFilePath, iter.second);
	}
}

D2DSpriteSheet* JsonParse::LoadSpriteSheetMeta(string filepath)
{
	std::ifstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);
		D2DSpriteSheet sheet1 = jsonData.get<D2DSpriteSheet>();
		D2DSpriteSheet::_spriteSheetCnt--;
		D2DSpriteSheet* sheet = new D2DSpriteSheet(sheet1);
		for (auto iter : sheet->_spriteSheet)
		{
			iter.second->m_SheetIndex = sheet->_spriteSheetIndex;
		}
		sheet->_metaFilePath = filepath;
		return sheet;
	}

	stream.close();

	return nullptr;
}

void JsonParse::SaveSpriteSheetMeta(string filepath, D2DSpriteSheet* spriteSheet)
{
	std::ofstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData(*spriteSheet);
		string test = jsonData.dump();
		stream << test << std::endl;
	}

	stream.close();
}

void JsonParse::LoadAllAnimationClipMeta(string filepath, std::map<string, AnimationClip*>& animationClips)
{
	std::ifstream stream;
	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);

		for (auto& iter : jsonData)
		{
			AnimationClip* animationClip = LoadAnimationClipMeta(iter.get<std::string>());
			animationClips.insert({animationClip->_animationClipName, animationClip});
		}
	}

	stream.close();
}

void JsonParse::SaveAllAnimationClipMeta(std::map<string, AnimationClip*>& animationClips)
{
	for (auto iter : animationClips)
	{
		SaveAnimationClipMeta(iter.second->_metaFilePath, iter.second);
	}
}

void JsonParse::SaveAllAnimationClipMetaFilePath(string filepath, std::map<string, AnimationClip*>& animationClips)
{
	std::ofstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json json_File_Path;
		for (auto iter : animationClips)
		{
			json_File_Path.push_back(iter.second->_metaFilePath);
		}
		stream << json_File_Path << std::endl;
	}

	stream.close();
}

void JsonParse::SaveAnimationClipMeta(string filepath, AnimationClip* animationClip)
{
	std::ofstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData(*animationClip);
		string test = jsonData.dump();
		stream << test << std::endl;
	}

	stream.close();
}

AnimationClip* JsonParse::LoadAnimationClipMeta(string filepath)
{
	std::ifstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);
		auto temp = jsonData.get<AnimationClip>();
		auto animationClip = new AnimationClip(temp);
		animationClip->_metaFilePath = filepath;
		return animationClip;
	}

	stream.close();

	return nullptr;
}

void JsonParse::LoadAllAnimatorControllerMeta(string filepath, std::map<string, AnimatorController*>& animationControllers)
{
	std::ifstream stream;
	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);

		for (auto& iter : jsonData)
		{
			AnimatorController* animationController = LoadAnimatorControllerMeta(iter.get<std::string>());
			animationControllers.insert({ animationController->_animatorControllerName, animationController });
		}
	}

	stream.close();
}

void JsonParse::SaveAllAnimatorControllerMeta(std::map<string, AnimatorController*>& animationControllers)
{
	for (auto iter : animationControllers)
	{
		SaveAnimatorControllerMeta(iter.second->_metaFilePath, iter.second);
	}
}

void JsonParse::SaveAllAnimatorControllerMetaFilePath(string filepath, std::map<string, AnimatorController*>& animatorControllers)
{
	std::ofstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json json_File_Path;
		for (auto iter : animatorControllers)
		{
			json_File_Path.push_back(iter.second->_metaFilePath);
		}
		stream << json_File_Path << std::endl;
	}

	stream.close();

}

void JsonParse::SaveAnimatorControllerMeta(string filepath, AnimatorController* animatorController)
{
	std::ofstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData(*animatorController);
		string test = jsonData.dump();
		stream << test << std::endl;
	}

	stream.close();
}

AnimatorController* JsonParse::LoadAnimatorControllerMeta(string filepath)
{
	std::ifstream stream;

	stream.open(filepath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);
		AnimatorController temp = jsonData.get<AnimatorController>();
		auto animatorController = new AnimatorController(temp);
		animatorController->_metaFilePath = filepath;
		return animatorController;
	}

	stream.close();

	return nullptr;
}

void JsonParse::LoadAllAudioClip(std::string filePath, std::map<string, AudioClip*>& soundList)
{
	std::ifstream stream;
	stream.open(filePath);

	if (stream.is_open() && !stream.fail())
	{
		json jsonData = json::parse(stream);
		AudioClip* _nowAudioClip = nullptr;

		for (auto& iter : jsonData)
		{
			AudioClip temp = iter.get<AudioClip>();
			_nowAudioClip = new AudioClip(temp);
			soundList.insert({ _nowAudioClip->m_SoundClipName , _nowAudioClip });
		}
	}

	stream.close();
}
