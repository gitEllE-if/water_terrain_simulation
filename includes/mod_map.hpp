#pragma once

#include "mod1.hpp"
#include "mod_IDW_interp.hpp"

class map_surf_water
{
	public:
		map_surf_water(int argc, char **argv);
		std::vector<double> surface;
		std::vector<double> water;
	private:
		std::vector<double>	x;
		std::vector<double>	y;
		std::vector<double>	z;
		bool				get_surface_points(std::string const file_name);
		bool				get_water_grid(std::string const file_name);
		void				gen_surface_grid();
		void				scale_surface_points();
		double				x_max;
		double				y_max;
		double				z_max;
		double				x_min;
		double				y_min;
};
