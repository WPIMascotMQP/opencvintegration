#include <iostream>

#include "BehaviourTree.h"
#include "Controller.h"
#include "Sequence.h"
#include "MasterControlLoop.h"
#include "MoveBackDown.h"
#include "MoveFrontLeft.h"
#include "MoveUpRight.h"
#include "Parallel.h"
#include "Utility.h"
#include "UtilityDec.h"
#include "SUtilityDec.h"
#include "PUtilityDec.h"
#include "VisualProcessor.h"

extern std::vector<Behaviour*> currentBehaviours;

int main(int argc, char* argv[]) {
	BehaviourTree bt;
	Sequence sq;
	Parallel pl;
	Utility ut;

	SUtilityDec sud;
	PUtilityDec pud;

	MoveUpRight mur;
	MoveFrontLeft mfl;
	MoveBackDown mbd;

	VisualProcessor vp(0);

	pl.addChild(&mur);
	pl.addChild(&mfl);
	pl.addChild(&mbd);
	pl.reset();

	sq.addChild(&mur);
	sq.addChild(&mfl);
	sq.addChild(&mbd);
	sq.reset();

	sud.setChild(&sq);
	pud.setChild(&pl);
	ut.addChild(&sud);
	ut.addChild(&pud);

	bt.setRoot(&ut);

	currentBehaviours.push_back(&bt);
	Controller* controller = &Node::controller;
	SensorData* data = &Node::data;

	vp.startThread();

	std::string input;
	std::getline(std::cin, input);
	data->setInput(input);
	while (input != "x") {
		executeBehaviours(input);
		controller->execute();

		std::getline(std::cin, input);
		data->setInput(input);
	}
	vp.killThread();
}

void executeBehaviours(std::string input) {
	std::vector<Behaviour*>::iterator itr;
	for (itr = currentBehaviours.begin(); itr < currentBehaviours.end(); itr++) {
		Behaviour* behaviour = *itr;
		Status* result = input.find("f") == std::string::npos ? 
			behaviour->executeP(Status().setSuccess()) : behaviour->executeP(Status().setFailure());
		currentBehaviours.erase(itr);
	}
}
