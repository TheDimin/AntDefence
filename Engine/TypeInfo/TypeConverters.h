#pragma once
#include <string>
using namespace  std;

#define CreateSimpleConverter(TypeName)																	\
	class TypeName##_converter : public type_converter													\
	{																									\
	public:																								\
	TypeName##_converter(std::string name, int size) : type_converter(#TypeName,sizeof(TypeName)){}		\
	TypeName* GetValue(void* val)																	\
		{ return static_cast<TypeName*>(val);}															\
																										\
	};																									\
	template<>	static type_converter* getConverter<TypeName>(){										\
			static	TypeName##_converter converter = TypeName##_converter (#TypeName,sizeof(TypeName));	\
			return &converter;};										




namespace Reflect
{
	class type_converter
	{
	public:
		type_converter(std::string name, int size)
		{
			this->name = name;
			this->size = size;
		}
	public:
		std::string name;
		int size;
	};

	template<class T>
	static type_converter* getConverter() { return nullptr; };


	CreateSimpleConverter(int);


	//CreateSimpleConverter(bool);
	//CreateSimpleConverter(double);
	//CreateSimpleConverter(string);
}