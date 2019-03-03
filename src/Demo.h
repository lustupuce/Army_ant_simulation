/*
 * Demo.h
 *
 *  Created on: 6 Nov 2018
 *      Author: lucie
 */

#ifndef DEMO_H_
#define DEMO_H_
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "Robot.h"
#include "RobotController.h"
#include "World.h"
#include "Vterrain.h"
#include "V2BLTerrain.h"
#include "Ramp.h"
#include "VStepper.h"
#include <iostream>
#include <fstream>
#include "Config.h"

#include <random>


class MyContactListener_v2 : public b2ContactListener
{
public:
	MyContactListener_v2(RobotController& robotController):m_robotController(&robotController){};

	void BeginContact(b2Contact* contact){
//		printf("contact \n");
		m_robotController->findContactRobots(contact);
	}
	void EndContact(b2Contact* contact) {
	}

private:
	RobotController* m_robotController;
};

class Demo {
public:
	Demo(b2World* m_world, config::sConfig cfg);
	virtual ~Demo();
	void init();
	void demoLoop();
	RobotController getController();
	bool addRobotWithDelay();
	bool addRobotWithDistance();
	sf::RenderWindow* getWindow();
	double getBridgeHeight();
	double getNewPathLength();

	void captureInThread();
	void step();
	void createBridgeFile();

	void writeResultFile();
	void writeBridgeFile();

	void takeScreenshot(bool draw, int step);

private:
	sf::RenderWindow window;
//	b2Vec2 m_gravity = b2Vec2(0.f, 0.f);
	RobotController m_robotController;
	double m_to_px;
	Vterrain m_terrain;
	MyContactListener_v2* myContactListener;
	double m_it = 0;
	int m_nbRobots = 0;
	double m_elapsedTime = 0; // in seconds (real-time =/= from simulation time)
	double m_elapsedTimeDissolution = 0;
	double m_elapsedTimeBridge = 0;
	double m_length = 0;
	double m_height = 0;
	int m_currentIt = 0;
	int m_nbRobotsInBridge = 0;
	int m_nbRobotsInBridgeState = 0;

	bool m_stacking = false;

	b2Vec2 m_startP;
	b2Vec2 m_endP;

	config::sConfig m_config ;

//    sf::Texture m_tex;

	std::ofstream m_logFile;
	std::ofstream m_bridgeFile;

	// random device class instance, source of 'true' randomness for initializing random seed
	std::random_device m_rd;
	// Mersenne twister PRNG, initialized with seed from previous random device instance
	std::mt19937 m_gen;
	double m_seed;
	double m_std_dev=0.25; //0.25

//	std::default_random_engine gen;
	std::normal_distribution<double> m_gauss_delay;

protected:
	b2World* m_world = nullptr;
};


#endif /* DEMO_H_ */
