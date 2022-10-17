#pragma once
#include "ISprite.h"
#include <string>
#include "nlohmann/json.hpp"

class D2DSprite :
    public ISprite
{
public:
	D2DSprite();
	D2DSprite(int spriteSheetIndex, int oriX, int oriY, int index, int width, int height, int keyColor,
		int centerPosX, int centerPosY);
	virtual ~D2DSprite();


public:
	std::string m_spriteName;

	// 스프라이트 시트의 인덱스
	int m_SheetIndex;

	// 원본에서의 위치
	int m_OriX;
	int m_OriY;
};

namespace nlohmann
{
	template <>
	struct adl_serializer<D2DSprite>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, D2DSprite& value)
		{
			value.m_spriteName = j["SpriteName"].get<std::string>();
			value.m_OriX = j["OriX"].get<int>();
			value.m_OriY = j["OriY"].get<int>();
			value.Width = j["Width"].get<int>();
			value.Height = j["Height"].get<int>();
			value.KeyColor = j["KeyColor"].get<int>();
			value.CenterPosX = j["CenterPosX"].get<int>();
			value.CenterPosY = j["CenterPosY"].get<int>();
		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const D2DSprite& sprite)
		{
			j = json{
				{ "SpriteName", sprite.m_spriteName },
				{ "OriX",		sprite.m_OriX },
				{ "OriY",		sprite.m_OriY },
				{ "Width",		sprite.Width },
				{ "Height",		sprite.Height },
				{ "KeyColor",	sprite.KeyColor },
				{ "CenterPosX",	sprite.CenterPosX },
				{ "CenterPosY",	sprite.CenterPosY },
			};
			/*j.at("SpriteName").get_to(sprite.m_spriteName);
			j.at("OriX").get_to(sprite.m_OriX);
			j.at("OriY").get_to(sprite.m_OriY);
			j.at("Width").get_to(sprite.Width);
			j.at("Height").get_to(sprite.Height);
			j.at("KeyColor").get_to(sprite.KeyColor);
			j.at("CenterPosX").get_to(sprite.CenterPosX);
			j.at("CenterPosY").get_to(sprite.CenterPosY);*/
		}
	};
}