/*
 * Vterrain.h
 *
 *  Created on: 8 oct. 2018
 *      Author: lucie
 *
 *      29 Jan 2019:
 *      	- Added the getBody() method
 *
 *
 */

#ifndef VTERRAIN_H_
#define VTERRAIN_H_

#include "Terrain.h"

class Vterrain: public Terrain {
public:
	Vterrain();
	Vterrain(b2World* world, sf::RenderWindow& window,  config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength=1); // If want to define the dimension relatively to the body length
	virtual ~Vterrain();

	void create(b2World* world, sf::RenderWindow& window,  config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength=1);
	void createBody(b2World* world);
	void drawBody(sf::RenderWindow& window);

	e_terrain_type getType();

	/** @return the position of the Top left corner of the V in the box2D world coordinates [m]*/
	b2Vec2 getTopLeftCorner();
	/** @return the position of the Top right corner of the V in the box2D world coordinates [m]*/
	b2Vec2 getTopRightCorner();
	/** @return the position of the bottom of the V in the box2D world coordinates [m]*/
	b2Vec2 getBottom();

	double getVLength();

};

#endif /* VTERRAIN_H_ */
