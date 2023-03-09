#pragma once
#include "Event.h"

class IObserver
{
public:
	virtual ~IObserver() {}
	virtual void onNotify(Event event) = 0;
};