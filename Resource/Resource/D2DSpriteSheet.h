#pragma once
#include "D2DSprite.h"
#include <map>
#include "nlohmann/json.hpp"

class D2DSpriteSheet
{
public:
	D2DSpriteSheet();
	D2DSpriteSheet(const D2DSpriteSheet&);
	~D2DSpriteSheet();

public:
	// ��������Ʈ�� �̸�
	std::string _sheetName;

	static int _spriteSheetCnt;

	// �������� ���� �ε���
	int _spriteSheetIndex;

	// ���� �̷�� json ������ ��ġ
	std::string _metaFilePath;

	// ���� �̷�� �̹��� ������ ��ġ
	std::string _imageFilePath;

	// ��������Ʈ���� ������ ��� ��
	std::map<std::string, D2DSprite*> _spriteSheet;

public:
	void AddSprite(std::string name, D2DSprite* sprite);
};

namespace nlohmann
{
	template <>
	struct adl_serializer<D2DSpriteSheet>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, D2DSpriteSheet& sheet)
		{
			sheet._sheetName = j["SheetName"].get<std::string>();
			sheet._imageFilePath = j["ImageFilePath"].get<std::string>();
			auto spriteSheets = j["SpriteSheet"];
			D2DSprite* sprite;
			for (auto& elements : spriteSheets.items())
			{
				D2DSprite temp = elements.value().get<D2DSprite>();
				sprite = new D2DSprite(temp);
				sheet.AddSprite(elements.key(), sprite);
			}
		} 

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const D2DSpriteSheet& sheet)
		{
			j["SheetName"] = sheet._sheetName;
			j["ImageFilePath"] = sheet._imageFilePath;

			for (auto iter = sheet._spriteSheet.begin(); iter != sheet._spriteSheet.end(); iter++)
			{
				j["SpriteSheet"][iter->first] = *(iter->second);
			}
		}
	};
}