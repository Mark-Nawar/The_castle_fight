#include "silentmode.h"

#include "Battle.h"


silentmode::silentmode(Battle* pApp) : action(pApp)
{

}

void silentmode::Execute() {
	bool flag = true;
	int time = 0;
	pManager->LOAD();
	while (flag)
		flag = pManager->silent_mode();
	pManager->Save();
	if (pManager->castlelose())
	{
		pManager->getgui()->PrintMessage("Extraordinary Enemies , you got the castle down");
		pManager->getgui()->waitForClick();
	}
	else if (pManager->battleDraw())
	{
		pManager->getgui()->PrintMessage("Fight is Over, Draw. Peace");
		pManager->getgui()->waitForClick();
	}
	else
	{
		pManager->getgui()->PrintMessage("Mighty Towers, all the enemies are killed");
		pManager->getgui()->waitForClick();
	}
}

silentmode::~silentmode()
{
}
