#pragma once
#include "AnimationClip.h"

/// <summary>
///	Link(Int, Boolean, Float)
/// ����(condition), ���ǰ�(value), ���� �Ķ���� �̸�(parameterName)�� ������ �ִ� ����ü
/// CheckCondition ���� input�� condition�� value�� ���� true false�� ��ȯ
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
/// ���� ����Ǿ���� �ִϸ��̼��� ������Ʈ ���ְ�
/// FSM�� �̿��Ͽ� ���� ����Ǿ��� �ִϸ��̼� Ŭ���� �ٲ���
/// </summary>
struct AnimationClipNode
{
	// jsonData
	// ��尡 �������� �ִϸ��̼�Ŭ���� �̸�
	string _animationClipName;
	// �׻� ���� ��ũ
	vector<string> _anyLinkNodes;
	// ��ũ�� ����� Ŭ�� �̸�
	vector<pair<IntLink, string>> _intLinkNodes;
	vector<pair<BooleanLink, string>> _booleanLinkNodes;
	vector<pair<FloatLink, string>> _floatLinkNodes;
	vector<pair<string, string>> _triggerLinkNodes;

	// �ִϸ��̼� Ŭ�� ������
	AnimationClip* _animationClip = nullptr;
	// �� ��ũ�� �ִٸ� �ִϸ��̼� Ŭ���� ������ �ٷ� �Ѿ
	vector<AnimationClipNode*> _anyLinks;
	// �Ķ���� ���ǰ� ���� �ִϸ��̼� ����ּ�
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
	/// �Ķ���� �̸��� ��
	/// ���¸ӽ��� ������ ���� �Ķ����
	map<string, int> _intParameter;
	map<string, bool> _booleanParameter;
	map<string, float> _floatParameter;
	map<string, bool> _triggerParameter;

	// �ִϸ��̼� Ŭ��
	vector<AnimationClip*> _animationClip;
	
	// �ִϸ��̼� Ŭ�� ���
	map<string, AnimationClipNode> _nodes;
	
	// ���� �ִϸ��̼� Ŭ��
	AnimationClipNode* _currAnimationNode= nullptr;
	AnimationClipNode _anyStateNode;
public:
	/// <summary>
	/// �ʱ�ȭ �۾�
	/// </summary>
	void Init();

	void SetStartNode(string nodeName);
	/// <summary>
	/// �ִϸ��̼� Ŭ������ ���ҽ� �Ŵ����κ��� ������
	/// </summary>
	void LoadAnimationClips();

	/// <summary>
	/// �Ķ���� �߰�
	/// </summary>
	/// <param name="name">�Ķ���� �̸�</param>
	void AddIntParameter(string name);
	void AddFloatParameter(string name);
	void AddBooleanParameter(string name);
	void AddTriggerParameter(string name);
	
	/// <summary>
	/// �ִϸ��̼� ����� ������Ʈ���� ���� ����
	/// </summary>
	/// <param name="objects">������Ʈ�� �̸��� Ű������ ������Ʈ �����Ͱ� ��� map</param>
	void AttachObject(map<string, GameObject*>& objects);

	/// <summary>
	/// AnimationClip�� �߰�
	/// </summary>
	void AddAnimationClip(AnimationClip* animationClip);

	/// <summary>
	/// �ִϸ��̼�Ŭ�� ������ �߰�
	/// </summary>
	void AddAnimationClipNode(AnimationClipNode node);

	/// <summary>
	/// FSM�� �ִϸ��̼� Ŭ���� ��ü
	/// </summary>
	void Update(float& currTimer, int& currFrame);

	/// <summary>
	/// ���� ����� �Ķ���͸� ���ϸ� ���ǿ� �����ϸ� ����� ���� �̵� ������
	/// </summary>
	void CheckState(float& currTimer, int& currFrame);

	/// <summary>
	/// AnyState�� ����� ��带 üũ�ϱ� ���� ���� ����� ��ũ���� üũ�ϱ����� ���� üũ��
	/// </summary>
	bool CheckAnyState(float& currTimer, int& currFrame);

	/// <summary>
	/// ������ ������ Ʈ���� �Ķ���͸� �ٽ� false�� ��ȯ
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
			// json���� ������ �־���ϴ°�
			// � �ִϸ��̼� Ŭ�� �������
			// �Ķ���� ���ǰ� ���� �ִϸ��̼� ����ּ�
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
			// json���� ������ �־���ϴ°�
			// int, float, boolean �Ķ������ �̸�, �ʱⰪ
			// map<string, int> _intParameter;
			// map<string, bool> _booleanParameter;
			// map<string, double> _floatParameter;
			// 
			// �ִϸ��̼� Ŭ���� => ���� �̸����� �޾ƾ��ϳ�?
			// vector<AnimationClip*> _animationClip;
			//
			// �ִϸ��̼� Ŭ�� ��� ����?? �׷��� ������� �Ǿ�����
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