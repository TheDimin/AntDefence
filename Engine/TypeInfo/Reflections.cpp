#include "Reflections.h"
#include <iostream>

void Reflect::Reflections::RegisterClass(Type* type)
{
	if (type == nullptr)
	{
		printf("[Reflections] Attempted to register a nullptr class");
		return;
	}

	if (!reflectedClasses.empty() && reflectedClasses.find(type->GetName()) != reflectedClasses.end())
	{
		printf("[Reflections] Failed to register class '%s'\n",type->GetName().c_str());
		return;
	}

	printf("[Reflections] Attempt at registering class '%s'\n", type->GetName().c_str());
	reflectedClasses.emplace(type->GetName(), type);
}

Reflect::Type* Reflect::Reflections::FindType(std::string name)
{

	auto it = reflectedClasses.find(name);
	if (it == reflectedClasses.end())
	{
		printf("[Reflections] Failed to find class '%s'\n", name.c_str());
		return nullptr;
	}

	return it->second.get();
}
