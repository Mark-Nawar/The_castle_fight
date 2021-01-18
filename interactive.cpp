#include "interactive.h"
#include "Battle.h"

interactive::interactive(Battle* pApp) : action(pApp)
{

}

void interactive::Execute()
{
	bool flag = true;
	int time = 0;
	pManager->LOAD();
	while (flag)
	{
		flag = pManager->stepbystep_and_interactive_battle();
		pManager->getgui()->ResetDrawingList();
		pManager->getgui()->waitForClick();
	}
	pManager->Save();
	pManager->getgui()->waitForClick();
	if (pManager->castlelose() == true)
	{
		pManager->getgui()->PrintMessage("Extraordinarily well-trained soliders, you got the castle down");
		pManager->getgui()->waitForClick();

	}
	else if (pManager->battleDraw())
	{
		pManager->getgui()->PrintMessage("Fight is Over, Draw. Peace");
		pManager->getgui()->waitForClick();
	}
	else
	{
		pManager->getgui()->PrintMessage("Mighty Castle, All enemies killed");
		pManager->getgui()->waitForClick();

	}
	
	
}

interactive::~interactive()
{
}
