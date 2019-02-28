/*
 * RobotController.h
 * This class act as a supervisor for the Robots.
 * It handles the collective behavior of the robots and the synchronization between them.
 * The individual Robot object should be created via the RobotControlller.
 * If it is not the case, the robot can be added afterward to the robotController via the addRobot(Robot& robot) method.
 *  Created on: 28 sept. 2018
 *      Author: lucie
 */

#ifndef ROBOTCONTROLLER_H_
#define ROBOTCONTROLLER_H_

#include "Robot.h"

/*----------------------TODOO
 * create a function to assign a robot to a controller after the robot has been created
 * */

enum direction {CLOCK_WISE, COUNTER_CLOCK_WISE};

class RobotController {
public:
	RobotController();
	RobotController(config::sController controllerParam, config::sRobot robotParam, b2Body* terrain, double m_to_px = 0);
	virtual ~RobotController();

	void setNbRobots(int nb_robots);
	void setScale(double m_to_px);

	void create(config::sController controllerParam, config::sRobot robotParam, b2Body* terrain, double m_to_px = 0);

	/**
	 * The function create a new robot object and add it to the m_robotVector
	 * @param 	world pointer on the box2D world object
	 * @param 	posX initial x position of the robot in meters
	 * @param 	posY initial y position of the robot in meters
	 * @param 	angle initial angle of the robot in rad
	 * @param 	delay number of iteration before the robot is able to move for the first time
	 * @return 	true if the robot has been created and added to m_robotVector, false otherwise
	 * */
	bool createRobot(b2World* world, int delay, double posX, double posY, double angle = 0);

	/**
	 * @param 	pos_id the robot position in the m_robotVector Robot vector containing all the robots
	 * belonging to the RobotController. The pos_id starts at 0
	 * Be careful pos_id does not necessarily match the robot id
	 * @return 	a pointer on the robot object */
	Robot* getRobot(int pos_id);
	/**
	 * @param 	id is the robot unique id
	 * Be careful, it does not necessarily match the robot position within the robots' vector.
	 * @	return a pointer on the robot object */
	Robot* getRobotWithId(int id);

	/**
	 * The function draws all the robots of the Robot controller on the SFML window
	 * @param 	window is the SFML window
	 * @param 	m_to_px is the conversion factor from m to pixels, it is generally obtained via the terrain
	 */
	void drawRobots(sf::RenderWindow& window, double m_to_px);

	/**
	 * This is the function used in the contactListener.
	 * It determines if a contact must lead to a grip creation,
	 * call the Robot::gripSide(b2Contact* contact, b2Body* otherBody, double m_to_px) when a grip has to be created
	 * @param  contact is the Box2D contact object
	 * @update 	Robot::m_state for contacted robots
	 * @update 	Robot::m_leftGripJointDef or Robot::m_rightGripJointDef for future gripping robots
	 * @update 	Robot::m_contact for future gripping robots
	 */
	void findContactRobots(b2Contact* contact);

	/**
	 * Takes the robot as parameter and create a new grip in the box2D world if the robot.isContact() is true
	 * @param 	robot generally from the m_robotVector of the controller
	 * @update 	Robot::m_previousGripJoint and Robot::m_currentGripJoint for contacted robots
	 * @update 	Robot::m_contact by setting it to false once the joint has been created
	 */
	void createGripRobots(Robot& robot);

	/**
	 * Handle the waiting delay of the robots by decreasing it at each world step.
	 * When the delay is null, the robot.m_ready state is set to true
	 * @param 	robot generally from the m_robotVector of the controller
	 * @update	Robot::m_ready is set to true when Robot::m_delay is null
	 * @update	Robot::m_delay is decreased otherwise
	 */
	void wait_delay(Robot& robot);

	/**
	 * Run a step of the simulation.
	 * @param 	end_x is the position of the end of the simulation world
	 * 			it generally correspond to the end of the window.
	 * 			above this position the robot is destroyed.
	 */
	void step(double end_x);

	/**
	 * Function used to set the state of a specific robot
	 * @param 	robot is the Robot object
	 * @param	robotState can be either WALK or BRIDGE
	 * @update	Robot::m_moving, Robot::m_state, Robot::m_contact and Robot::m_delay
	 */
	void setRobotState(Robot& robot,  e_state robotState);

	/**
	 * Invert the moving side of the robot
	 * @param 	robot is the Robot object
	 * @update	Robot::m_movingSide: become LEFT if it was RIGHT and vice versa
	 */
	void invertMovingWheel(Robot& robot);

	/**
	 * Remove from the world and destroy a given Box2D joint. This joint is one of a robot gripper
	 * @param 	s is either LEFT or RIGHT
	 * @update	Robot::m_previousGripJoint and Robot::m_currentGripJoint
	 */
	void destroyJoints(Robot& robot, side s);

	/**
	 * Add/Remove a robot to the controller
	 */
	void addRobot(Robot* robot);
	void removeRobot();

	/**
	 * Check if a robot with a given unique id is outside the world.
	 * If it is the robot is removed from the world and destroyed
	 * @param 	end_x corresponds to the end of the world
	 * @param	id is the unique id of the robot, can be obtained with robot.getID()
	 */
	void robotOut(double end_x, int id);

	/**
	 * Check if the robot is grabbed by any other robot of the controller
	 * @return true if the robot is grabbed, false otherwise
	 */
	bool checkGrabbed(Robot& robot);

	/**
	 * Get the time required to obtain a stable bridge
	 * @return the simulated time
	 */
	double getStabilizationTime();

	/**
	 * Get the time required to obtain a stable bridge
	 * @return the simulated time
	 */
	double getDissolutionTime();

	/**
	 * Check if a stable bridge has been obtained. To do so, we compare the time the last robot entered the bridge with the stability condition.
	 * The time the last robot has been obtained is stocked inside m_stableTime.
	 * m_stableTime is updated everytime a robot enter the bridge state via a call of the function setRobotState(Robot& robot,  e_state robotState);
	 * @return true if a stable bridge is obtained, false otherwise
	 */
	bool isBridgeStable();

	/**
	 * Check if the bridge has been dissolved. We consider that if only one robot is remained, the dissolution has been reached.
	 * @return true if the dissolution of the bridge is obtained, false otherwise
	 */
	bool isBridgeDissolved();

	/**
	 * Set if a stable bridge has been obtained
	 * @param stable is either true if the stability has been reached or false
	 * @update m_isStable
	 */
	void setBridgeStability(bool stable);

	/**
	 * Get the number of robots of the robotController under a certain state
	 * @param s is the considered state, can be either BRIDGE or WALK
	 * @return the number of robot in this given state
	 */
	int getNbRobots(e_state s);

	/**
	 * Get the number of active robots of the robotController.
	 * ie the number of robots in the world window
	 * @return the number of active robots
	 */
	int getNbActiveRobots();

	/**
	 * Determine if a robot is pushing after the pushing delay has been reached
	 * by determining if the robot is touching another object.
	 * This contact has to be on the moving side.
	 * This is checked by calling the function Robot::contactOnGripSide(b2Contact* contact).
	 * In addition, the robot must have run a higher angle than m_angle_min to avoid gripping the exact previous position
	 * @param r is the Robot to be checked when its delay corresponds to the pushing_delay, if no direct joint has been created
	 * @update Robot::m_delay, Robot::m_contact, Robot::m_leftGripJointDef, Robot::m_rightGripJointDef
	 * @return true if the robot is pushing, false otherwise
	 */
	bool robotPushing(Robot& r);

	/**
	 * This function is used to help determine if the robots are stacking.
	 * It does so by checking if there is a robot located before the given position posX.
	 * @param r is the Robot to be checked
	 * @param posX is the superior limit of the position one wants to check
	 * @return true if the robot is located before posX, false otherwise
	 */
	bool robotStacking(Robot* r, float posX);

	int getNbRobotsBlocked();

	bool m_bridgeEntry = false;


private:
	std::vector<Robot*> m_robotVector;
	std::vector<int> m_robotToDestroy;
	int m_nbRobots = 0;
	int m_currentIt = 0;
	int m_idLastRobot = 0; // id of the last robot that entered the bridge state
	int m_nbRobInBridge = 0;
	double m_stableTime = 0;
	bool m_isStable = false;
	bool m_isDissolved = false;
	double m_dissolutionTime = 0;
	double m_angle_min= 0; // PI/8
	b2Body* m_terrainBody=nullptr;

//
	config::sController m_controllerParam;
	config::sRobot m_robotParam;

//	const int m_DELAY_BRIDGE_UP = 30;
//	const int m_DELAY_BRIDGE_DOWN = 300;
//	const int m_DELAY_WALK = 30;
//	const int m_TIME_TO_MOVE =300;
//	const int m_ANGLE_LIM = PI/2;
	int m_M_TO_PX;


};



#endif /* ROBOTCONTROLLER_H_ */
