#include "Subject.h"

void Subject::addObserver(IObserver* observer)
{
	auto iter = std::find(begin(observers), end(observers), observer);
	if (iter == end(observers))
	{
		observers.push_back(observer);
	}
}

void Subject::removeObserver(IObserver* observer)
{
	auto iter = std::find(begin(observers), end(observers), observer);
	if (iter != end(observers))
	{
		std::iter_swap(iter, end(observers) - 1);
		observers.pop_back();
	}
}

void Subject::notify(Event event)
{
	for (auto iter : observers)
	{
		iter->onNotify(event);
	}
}
