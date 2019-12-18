/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_grid.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 21:03:54 by laleta            #+#    #+#             */
/*   Updated: 2019/11/28 21:05:49 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_grid.hpp"

grid::grid(size_t x_cells, size_t y_cells):
	base(x_cells * y_cells, 0),
	x_cells(x_cells),
	y_cells(y_cells)
{}

void	grid::resize(size_t x_cells, size_t y_cells)
{    
    this->x_cells = x_cells;
    this->y_cells = y_cells;   
    base.resize(x_cells * y_cells);
}

double &grid::operator()(size_t x, size_t y)
{    
	assert((x < x_cells) && (y < y_cells));
	return (base[x * y_cells + y]);
}

double	grid::operator()(size_t x, size_t y) const
{    
	assert((x < x_cells) && (y < y_cells));
	return (base[x * y_cells + y]);
}

grid	grid::operator+(grid const &ggrid) const
{
    grid sum(*this);
    sum += ggrid;
    return (sum);
}

grid	grid::operator-(grid const &ggrid) const
{
    grid diff(*this);
    diff -= ggrid;
    return (diff);
}

grid&	grid::operator+=(grid const &ggrid)
{
    assert(x_cells == ggrid.x_cells && y_cells == ggrid.y_cells);
    size_t size = ggrid.base.size();
    for (size_t i = 0; i < size; ++i)
        base[i] += ggrid.base[i];
    return (*this);
}

grid&	grid::operator-=(grid const &ggrid)
{
    assert(x_cells == ggrid.x_cells && y_cells == ggrid.y_cells);
    size_t size = ggrid.base.size();
    for (size_t i = 0; i < size; ++i)
        base[i] -= ggrid.base[i];
    return (*this);
}

grid	grid::operator*(double multiplier) const
{
    grid scaled(*this);
    for (double &element: scaled.base)
        element *= multiplier;
    return (scaled);
}

const std::vector<double>	&grid::get_base() const
{
    return (base);
}
