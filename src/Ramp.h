/*
 * Ramp.h
 *
 *  Created on: 12 Feb 2019
 *      Author: lucie
 */

#ifndef RAMP_H_
#define RAMP_H_

#include "Terrain.h"

class Ramp: public Terrain{
public:
	Ramp();
	Ramp(b2World* world, sf::RenderWindow& window,  config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength=1); // If want to define the dimension relatively to the body length
	virtual ~Ramp();

	void create(b2World* world, sf::RenderWindow& window,  config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength=1);
	void createBody(b2World* world);
	void drawBody(sf::RenderWindow& window);

	e_terrain_type getType();
//
	/** @return the position of the Top left corner of the V in the box2D world coordinates [m]*/
	b2Vec2 getTopLeftCorner();
	/** @return the position of the Top right corner of the V in the box2D world coordinates [m]*/
	b2Vec2 getTopRightCorner();
	/** @return the position of the bottom of the V in the box2D world coordinates [m]*/
	b2Vec2 getBottom();
//
//	double getVLength();
};

#endif /* RAMP_H_ */
