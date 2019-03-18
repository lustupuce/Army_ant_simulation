/*
 * robot.h
 *
 *  Created on: 26 sept. 2018
 *      Author: lucie
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <math.h>

#include "constants.h"
#include "Config.h"
/*----------------------TODOO
 * create a function to assign a robot to a controller after the robot has been created
 * */

enum e_state {WALK, BRIDGE};
enum side {RIGHT, LEFT};

class Robot {

public:
	Robot();
	Robot(b2World* world, config::sRobot robotParameters, double posX, double posY, double angle = 0);
	virtual ~Robot();

	/** Create the box2D body of the robot and attach it to the world
	 * @param world: box2D world defined in the main program
	 * @param robotParameters: structure containing the robot parameters: only the body length and speed have to be defined
	 * @param posX, posY : initial position of the robot in this world in meters
	 * @param angle : initial angle of the robot in this world in rad
	 * */
	void createBody(b2World* world, config::sRobot m_robotParameters, double posX, double posY, double angle = 0);

	/** Use SFML to to draw the body and joints on the window
	 * @param window: active SFML window
	 * @param m_to_pix is the conversion factor used to transform the meters to pixels
	 * */
	void drawBody(sf::RenderWindow& window, double m_to_pix);
	void drawJoint(sf::RenderWindow& window, double m_to_px);
	void drawGripJoint(sf::RenderWindow& window, double m_to_px);

	/** Three different methods to move the robot body in the clockwise direction,
	 * The speed is applied via the m_angularSpeed class member (except for the force
	 * The impulse method uses a proportional action to reach the angular target speed
	 * */
	void moveBodyWithMotor();
	void moveBodyWithForce();
	void moveBodyWithImpulse();

	/** Methods to control the motor rotation
	 * turnOffMotor disable the motor, it means that the rotation is freed
	 * blockMotorRotation keep the motor enable but set a rotation limit and the speed to 0 in order to block the rotation
	 * allowMotorRotation, remove the rotation limit and keep the motor active
	 * @param s is the motor side can take LEFT or RIGHT value
	 * */
	void turnOffMotor(side s);
	void blockMotorRotation(side s);
	void allowMotorRotation(side s);
	void limitMotorRotation(side s, double limit_angle_rad);

	/** Methods to access and set the current robot state
	 * @param state is the new robot state, can take three values WALK, BRIDGE_UP or BRIDGE_DOWN
	 * */
	void setState(e_state state);
	e_state getState();

	/** Methods to get the Box2D body parts that make the robot
	 * @param s is the side of the robot (relative to the robot referential), can be either LEFT or RIGHT
	 * getBody return a pointer on the body of the attach between the two wheels
	 * getWheel return a pointer on the box2D wheel on the s side
	 * */
	b2Body* getBody();
	b2Body* getWheel(side s);

	/** get the box2D definition of the prismatic joint used to grip,
	 * this definition can then be used to create the actual grip joint
	 * @param s is the side of the robot (relative to the robot referential), can be either LEFT or RIGHT
	 * */
	b2PrismaticJointDef getJointDef(side s);

	/** Create the grip joint definition as a Box2D prismatic joint definition object.
	 * gripGroundFromPos is used when one needs to create a static robot:
	 * It directly create the joint object without the intermediate definition.
	 * @param contact: box2D contact object usually obtained via the contact listener
	 * @param otherBody: box2D body in contact with the robot
	 * @param m_to_px: scale conversion between box2d and sfml coordinates, used to draw the contact point
	 * @update m_leftGripJointDef and m_rightGripJointDef depending on the contact side
	 * */
	void grip(b2Contact* contact, b2Body* otherBody, double m_to_px);
	void gripGroundFromPos();
	bool gripSide(b2Contact* contact, b2Body* otherBody, double m_to_px);


	bool contactOnGripSide(b2Contact* contact);

	/** Used in the contact listener to update the m_contact flag if the robot initiate the contact
	 * @update m_contact
	 * */
	void setContact(bool contact);
	/** @return true if the robot has just initiated a contact and didn't create a joint yet.
	 * */
	bool isContact();

	/** setter and getter of the delay m_delay parameter
	 * @param delay is the number of iteration needed to be able to turn the motors on again
	 * */
	void setDelay(int delay);
	int getDelay();

	/** Check if the robot is currently grabbing something (gripper on)
	 * @param side of the gripper can be either LEFT or RIGHT
	 * @return true if the gripper on the side is active
	 * */
	bool checkGripp(side s);

	/** Check if the robot is currently grabbed by another robot
	 * @return true if it is
	 * */
	bool isGrabbed();

	//void releaseGrip(b2World* world, b2Joint* gripJointDef);

	/** Methods to check and set the number of grip joints of the robot, this number should not exceed 1
	 * @param s is the side of the robot: can be either LEFT or RIGHT
	 * */
	int nbJoint(side s);
	void incrementNbJoint(side s);
	void resetNbJoint(side s);


	b2RevoluteJoint* getMotor(side s);

	void destroyBody();

	/**
	 * @return the body length of the robot in meter (and not pixels)
	 * */
	double getBodyLength();

	/**
	 * @set the rotational robot speed, if the moveBodyWithMotor is used, the speed is in rad/s
	 * */
	void setSpeed(double speed);

	/**
	 * @return true if the robot is ready to move, false otherwise
	 * */
	bool isReady();

	/**
	 * @return true if the robot is moving, false otherwise
	 * */
	bool isMoving();

	void setId(int id);
	int getId();

	b2Vec2 getPosition();
	double getAngle();

	side m_movingSide = RIGHT;
	bool m_ready = false;
	bool m_moving = false; //remplacer par test sur valeur de la vitesse (non nulle ou sup a un threshold ) ?
	bool m_start = true;
	bool m_pushing = false;
	bool m_isGrabbed = false;
	double m_referenceAngle = -PI ;
	double m_referenceAngleJoint = 0 ;
	e_state m_nextState;
	int m_bridgeAge = 0;
	int m_age = 0;
	int m_pushing_delay = 0;

	/**
	 * Pointers on the two possible gripping joints
	 * */
	b2PrismaticJoint* m_previousGripJoint = nullptr;
	b2PrismaticJoint* m_currentGripJoint = nullptr;


private:

	/*Speed parameters*/
	double m_angularSpeed = 2*PI;
	config::sRobot m_robotParameters;

	b2Body* m_robotBody;
	b2Body* m_leftWheel;
	b2Body* m_rightWheel;

	/**
	 * Pointers on the two wheel joints
	 * */
	b2RevoluteJoint* m_rightWheelMotor;
	b2RevoluteJoint* m_leftWheelMotor;

	e_state m_state;
	bool m_contact = false;
	b2PrismaticJointDef m_leftGripJointDef;
	b2PrismaticJointDef m_rightGripJointDef;
	int m_nbJointLeft = 0;
	int m_nbJointRight = 0;

	int m_delay = 60; // 60 fps => 60 = 1s de delay

	int m_id;

	sf::CircleShape m_shapeRight;
	sf::CircleShape m_shapeLeft;
	sf::CircleShape m_shape3;
	sf::Vertex m_normal[2];

	double m_M_TO_PX;
};

#endif /* ROBOT_H_ */
