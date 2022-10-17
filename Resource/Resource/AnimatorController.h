#pragma once
#include "AnimationClip.h"

/// <summary>
///	Link(Int, Boolean, Float)
/// 조건(condition), 조건값(value), 비교할 파라미터 이름(parameterName)를 가지고 있는 구조체
/// CheckCondition 에서 input이 condition과 value에 따라 true false를 반환
/// </summary>
struct BooleanLink
{
	enum class BooleanCondition
	{
		Equal,
		NotEqual
	};

	BooleanLink(string name, bool value, int condition)
	{
		_parameterName = name;
		_value = value;
		_condition = (BooleanCondition)condition;
	}

	string _parameterName;
	bool _value;
	BooleanCondition _condition;

	bool CheckCondition(bool input)
	{
		switch (_condition)
		{
			case BooleanCondition::Equal:
			{
				if (input == _value) return true;
				else return false;
				break;
			}
			case BooleanCondition::NotEqual:
			{
				if (input != _value) return true;
				else return false;
				break;
			}
			default:
			{
				return false;
			}
		}
	}
};

struct IntLink
{
	enum class IntCondition
	{
		Greater,
		Less,
		Equal,
		NotEqual
	};

	IntLink(string name, int value, int condition)
	{
		_parameterName = name;
		_value = value;
		_condition = (IntCondition)condition;
	}

	string _parameterName;
	int _value;
	IntCondition _condition;

	bool CheckCondition(int input)
	{
		switch (_condition)
		{
			case IntCondition::Greater:
			{
				if (input > _value) return true;
				else return false;
				break;
			}
			case IntCondition::Less:
			{
				if (input < _value) return true;
				else return false;
				break;
			}
			case IntCondition::Equal:
			{
				if (input == _value) return true;
				else return false;
				break;
			}
			case IntCondition::NotEqual:
			{
				if (input != _value) return true;
				else return false;
				break;
			}
			default:
			{
				return false;
			}
		}
	}
};

struct FloatLink
{
	enum class FloatCondition
	{
		Greater,
		Less
	};

	FloatLink(string name, float value, int condition)
	{
		_parameterName = name;
		_value = value;
		_condition = (FloatCondition)condition;
	}

	string _parameterName;
	float _value;
	FloatCondition _condition;

	bool CheckCondition(float input)
	{
		switch (_condition)
		{
			case FloatCondition::Greater:
			{
				if (input > _value) return true;
				else return false;
				break;
			}
			case FloatCondition::Less:
			{
				if(input < _value) return true;
				else return false;
				break;
			}
			default:
			{
				return false;
			}
		}
	}
};

/// <summary>
/// 현재 재생되어야할 애니메이션을 업데이트 해주고
/// FSM을 이용하여 현재 재생되야할 애니메이션 클립을 바꿔줌
/// </summary>
struct AnimationClipNode
{
	// jsonData
	// 노드가 가져야할 애니메이션클립의 이름
	string _animationClipName;
	// 항상 참인 링크
	vector<string> _anyLinkNodes;
	// 링크와 연결된 클립 이름
	vector<pair<IntLink, string>> _intLinkNodes;
	vector<pair<BooleanLink, string>> _booleanLinkNodes;
	vector<pair<FloatLink, string>> _floatLinkNodes;
	vector<pair<string, string>> _triggerLinkNodes;

	// 애니메이션 클립 포인터
	AnimationClip* _animationClip = nullptr;
	// 이 링크가 있다면 애니메이션 클립이 끝나고 바로 넘어감
	vector<AnimationClipNode*> _anyLinks;
	// 파라미터 조건과 다음 애니메이션 노드주소
	vector<pair<IntLink, AnimationClipNode*>> _intLinks;
	vector<pair<BooleanLink, AnimationClipNode*>> _booleanLinks;
	vector<pair<FloatLink, AnimationClipNode*>> _floatLinks;
	vector<pair<string, AnimationClipNode*>> _triggerLinks;

	void AddIntLink(IntLink link, AnimationClipNode* node)
	{
		_intLinks.push_back({ link, node });
	}

	void AddBooleanLink(BooleanLink link, AnimationClipNode* node)
	{
		_booleanLinks.push_back({link, node});
	}

	void AddFloatLink(FloatLink link, AnimationClipNode* node)
	{
		_floatLinks.push_back({ link, node });
	}

	void AddTriggerLink(string link, AnimationClipNode* node)
	{
		_triggerLinks.push_back({ link, node });
	}

	void AddAnyLink(AnimationClipNode* node)
	{
		_anyLinks.push_back(node);
	}

	void SetAnimationClip(AnimationClip* animationClip)
	{
		_animationClip = animationClip;
	}
};

class AnimatorController
{
public:
	AnimatorController();
	~AnimatorController();

public:
	string _metaFilePath;
	string _animatorControllerName;
	/// 파라미터 이름과 값
	/// 상태머신을 돌리기 위한 파라미터
	map<string, int> _intParameter;
	map<string, bool> _booleanParameter;
	map<string, float> _floatParameter;
	map<string, bool> _triggerParameter;

	// 애니메이션 클립
	vector<AnimationClip*> _animationClip;
	
	// 애니메이션 클립 노드
	map<string, AnimationClipNode> _nodes;
	
	// 현재 애니메이션 클립
	AnimationClipNode* _currAnimationNode= nullptr;
	AnimationClipNode _anyStateNode;
public:
	/// <summary>
	/// 초기화 작업
	/// </summary>
	void Init();

	void SetStartNode(string nodeName);
	/// <summary>
	/// 애니메이션 클립들을 리소스 매니저로부터 가져옴
	/// </summary>
	void LoadAnimationClips();

	/// <summary>
	/// 파라미터 추가
	/// </summary>
	/// <param name="name">파라미터 이름</param>
	void AddIntParameter(string name);
	void AddFloatParameter(string name);
	void AddBooleanParameter(string name);
	void AddTriggerParameter(string name);
	
	/// <summary>
	/// 애니메이션 적용될 오브젝트들을 연결 해줌
	/// </summary>
	/// <param name="objects">오브젝트의 이름을 키값으로 오브젝트 포인터가 담긴 map</param>
	void AttachObject(map<string, GameObject*>& objects);

	/// <summary>
	/// AnimationClip를 추가
	/// </summary>
	void AddAnimationClip(AnimationClip* animationClip);

	/// <summary>
	/// 애니메이션클립 노드들을 추가
	/// </summary>
	void AddAnimationClipNode(AnimationClipNode node);

	/// <summary>
	/// FSM로 애니메이션 클립을 교체
	/// </summary>
	void Update(float& currTimer, int& currFrame);

	/// <summary>
	/// 현재 노드의 파라미터를 비교하며 조건에 충족하면 연결된 노드로 이동 시켜줌
	/// </summary>
	void CheckState(float& currTimer, int& currFrame);

	/// <summary>
	/// AnyState와 연결된 노드를 체크하기 위해 현재 노드의 링크들을 체크하기전에 먼저 체크함
	/// </summary>
	bool CheckAnyState(float& currTimer, int& currFrame);

	/// <summary>
	/// 프레임 종료후 트리거 파라미터를 다시 false로 변환
	/// </summary>
	void InitTrigger();
};

namespace nlohmann
{
	template <>
	struct adl_serializer<AnimationClipNode>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, AnimationClipNode& value)
		{
			// json으로 가지고 있어야하는것
			// 어떤 애니메이션 클립 노드인지
			// 파라미터 조건과 다음 애니메이션 노드주소
			value._animationClipName = j["ClipName"].get<std::string>();
			for (auto el : j["Links"].items())
			{
				int type = el.value()["Type"];
				switch (el.value()["Type"].get<int>())
				{
					case 0: // IntLink
					{
						value._intLinkNodes.push_back({
							IntLink(
								el.value()["ParameterName"].get<std::string>(),
								el.value()["Value"].get<int>(),
								el.value()["Condition"].get<int>()
							),
							el.value()["LinkedNode"].get<std::string>()
							});
						break;
					}
					case 1: // FloatLink
					{
						value._floatLinkNodes.push_back({
							FloatLink(
								el.value()["ParameterName"].get<std::string>(),
								el.value()["Value"].get<float>(),
								el.value()["Condition"].get<int>()
							),
							el.value()["LinkedNode"].get<std::string>()
							});
						break;
					}
					case 2: // BooleanLink
					{
						value._booleanLinkNodes.push_back({
							BooleanLink(
								el.value()["ParameterName"].get<std::string>(),
								el.value()["Value"].get<bool>(),
								el.value()["Condition"].get<int>()
							),
							el.value()["LinkedNode"].get<std::string>()
							});
						break;
					}
					case 3:
					{
						value._triggerLinkNodes.push_back({
								el.value()["ParameterName"].get<std::string>(),
								el.value()["LinkedNode"].get<std::string>()
							});
						break;
					}
					case 4:
					{
						value._anyLinkNodes.push_back({
								el.value()["LinkedNode"].get<std::string>()
							});
					}
				}
			}
		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const AnimationClipNode& animationClipNode)
		{
			j["ClipName"] = animationClipNode._animationClipName;

			for (auto iter : animationClipNode._intLinkNodes)
			{
				json temp;
				temp["Type"] = 0;
				temp["ParameterName"] = iter.first._parameterName;
				temp["Value"] = iter.first._value;
				temp["Condition"] = (int)iter.first._condition;
				temp["LinkedNode"] = iter.second;
				j["Links"].push_back(temp);
			}

			for (auto iter : animationClipNode._floatLinkNodes)
			{
				json temp;
				temp["Type"] = 1;
				temp["ParameterName"] = iter.first._parameterName;
				temp["Value"] = iter.first._value;
				temp["Condition"] = (int)iter.first._condition;
				temp["LinkedNode"] = iter.second;
				j["Links"].push_back(temp);
			}

			for (auto iter : animationClipNode._booleanLinkNodes)
			{
				json temp;
				temp["Type"] = 2;
				temp["ParameterName"] = iter.first._parameterName;
				temp["Value"] = iter.first._value;
				temp["Condition"] = (int)iter.first._condition;
				temp["LinkedNode"] = iter.second;
				j["Links"].push_back(temp);
			}

			for (auto iter : animationClipNode._triggerLinkNodes)
			{
				json temp;
				temp["Type"] = 2;
				temp["ParameterName"] = iter.first;
				temp["LinkedNode"] = iter.second;
				j["Links"].push_back(temp);
			}

			for (auto iter : animationClipNode._anyLinkNodes)
			{
				json temp;
				temp["Type"] = 4;
				temp["LinkedNode"] = iter;
				j["Links"].push_back(temp);
			}
		}
	};
	template <>
	struct adl_serializer<AnimatorController>
	{
		// note: the return type is no longer 'void', and the method only takes
		// one argument
		static void from_json(const json& j, AnimatorController& value)
		{
			// json으로 가지고 있어야하는것
			// int, float, boolean 파라미터의 이름, 초기값
			// map<string, int> _intParameter;
			// map<string, bool> _booleanParameter;
			// map<string, double> _floatParameter;
			// 
			// 애니메이션 클립들 => 파일 이름으로 받아야하나?
			// vector<AnimationClip*> _animationClip;
			//
			// 애니메이션 클립 노드 정보?? 그래프 방식으로 되어있음
			// 
			// vector<AnimationClipNode> _nodes;
			value._animatorControllerName = j["Name"].get<std::string>();
			value._intParameter = j["IntParameter"].get<map<string, int>>();
			value._floatParameter = j["FloatParameter"].get<map<string, float>>();
			value._booleanParameter = j["BooleanParameter"].get<map<string, bool>>();
			value._triggerParameter = j["TriggerParameter"].get<map<string, bool>>();
			value._anyStateNode = j["AnyStateNode"].get<AnimationClipNode>();
			value._nodes = j["Nodes"].get<map<string, AnimationClipNode>>();

		}

		// Here's the catch! You must provide a to_json method! Otherwise, you
		// will not be able to convert move_only_type to json, since you fully
		// specialized adl_serializer on that type
		static void to_json(json& j, const AnimatorController& animatorController)
		{
			j["Name"] = animatorController._animatorControllerName;
			j["IntParameter"] = json(animatorController._intParameter);
			j["FloatParameter"] = json(animatorController._floatParameter);
			j["BooleanParameter"] = json(animatorController._booleanParameter);
			j["TriggerParameter"] = json(animatorController._triggerParameter);
			j["AnyStateNode"] = json(animatorController._anyStateNode);
			j["Nodes"] = json(animatorController._nodes);
		}
	};
}