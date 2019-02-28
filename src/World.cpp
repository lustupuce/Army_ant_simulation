/*
 * World.cpp
 *
 *  Created on: 27 sept. 2018
 *      Author: lucie
 */

#include "World.h"
#include "constants.h"

World::World(b2World& world, sf::RenderWindow& window , float m_to_pix, float window_x_px, float window_y_px, float wall_w_m, float wall_h_m) {
	// TODO Auto-generated constructor stub
	createBody(world,m_to_pix, window_x_px, window_y_px, wall_w_m, wall_h_m);
	drawBody(window, m_to_pix, window_x_px, window_y_px, wall_w_m, wall_h_m);

}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::createBody(b2World& world, float m_to_pix, float window_x_px, float window_y_px, float wall_w_m, float wall_h_m){

    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(0, 0);
    BodyDef.type = b2_staticBody;
    m_groundBody = world.CreateBody(&BodyDef);

	b2EdgeShape edgeShape;
	float h = window_y_px/m_to_pix - wall_h_m;
	float l = window_x_px/m_to_pix - wall_w_m;

	b2FixtureDef topEdgeFixtureDef;
	edgeShape.Set( b2Vec2(l/2,h/2), b2Vec2(window_x_px/m_to_pix - l/2,h/2) );
	topEdgeFixtureDef.shape = &edgeShape;
	m_groundBody->CreateFixture(&topEdgeFixtureDef);

	b2FixtureDef bottomEdgeFixtureDef;
	edgeShape.Set( b2Vec2(l/2,window_y_px/m_to_pix - h/2), b2Vec2(window_x_px/m_to_pix - l/2,window_y_px/m_to_pix - h/2) );
	bottomEdgeFixtureDef.shape = &edgeShape;
	m_groundBody->CreateFixture(&bottomEdgeFixtureDef);

	b2FixtureDef leftEdgeFixtureDef;
	edgeShape.Set( b2Vec2(l/2,h/2), b2Vec2(l/2,window_y_px/m_to_pix - h/2) );
	leftEdgeFixtureDef.shape = &edgeShape;
	m_groundBody->CreateFixture(&leftEdgeFixtureDef);

	b2FixtureDef rightEdgeFixtureDef;
	edgeShape.Set( b2Vec2(window_x_px/m_to_pix - l/2,window_y_px/m_to_pix - h/2), b2Vec2(window_x_px/m_to_pix - l/2,h/2) );
	rightEdgeFixtureDef.shape = &edgeShape;
	m_groundBody->CreateFixture(&rightEdgeFixtureDef);

}

void World::drawBody(sf::RenderWindow& window, float m_to_pix, float window_x_px, float window_y_px, float wall_w_m, float wall_h_m){

	float h = window_y_px - wall_h_m*m_to_pix ;
	float l = window_x_px - wall_w_m*m_to_pix;

	sf::VertexArray lines(sf::LinesStrip, 5);
	lines[0].position = sf::Vector2f(l/2, h/2);
	lines[1].position = sf::Vector2f(l/2, window_y_px-h/2);
	lines[2].position = sf::Vector2f(window_x_px-l/2, window_y_px-h/2);
	lines[3].position = sf::Vector2f(window_x_px-l/2, h/2);
	lines[4].position = sf::Vector2f(l/2, h/2);

	lines[0].color = sf::Color::Black;
	lines[1].color = sf::Color::Black;
	lines[2].color = sf::Color::Black;
	lines[3].color = sf::Color::Black;
	lines[4].color = sf::Color::Black;

	window.draw(lines);

}

