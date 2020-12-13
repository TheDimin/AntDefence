#pragma once
#include <map>
#include <memory>
#include <vector>

#include "PropInfo.h"

namespace Reflect
{
	class Type
	{
		friend class TypeRegister;
	public:
		explicit Type(void (*init)());

		std::string GetName();

		std::vector<PropInfo*> GetProps();
		PropInfo* FindProp(const std::string PropName);

		Type();

	private:
		bool constructed = false;
		std::string name = "";
		//PropName , PropInfo, for faster lookup
		std::map<std::string, std::unique_ptr<PropInfo>> props = std::map<std::string, std::unique_ptr<PropInfo>>();
		//void* CDO;
	};


	class TypeRegister
	{
	public:
		static void RegisterProperty(Type* type, std::string name, size_t prop, std::string proptype);
		static void SetInfo(Type* type, std::string Name, void* CDO);
	};
};