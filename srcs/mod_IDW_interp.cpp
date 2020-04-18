#include "mod_IDW_interp.hpp"

double			IDW_interp::get_dist(double x1, double y1, double x2, double y2)
{
	double dx;
	double dy;
	double sq;

	dx = x2 - x1;
	dy = y2 - y1;
	sq = sqrt(dx * dx + dy * dy);
    if (sq == 0)
        sq = 0.001;
	return (sq);
}

double			IDW_interp::get_max_dist_from_point(double x, double y,
										vector<double> xs, vector<double> ys)
{
    double max_dist;
	double this_dist;

	max_dist = 0.0f;
    for (uint64_t i = 0; i < xs.size(); i++)
	{
        this_dist = get_dist(x, y, xs[i], ys[i]);
        if (this_dist > max_dist)
            max_dist = this_dist;
    }
    return (max_dist);
}

vector<double>	IDW_interp::get_all_dist_from_point(double x, double y,
										vector<double> xs, vector<double> ys)
{
    vector<double>  all_dist;
	double			this_dist;

    for (uint64_t i = 0; i < xs.size(); i++)
	{
        this_dist = get_dist(x, y, xs[i], ys[i]);
        all_dist.push_back(this_dist);
    }
    return (all_dist);
}

double			IDW_interp::get_interp_value(double x, double y,
						vector<double> xs, vector<double> ys, vector<double> f)
{
	vector<double>	all_dist;
    double			interp_value;
	double			max_dist;
	double			this_dist;
    
	interp_value = 0.0f;
    for (uint64_t i = 0; i < xs.size(); i++)
	{
        max_dist = get_max_dist_from_point(x, y, xs, ys);
        all_dist = get_all_dist_from_point(x, y, xs, ys);
        this_dist = get_dist(x, y, xs[i], ys[i]);
        interp_value += f[i] * get_weight(max_dist, this_dist, all_dist);
    }
    return (interp_value);
}

double			IDW_interp::get_weight(double max_dist, double this_dist,
														vector<double> all_dist)
{
    double	weight;
	double	first_term;
	double	second_term;

	weight = 0.0f;
	second_term = 0.0f;
    first_term = pow(((max_dist - this_dist) / (max_dist * this_dist)), 2);
    for (uint64_t i = 0; i < all_dist.size(); i++)
        second_term += pow(((max_dist - all_dist[i]) /
												(max_dist * all_dist[i])), 2);
    weight = first_term / second_term;
    return (weight);
}
