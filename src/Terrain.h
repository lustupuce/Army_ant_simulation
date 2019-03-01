/*
 * Terrain.h
 *
 *  Created on: 12 Feb 2019
 *      Author: lucie
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Config.h"

enum e_terrain_type {DEFAULT, V_TERRAIN, RAMP, BOX, V_STEPPER};

class Terrain {
public:
	Terrain();
	Terrain(b2World* world, sf::RenderWindow& window,  config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength=1);
	virtual ~Terrain();

	/*Default terrain is linear ground of width m_width located at m_height from the top of the window*/
	/** The function create MUST be called if the terrain object has been created via the default constructor (ex when created dynamically with new),
	 * otherwise no need to use it*/
	virtual void create(b2World* world, sf::RenderWindow& window, config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength);
	virtual void createBody(b2World* world);
	virtual void drawBody(sf::RenderWindow& window);
	virtual e_terrain_type getType();

	/** @return the position of the Top left corner of the V in the box2D world coordinates [m]*/
	virtual b2Vec2 getTopLeftCorner();
	/** @return the position of the Top right corner of the V in the box2D world coordinates [m]*/
	virtual b2Vec2 getTopRightCorner();
	/** @return the position of the bottom of the V in the box2D world coordinates [m]*/
	virtual b2Vec2 getBottom();

	double getVLength(){return 0;};

	b2Body* getBody();
	const double getScale();

protected:
	b2Body* m_groundBody;
	double m_bodyLength;
	double m_M_TO_PX;
	double m_width;
	double m_height;
	double m_runaway;
	double m_angle;
	double m_posY=2.5;

	config::sTerrain m_terrainParam;
};

#endif /* TERRAIN_H_ */
