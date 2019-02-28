/*
 * World.h
 *
 *  Created on: 27 sept. 2018
 *      Author: lucie
 */

#ifndef WORLD_H_
#define WORLD_H_

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Config.h"

class World {
public:
	World(	b2World& world, sf::RenderWindow& window,
			float m_to_pix, float window_x_px, float window_y_px,
			float wall_w_m, float wall_h_m);
	virtual ~World();

	/// Create the Box2D body for the static object of the scene.
	/// @param m_to_pix, window_x_px, window_y_px: configuration of the window, they are usually defined in the config file.
	/// @param wall_w_m, wall_h_m: configuration of the walls, they are usually defined in the config file.
	void createBody(	b2World& world,
						float m_to_pix, float window_x_px, float window_y_px,
						float wall_w_m, float wall_h_m);

	/// Draw the shapes corresponding to the Box2D body created previously.
	/// @param m_to_pix, window_x_px, window_y_px: configuration of the window, they are usually defined in the config file.
	/// @param wall_w_m, wall_h_m: configuration of the walls, they are usually defined in the config file.
	void drawBody(	sf::RenderWindow& window,
					float m_to_pix, float window_x_px, float window_y_px,
					float wall_w_m, float wall_h_m);

private:
	b2Body* m_groundBody;
	float m_M_TO_PX ;
};

#endif /* WORLD_H_ */
