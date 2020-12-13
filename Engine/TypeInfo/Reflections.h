#pragma once
#include <map>
#include <string>
#include "Type.h"
#include "json.hpp"

// Inspired by https://preshing.com/20180116/a-primitive-reflection-system-in-cpp-part-1/

#define REFLECT_CLASS(classType)/*																\
	protected:																					\
		static Reflect::Type type;																\
		static void GenerateReflection();														\
	public:																						\
		friend void to_json(nlohmann::json& nlohmann_json_j, const classType& nlohmann_json_t);	\
		friend void from_json(const nlohmann::json& nlohmann_json_j, classType& go);			\
		classType();																			\
		static Reflect::Type* GetType() { return &type; };										*/



#define BEGIN_REFLECT(classType)/*																\
	classType::classType(){}																	\
	Reflect::Type classType::type{classType::GenerateReflection};								\
void to_json(nlohmann::json& nlohmann_json_j, const classType& nlohmann_json_t)					\
{																								\
	classType& go = const_cast<classType&>(nlohmann_json_t);									\
																								\
	for (auto& prop : classType::GetType()->GetProps()) {										\
		if (prop->type == "int") {																\
			nlohmann_json_j[prop->name] = *prop->TryGetValue<int>(&go);							\
		}																						\
		else if (prop->type == "std::string")													\
		{																						\
			nlohmann_json_j[prop->name] = *prop->TryGetValue<std::string>(&go);					\
		}																						\
		else { std::cout << "to_json Failed to find prop : '" << prop->name << "' of type: '" << prop->type << "'" << std::endl; }	\
	}																							\
}																								\
void from_json(const nlohmann::json& nlohmann_json_j, classType& go)							\
{																								\
	for (auto& prop : classType::GetType()->GetProps()) {										\
		if (prop->type == "int") {																\
			nlohmann_json_j.at(prop->name).get_to(*prop->TryGetValue<int>(&go));				\
		}																						\
		else if (prop->type == "std::string") {													\
			nlohmann_json_j.at(prop->name).get_to(*prop->TryGetValue<std::string>(&go));		\
		}																						\
		else { std::cout << "from_json Failed to find prop : '" << prop->name << "' of type: '" << prop->type << std::endl; }\
	}																							\
}																								\
																								\
	void classType::GenerateReflection() {														\
																								\
		using T = classType;																	\
		std::string className = #classType;														\
*/
#define PROPERTY_REFLECT(propDef,propType)/*														\
	Reflect::TypeRegister::RegisterProperty(&type,#propDef, offsetof(T,propDef),#propType);*/

#define FINISH_REFLECT()/*	Reflect::TypeRegister::SetInfo(&type,className,new T()); }*/	



namespace Reflect
{
	class Reflections
	{

		friend Type;
	public:
		Type* FindType(std::string name);
		static Reflections* Get()
		{
			static Reflections instance;
			return &instance;
		}


	protected:
		friend class TypeRegister;
		void RegisterClass(Type* type);

	private:
		std::map<std::string, std::unique_ptr<Type>> reflectedClasses;
	};


}
