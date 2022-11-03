#include "RaceTimer.h"
#include "Rectangle.h"
#include "Game.h"
#include "Log.h"

RaceTimer::RaceTimer() : Actor()
{
	checkpoint1 = new RectangleCollisionComponent(this);
	checkpoint2 = new RectangleCollisionComponent(this);
	checkpoint3 = new RectangleCollisionComponent(this);
	checkpoint1->setRectangle(Rectangle{ 930.0f, -100.0f, 140.0f, 50.0f });
	checkpoint2->setRectangle(Rectangle{ -100.0f, 25.0f, 50.0f, 140.0f });
	checkpoint3->setRectangle(Rectangle{ -250.0f, -575.0f, 50.0f, 140.0f });
}

void RaceTimer::updateActor(float dt)
{
	if (checkpointPassed < 3)
	{
		timer += dt;
	}
	switch (checkpointPassed)
	{
		case 0:
			if (checkpoint1->intersect(getGame().getPlayer()->getPosition()))
			{
				checkpointPassed++;
				Log::info("Checkpoint 1 passed !");
			}
			break;
		case 1:
			if (checkpoint2->intersect(getGame().getPlayer()->getPosition()))
			{
				checkpointPassed++;
				Log::info("Checkpoint 2 passed !");
			}
			break;
		case 2:
			if (checkpoint3->intersect(getGame().getPlayer()->getPosition()))
			{
				checkpointPassed++;
				Log::info("Race finished in " + std::to_string(timer) + " seconds !");
			}
			break;
	}
}