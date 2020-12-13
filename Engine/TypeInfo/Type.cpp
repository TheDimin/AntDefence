#include "Type.h"
#include "Reflections.h"

namespace Reflect
{
	Type::Type(void(*init)())
	{
		init();
	}

	void TypeRegister::RegisterProperty(Type* type, std::string name, size_t offset, std::string proptype)
	{
		type->props.insert(type->props.begin(), std::pair<std::string, std::unique_ptr<PropInfo>>(name, std::make_unique<PropInfo>(name, offset, proptype)));
	}


	void TypeRegister::SetInfo(Type* type, std::string Name, void* CDO)
	{
		type->name = Name;
		//type->CDO = CDO;
		Reflections::Get()->RegisterClass(type);
	}

	std::string Type::GetName()
	{
		return name;
	}

	std::vector<PropInfo*> Type::GetProps()
	{
		std::vector<PropInfo*> values;
		//https://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap-and-put-them-into-a-vector
		for (std::map<std::string, std::unique_ptr<PropInfo>>::iterator it = props.begin(); it != props.end(); ++it) {
			values.push_back(it->second.get());
		}
		return values;
	}

	PropInfo* Type::FindProp(const std::string PropName)
	{
		auto it = props.find(PropName);

		assert(it != props.end()); // failed to find prop

		return it->second.get();
	}

	Type::Type()
	{
		props.clear();
	}
}
