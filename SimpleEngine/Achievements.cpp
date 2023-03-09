#include "Achievements.h"
#include "Log.h"

void Achievements::onNotify(Event event)
{
	switch (event)
	{
		case SPRING_ARM_USED:
			unlockAchievement(ACHIEVEMENT_SPRING_ARM);
		break;

		case CINEMATIC_CAMERA:
			unlockAchievement(ACHIEVEMENT_CINEMATIC_CAMERA);
		break;

		case FAR_FROM_HOME:
			unlockAchievement(ACHIEVEMENT_FAR_FROM_HOME);
		break;
	}
}

void Achievements::unlockAchievement(Achievement achievement)
{
	if (unlockedAchievements[achievement]) return;

	switch (achievement)
	{
		case ACHIEVEMENT_SPRING_ARM:
			Log::info("Achievement : Spring Arm   -   Yeah there is spring arm collision in this game ! Was fun to do it.");
		break;

		case ACHIEVEMENT_CINEMATIC_CAMERA:
			Log::info("Achievement : Cinematic Camera   -   By far the camera with the best view.");
		break;

		case ACHIEVEMENT_FAR_FROM_HOME:
			Log::info("Achievement : Far From Home   -   Why did you went so far from the spawn ? You play a car floating in the air.");
		break;
	}

	unlockedAchievements[achievement] = true;
}
