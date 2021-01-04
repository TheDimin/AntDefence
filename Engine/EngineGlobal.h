#pragma once
#include "../surface.h"
#include "TypeInfo/Reflections.h"

/*
#define JSON_Reflected(ClassName)								\
	void to_json(nlohmann::json& j, const ClassName& p) {		\
		ClassName& gnc = const_cast<ClassName&>(p);				\
		for (auto prop : ClassName::GetType()->GetProps())		\
		{														\
			if (prop->type == "int")							\
			{													\
				j[prop->name] = prop->TryGetValue<int>(&gnc);	\
			}													\
		}														\
	}															\
\
	void from_json(const nlohmann::json& j, GameObject& p) {	}\

*/

namespace nlohmann {
	//https://github.com/nlohmann/json/issues/975
	template <typename T>
	struct adl_serializer<std::unique_ptr<T>> {
		static void to_json(json& j, const std::unique_ptr<T>& opt) {
			if (opt.get()) {
				j = *opt.get();
			}
			else {
				j = nullptr;
			}
		}
		static void from_json(const json& j, std::unique_ptr<T>& value) {
			if (j.is_null()) value = nullptr;
			else if (value != nullptr)
			{
				j.get_to(*value.get());
			}
			else
			{
				value = std::make_unique<T>(j.get<T>());
			};
		}
	};
	template <>
	struct adl_serializer<Tmpl8::Sprite> {
		static void to_json(json& j, const Tmpl8::Sprite& opt) {
		}
		static void from_json(const json& j, Tmpl8::Sprite& value) {
			value = Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(j.get<std::string>().c_str())), 1);
		}

	};

}



class EngineGlobal
{
public:
	static int GetWidth();
	static int GetHeight();
	static void RegisterObject(void* newObject)
	{
		managedObjects.insert(managedObjects.begin(), std::unique_ptr<void*>(&newObject));
	}

private:
	static std::vector<std::unique_ptr<void*>> managedObjects;
};


class IRenderable
{
protected:
	friend class Game;
	friend class UiContainer;
	friend class Level;
	virtual void Render(Tmpl8::Surface* surface) = 0;
};

class ITickable
{
public:
	virtual ~ITickable() = default;
protected:
	virtual void Tick() = 0;
};