#pragma once
#include <map>
#include <string>
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace std;

class D2DSpriteSheet;
class AnimationClip;
class AnimatorController;
class AudioClip;

class JsonParse
{
public:
	JsonParse();
	~JsonParse();

public:

#pragma region Sprite

	// ��� sprite meta json ������ �о�ͼ� spriteSheetMeta�� push
	void LoadAllSpriteSheetMeta(string filepath, std::map<string, D2DSpriteSheet*>& spriteSheetMeta);

	// ��� SpriteMeta�� �� json ���Ͽ� ������
	void SaveAllSpriteSheetMeta(std::map<string, D2DSpriteSheet*>& spriteSheetMeta);

	// SpriteSheetmeta���� ��ġ�� ������ json ����Ÿ�� ������
	void SaveAllSpriteSheetMetaFilePath(string filepath, std::map<string, D2DSpriteSheet*>& spriteSheetMeta);

	// ��������Ʈ ��Ʈ�� ������ Json ���Ϸ� ���� �о�ͼ� D2DSpriteSheet*�� ��ȯ����
	D2DSpriteSheet* LoadSpriteSheetMeta(string filepath);

	// filepath ����� json ���Ͽ� sprite sheet meta�� ����
	void SaveSpriteSheetMeta(string filepath, D2DSpriteSheet* spriteSheet);

#pragma endregion

#pragma region AnimationClip

	// ��� AnimationClip meta json ������ �о�ͼ� animationClipMeta�� push
	void LoadAllAnimationClipMeta(string filepath, std::map<string, AnimationClip*>& animationClips);

	// ��� SpriteMeta�� �� json ���Ͽ� ������
	void SaveAllAnimationClipMeta(std::map<string, AnimationClip*>& animationClips);

	// AnimationClip meta���� ��ġ�� ������ json ����Ÿ�� ������
	void SaveAllAnimationClipMetaFilePath(string filepath, std::map<string, AnimationClip*>& animationClips);

	// filepath ����� json ���Ͽ� AnimationClip meta�� ����
	void SaveAnimationClipMeta(string filepath, AnimationClip* animationClip);

	// �ִϸ��̼� Ŭ�� ������ Json ���Ϸκ��� �о�ͼ� AnimationClip*�� ��ȯ����
	AnimationClip* LoadAnimationClipMeta(string filepath);

#pragma endregion

#pragma region AnimationClip

	// ��� AnimatorController meta json ������ �о�ͼ� animatorControllerMeta�� push
	void LoadAllAnimatorControllerMeta(string filepath, std::map<string, AnimatorController*>& animationControllers);

	// ��� AnimatorController meta�� �� json ���Ͽ� ������
	void SaveAllAnimatorControllerMeta(std::map<string, AnimatorController*>& animationControllers);

	// AnimatorController meta���� ��ġ�� ������ json ����Ÿ�� ������
	void SaveAllAnimatorControllerMetaFilePath(string filepath, std::map<string, AnimatorController*>& animatorControllers);

	// filepath ����� json ���Ͽ� AnimatorController meta�� ����
	void SaveAnimatorControllerMeta(string filepath,  AnimatorController* animatorController);

	// �ִϸ��̼� Ŭ�� ������ Json ���Ϸκ��� �о�ͼ� AnimatorController*�� ��ȯ����
	AnimatorController* LoadAnimatorControllerMeta(string filepath);

#pragma endregion


#pragma region AudioClip

	// ��� ���������� �о �����Ŭ������ �����.
	void LoadAllAudioClip(std::string filePath, std::map<string, AudioClip*>& soundList);

#pragma endregion
};
