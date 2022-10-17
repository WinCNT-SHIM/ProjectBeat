#pragma once
#include <vector>
#include <string>
#include <map>
#include "DataInfo.h"
#include "nlohmann/json.hpp"

using namespace std;

class GameObject;
class D2DSprite;

/// <summary>
/// 각 프레임 별 Animation Snap Data
/// </summary>
struct SnapData
{
	SnapData()
	{

	}
	SnapData(string objectName, string sheetName, string spriteName
	, Vector2 position, Vector2 rotate, Vector2 scale)
	{
		_objectName = string(objectName);
		_sheetName = string(sheetName);
		_spriteName = string(spriteName);
		_positionSnap = position;
		_rotateSnap = rotate;
		_scaleSnap = scale;
	}
	string _objectName;
	GameObject* _targetObject = nullptr;

	bool _spriteSnapExist = false;
	string _sheetName;
	string _spriteName;

	bool _positionSnapExist = false;
	Vector2 _positionSnap;

	bool _rotateSnapExist = false;
	Vector2 _rotateSnap;

	bool _scaleSnapExist = false;
	Vector2 _scaleSnap;

	bool _eventSnapExist = false;
	string _component;
	string _event;
	bool _isDone = false;
};

class AnimationSnap
{
public:
	AnimationSnap();
	~AnimationSnap();

	float _time = 0.f;

	vector<SnapData> _snapDatas;
public:

	void AttachObject(map<string, GameObject*>& objects);
	void AddSnapData(SnapData snapData);
	void Init();
	void Play();
	void InitEvent();
};

namespace nlohmann
{
	template <>
	struct adl_serializer<SnapData>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, SnapData& value)
		{
			value._objectName = j["ObjectName"].get<std::string>();
			for (auto& el : j.items())
			{	
				if (el.key() == "SpriteSnap")
				{
					value._spriteSnapExist = true;
					value._sheetName = el.value()["SheetName"].get<std::string>();
					value._spriteName = el.value()["SpriteName"].get<std::string>();
				}
				else if (el.key() == "PositionSnap")
				{
					value._positionSnapExist = true;
					value._positionSnap.x = el.value()["X"].get<double>();
					value._positionSnap.y = el.value()["Y"].get<double>();
				}
				else if (el.key() == "RotateSnap")
				{
					value._rotateSnapExist = true;
					value._rotateSnap.x = el.value()["X"].get<double>();
					value._rotateSnap.y = el.value()["Y"].get<double>();
				}
				else if (el.key() == "ScaleSnap")
				{
					value._scaleSnapExist = true;
					value._scaleSnap.x = el.value()["X"].get<double>();
					value._scaleSnap.y = el.value()["Y"].get<double>();
				}
				else if (el.key() == "EventSnap")
				{
					value._eventSnapExist = true;
					value._component = el.value()["Component"].get<std::string>();
					value._event = el.value()["Event"].get<std::string>();
				}
			}
		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const SnapData& snapData)
		{
			j["ObjectName"] = snapData._objectName;
			if (snapData._spriteSnapExist)
			{
				j["SpriteSnap"]["SheetName"] = snapData._sheetName;
				j["SpriteSnap"]["SpriteName"] = snapData._spriteName;
			}
			if (snapData._positionSnapExist)
			{
				j["PositionSnap"]["X"] = snapData._positionSnap.x;
				j["PositionSnap"]["Y"] = snapData._positionSnap.y;
			}
			if (snapData._rotateSnapExist)
			{
				j["RotateSnap"]["X"] = snapData._rotateSnap.x;
				j["RotateSnap"]["Y"] = snapData._rotateSnap.y;
			}
			if (snapData._scaleSnapExist)
			{
				j["ScaleSnap"]["X"] = snapData._scaleSnap.x;
				j["ScaleSnap"]["Y"] = snapData._scaleSnap.y;
			}
			if (snapData._eventSnapExist)
			{
				j["EventSnap"]["Component"] = snapData._component;
				j["EventSnap"]["Event"] = snapData._event;
			}
		}
	};
	template <>
	struct adl_serializer<AnimationSnap>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, AnimationSnap& value)
		{
			value._time = j["Time"].get<float>();
			value._snapDatas = j["SnapDatas"].get<std::vector<SnapData>>();
		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const AnimationSnap& animationSnap)
		{
			j["Time"] = animationSnap._time;
			j["SnapDatas"] = json(animationSnap._snapDatas);
		}
	};
}