#include <iostream>

#include "Engine.h"
#include "Scene.h"


#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();
		g_engine.GetPS().Draw(g_engine.GetRenderer());
		g_engine.GetPS().Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().EndFrame();
	}
	g_engine.Shutdown();

	return 0;
}