#pragma once

#include "Observer.h"
#include <list>

using namespace std;

class Observer;

class Subject {
	public:

		//Default Constructor
		Subject();

		// Destructor
		~Subject();

		virtual void Attach(Observer* obv);		// Attaching an Observer
		virtual void Detach(Observer* obv);		// Detaching an Observer
		virtual void Notify();					// Notify the Observers when there is a change

	private:
		list<Observer*>* obv;					// List of Observers
};


