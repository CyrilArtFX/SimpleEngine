#pragma once
#include "IObserver.h"
#include <map>

enum Achievement
{
	ACHIEVEMENT_SPRING_ARM,
	ACHIEVEMENT_CINEMATIC_CAMERA,
	ACHIEVEMENT_FAR_FROM_HOME
};

class Achievements : public IObserver
{
public:
	Achievements() {}
	virtual void onNotify(Event event);

private:
	void unlockAchievement(Achievement achievement);

	std::map<Achievement, bool> unlockedAchievements{ 
		{ACHIEVEMENT_SPRING_ARM, false}, 
		{ACHIEVEMENT_CINEMATIC_CAMERA, false}, 
		{ACHIEVEMENT_FAR_FROM_HOME, false} };
};

