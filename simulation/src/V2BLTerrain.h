/*
 * V2BLTerrain.h
 *
 *  Created on: 18 Feb 2019
 *      Author: lucie
 */

#ifndef V2BLTERRAIN_H_
#define V2BLTERRAIN_H_

#include "Terrain.h"

class V2BLTerrain: public Terrain  {
public:
	V2BLTerrain();
	V2BLTerrain(b2World* world, sf::RenderWindow& window,  config::sTerrain terrainParam, int WINDOW_X_PX, double bodyLength=1); // If want to define the dimension relatively to the body length
	virtual ~V2BLTerrain();

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

private:
	double m_bottom=0;
};

#endif /* V2BLTERRAIN_H_ */
