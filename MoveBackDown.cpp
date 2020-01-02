#include "MoveBackDown.h"

#include "Calculator.h"
#include "Controller.h"
#include "Node.h"

/**
 CONSTRUCTOR
 Creates all of the actions and
 @return The MoveBackDown Object
*/
MoveBackDown::MoveBackDown() {
	state = fresh;
	Action *md = new Action(0, 0, -1);
	Action *mb = new Action(0, -1, 0);
	actions.push_back(md);
	actions.push_back(mb);
	actions.push_back(md);
	actions.push_back(mb);
	actions.push_back(md);
	actions.push_back(mb);
}

/**
 DECONSTRUCTOR
*/
MoveBackDown::~MoveBackDown() {

}

/**
 Node Execute as child fucntion
 Executes the function by generating the movements and
 putting them into the controller
 @return The status enum
*/status MoveBackDown::executeC() {
	state = running;
	verbose("Execute MoveBackDown");
	std::vector<Movement*>* movements = calculator.generateMovements(actions, this);
	controller.addMovements(movements);
	return state;
}

/**
 Node Execute as parent fucntion
 Executes the function by generating the movements and
 putting them into the controller
 @return The status enum
*/
status MoveBackDown::executeP(status stat) {
	if (state != running) {
		return not_running;
	}
	state = stat;
	verbose("Call MoveBackDown Parent");
	return parent->executeP(stat);
}


std::vector<Movement*> MoveBackDown::generateMovements() {
	std::vector<Movement*> movements;
	return movements;
}
