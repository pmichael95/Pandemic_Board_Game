#pragma once

#include "Subject.h"

class Subject;

class Observer {
	public:

		// Destructor
		~Observer();

		// Update Function
		virtual void Update() = 0;

	protected:

		// Constructor
		Observer();
};