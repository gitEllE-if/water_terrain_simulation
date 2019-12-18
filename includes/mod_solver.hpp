/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_solver.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:09:14 by laleta            #+#    #+#             */
/*   Updated: 2019/11/28 22:30:47 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"
#include "mod_grid.hpp"
#include "mod_view_control.hpp"
    
class pipe_model_solver
{
	public:
		pipe_model_solver(size_t x_cells, size_t y_cells, double time_step);
		void		initialize_water_height(const std::vector<double> &input);
		void		initialize_flow(size_t x_cells, size_t y_cells);
		void		initialize_surface_level(const std::vector<double> &input);
		void		run();//size_t iterations);
		void		init_df(double time_step);
		const grid	&get_water_height() const;
		const grid	&get_surface_level() const;
	private:
//		void		simple();
		grid		calculate_flow(double time_step);
		double		cell_flow(double w0, double h0, double w1, double h1);
		void		apply_boundary_conditions(grid &ggrid, double dt);
		void		apply_corner_conditions(grid &ggrid, double dt);
		void		rain(grid &ggrid);
		void		snow(grid &ggrid);
		double		dt;
		double		df;
		size_t		x_cells;
		size_t		y_cells;
		grid		water_height;
		grid		flow;
		grid		surface_level;

};
