#pragma once
#include "../surface.h"
#include "json.hpp"

#if _DEBUG
#define PATH_DEBUG //Show debug info of path generation
#undef PATH_DEBUG

#define STATE_DEBUG //Enable for state debug info
#undef STATE_DEBUG


#define SKIP_MAIN_MENU_DEBUG
//#undef SKIP_MAIN_MENU_DEBUG


#define UI_DEBUG //Extra debugging info for ui
#undef UI_DEBUG

#define UI_COLLISION_DEBUG //Collision debugging for ui
#undef UI_COLLISION_DEBUG
#endif


namespace nlohmann {
	//https://github.com/nlohmann/json/issues/975
	template <typename T>
	struct adl_serializer<std::unique_ptr<T>> {
		static void to_json(nlohmann::json& j, const std::unique_ptr<T>& opt) {
			if (opt.get()) {
				j = *opt.get();
			}
			else {
				j = nullptr;
			}
		}
		static void from_json(const nlohmann::json& j, std::unique_ptr<T>& value) {
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
		static void to_json(nlohmann::json& j, const Tmpl8::Sprite& opt) {
		}
		static void from_json(const nlohmann::json& j, Tmpl8::Sprite& value) {
			value = Tmpl8::Sprite(new Tmpl8::Surface(const_cast<char*>(j.get<std::string>().c_str())), 1);
		}
	};

}



class EngineGlobal
{
public:
	static int GetWidth();
	static int GetHeight();

	static Tmpl8::Surface* GetDebugScreen();
	static void SetDebugScreen(Tmpl8::Surface* screen);
private:
	static Tmpl8::Surface* debugScreen;
};


//Wish i could make these protected but cant find out how to make function be be called recursive (Friend relationship fails ?)
class IRenderable
{
public:
	virtual void Render(Tmpl8::Surface* surface) = 0;
};

class ITickable
{
public:
	virtual void Tick(float deltaTime) = 0;
};