/*
 * config.h
 *
 *  Created on: 26 sept. 2018
 *      Author: lucie
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "constants.h"


namespace config
{

	const double WINDOW_X_PX = 1920; // [pixel]
	const double WINDOW_Y_PX = 1080; // [pixel]

	const double WALL_WIDTH_M = 6.0; // [m]
	const double WALL_HEIGHT_M = 3.0; // [m]




struct sTerrain{
	double runaway;
	double v_width;
	double v_height;
	double v_angle;
};

struct sSimulation{
	double gravity;
	double robot_delay;
	double robot_distance;
	double robot_phase;
	double robot_initial_posX;
	double robot_initial_posY;
	int nb_robots;
	double bridge_duration;
	double dissolution_duration;
	bool visualization;
};

struct sController{
	double angle_limit;
	double bridge_delay;
	double walk_delay;
	double time_before_pushing;
	int max_robot_window;
	double stability_condition;
};

struct sRobot{
	double body_length;
	double speed;
	double wheel_distance;
	double attach_height;
	double wheel_radius;
};

struct sWindow{
	int WINDOW_X_PX ;
	int WINDOW_Y_PX;
};

struct sConfig{
	struct sTerrain terrain;
	struct sSimulation simulation;
	struct sController controller;
	struct sRobot robot;
	struct sWindow window;

	std::string logfile_name;
	std::string logfile_path;
};


class Configuration
{
public:
    // clear all values
    void Clear();

    // load a configuration file
    bool Load(const std::string& File);

    // check if value associated with given key exists
    bool Contains(const std::string& key) const;

    // get value associated with given key
    bool Get(const std::string& key, std::string& value) const;
    bool Get(const std::string& key, int&    value) const;
    bool Get(const std::string& key, long&   value) const;
    bool Get(const std::string& key, double& value) const;
    bool Get(const std::string& key, bool&   value) const;

private:
    // the container
    std::map<std::string,std::string> data;

    // remove leading and trailing tabs and spaces
    static std::string Trim(const std::string& str);
};

//extern sConfig sConfig;
};
#endif /* CONFIG_H_ */
