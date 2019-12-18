/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_IDW_interp.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 05:24:36 by laleta            #+#    #+#             */
/*   Updated: 2019/12/09 05:25:10 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"

using namespace std;

class IDW_interp
{
	public:
		double			get_interp_value(double x, double y, vector<double> xs,
										vector<double> ys, vector<double> f);
	protected:
		double			get_max_dist_from_point(double x, double y,
										vector<double> xs, vector<double> ys);
		vector<double>	get_all_dist_from_point(double x, double y,
										vector<double> xs, vector<double> ys);
		double			get_weight(double max_dist, double this_dist,
													vector<double> all_dist);
		double			get_dist(double x1, double y1, double x2, double y2); 
};