#include "EngineGlobal.h"
#include "../template.h"


//#include "game.h"

//https://stackoverflow.com/questions/20157896/initializing-static-pointer-in-static-class
Tmpl8::Surface* EngineGlobal::debugScreen;

int EngineGlobal::GetWidth()
{
	return ScreenWidth;
}
int EngineGlobal::GetHeight()
{
	return ScreenHeight;
}

Tmpl8::Surface* EngineGlobal::GetDebugScreen()
{
	return debugScreen;
}

void EngineGlobal::SetDebugScreen(Tmpl8::Surface* Screen)
{
	debugScreen = Screen;
}