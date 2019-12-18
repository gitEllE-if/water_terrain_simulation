/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_grid.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 21:00:36 by laleta            #+#    #+#             */
/*   Updated: 2019/11/28 22:21:38 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"
    
class grid
{
	public:
		grid(size_t x_cells = 0, size_t y_cells = 0);
		grid(grid const &copy_from) = default;
		grid(grid&& move_from) = default;
		double	&operator()(size_t x, size_t y);
		double 	operator()(size_t x, size_t y) const;
		void	resize(size_t x_cells, size_t y_cells);
		grid&	operator=(grid const &copy_from) = default;
		grid	operator+(grid const &ggrid) const;
		grid	operator-(grid const &ggrid) const;
		grid&	operator+=(grid const &ggrid);
		grid&	operator-=(grid const &ggrid);
		grid	operator*(double multiplier) const;
		const std::vector<double>	&get_base() const;
	private:
		std::vector<double>	base;
		size_t				x_cells;
		size_t				y_cells;
};
