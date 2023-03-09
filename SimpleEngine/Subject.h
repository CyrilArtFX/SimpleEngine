#pragma once
#include "IObserver.h"
#include <vector>

class Subject
{
public:
	void addObserver(IObserver* observer);
	void removeObserver(IObserver* observer);

protected:
	void notify(Event event);

private:
	std::vector<IObserver*> observers;
};

