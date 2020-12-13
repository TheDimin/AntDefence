#pragma once
#include <cassert>
#include <string>
#include <vcruntime_typeinfo.h>

namespace Reflect {
	class type_converter;


	class PropInfo
	{
	public:
		PropInfo(std::string propName, size_t propOffset, std::string type) : offset(propOffset), name(propName), type(type) {}
		~PropInfo() = default;

		template<class T>
		void TrySetValue(void* object, const T NewValue)
		{
			T* ptr = reinterpret_cast<T*>(reinterpret_cast<int>(object) + offset);

			assert(ptr != nullptr);

			*ptr = NewValue;
		}

		template<class  T>
		T* TryGetValue(void* object)
		{
			return static_cast<T*>(reinterpret_cast<void*>(offset + reinterpret_cast<size_t>(object)));
		}

		void* GetValue(void* object)
		{
			return reinterpret_cast<void*>(offset + reinterpret_cast<size_t>(object));
		}

	public:
		size_t offset;

		std::string name;
		std::string type;
	};
}