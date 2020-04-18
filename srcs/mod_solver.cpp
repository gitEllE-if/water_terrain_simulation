#include "mod_solver.hpp"

pipe_model_solver::pipe_model_solver(size_t x_cells, size_t y_cells,
															double time_step):

    dt(time_step),
    x_cells(x_cells),
    y_cells(y_cells),
    water_height(x_cells, y_cells),
    flow(x_cells, y_cells),
    surface_level(x_cells, y_cells)
{}
    
void pipe_model_solver::run()
{    
	grid new_flow(calculate_flow(view_control::state.dt));
	if (view_control::state.weather == MOD_RAIN)
		rain(new_flow);
	if (view_control::state.weather == MOD_SNOW)
		snow(new_flow);
	flow = new_flow;
	water_height += new_flow;
}

void pipe_model_solver::apply_corner_conditions(grid &new_flow, double dt)
{
	using namespace view_control;
	double dh;
	double flow_upleft = (state.up_flow + state.left_flow) / 2;
	double flow_upright = (state.up_flow + state.right_flow) / 2;
	double flow_downleft = (state.down_flow + state.left_flow) / 2;
	double flow_downright = (state.down_flow + state.right_flow) / 2;

	dh = 	cell_flow(	water_height(0, 0),
						surface_level(0, 0),
						water_height(1, 0),
						surface_level(1, 0)) +
			cell_flow(	water_height(0, 0),
						surface_level(0, 0),
						water_height(0, 1),
						surface_level(0, 1)) + flow_downright;
	new_flow(0, 0) = MOD_FRICTION * flow(0, 0) + dh * dt;
	dh =	cell_flow(	water_height(0, y_cells - 1),
						surface_level(0, y_cells - 1),
						water_height(1, y_cells - 1),
						surface_level(1, y_cells - 1)) +
			cell_flow(	water_height(0, y_cells - 1),
						surface_level(0, y_cells - 1),
						water_height(0, y_cells - 2),
						surface_level(0, y_cells - 2)) + flow_upright;
	new_flow(0, y_cells - 1) = MOD_FRICTION * flow(0, y_cells - 1) + dh * dt;
	dh =	cell_flow(	water_height(x_cells - 1, 0),
						surface_level(x_cells - 1, 0),
						water_height(x_cells - 1, 1),
						surface_level(x_cells - 1, 1)) +
			cell_flow(	water_height(x_cells - 1, 0),
						surface_level(x_cells - 1, 0),
						water_height(x_cells - 2, 0),
						surface_level(x_cells - 2, 0)) + flow_downleft;
	new_flow(x_cells - 1, 0) = MOD_FRICTION * flow(x_cells - 1, 0) + dh * dt;
	dh = 	cell_flow(	water_height(x_cells - 1, y_cells - 1),
						surface_level(x_cells - 1, y_cells - 1),
						water_height(x_cells - 2, y_cells - 1),
						surface_level(x_cells - 2, y_cells - 1)) +
			cell_flow(	water_height(x_cells - 1, y_cells - 1),
						surface_level(x_cells - 1, y_cells - 1),
						water_height(x_cells - 1, y_cells - 2),
						surface_level(x_cells - 1, y_cells - 2)) + flow_upleft;
	new_flow(x_cells - 1, y_cells - 1) = MOD_FRICTION *
									flow(x_cells - 1, y_cells - 1) + dh * dt;
}

void pipe_model_solver::apply_boundary_conditions(grid &new_flow, double dt)
{    
	double dh;
    for (size_t j = 1; j < y_cells - 1; ++j)
	{
		dh = cell_flow(water_height(0, j), surface_level(0, j),
							water_height(1, j), surface_level(1, j)) +
						cell_flow(water_height(0, j), surface_level(0, j),
							water_height(0, j + 1), surface_level(0, j + 1)) +
						cell_flow(water_height(0, j), surface_level(0, j),
							water_height(0, j - 1), surface_level(0, j - 1)) + 
												view_control::state.right_flow;
		new_flow(0, j) = MOD_FRICTION * flow(0, j) + dh * dt;
    }
    for (size_t j = 1; j < y_cells - 1; ++j)
	{
		dh = cell_flow(water_height(x_cells - 1, j), surface_level(x_cells - 1, j),
		water_height(x_cells - 2, j), surface_level(x_cells - 2, j)) +
		cell_flow(water_height(x_cells - 1, j), surface_level(x_cells - 1, j),
		water_height(x_cells - 1, j + 1), surface_level(x_cells - 1, j + 1)) +
		cell_flow(water_height(x_cells - 1, j), surface_level(x_cells - 1, j),
		water_height(x_cells - 1, j - 1), surface_level(x_cells - 1, j - 1)) +
												view_control::state.left_flow;
		new_flow(x_cells - 1, j) = MOD_FRICTION * flow(x_cells - 1, j) + dh * dt;
    }
    for (size_t i = 1; i < x_cells - 1; ++i)
	{
		dh = cell_flow(water_height(i, 0), surface_level(i, 0),
							water_height(i, 1), surface_level(i, 1)) +
						cell_flow(water_height(i, 0), surface_level(i, 0),
							water_height(i + 1, 0), surface_level(i + 1, 0)) +
						cell_flow(water_height(i, 0), surface_level(i, 0),
							water_height(i - 1, 0), surface_level(i - 1, 0)) +
												view_control::state.down_flow;
		new_flow(i, 0) = MOD_FRICTION * flow(i, 0) + dh * dt;
    }
    for (size_t i = 1; i < x_cells - 1; ++i)
	{
		dh = cell_flow(water_height(i, y_cells - 1), surface_level(i, y_cells - 1),
		water_height(i, y_cells - 2), surface_level(i, y_cells - 2)) +
		cell_flow(water_height(i, y_cells - 1), surface_level(i, y_cells - 1),
		water_height(i + 1, y_cells - 1), surface_level(i + 1, y_cells - 1)) +
		cell_flow(water_height(i, y_cells - 1), surface_level(i, y_cells - 1),
		water_height(i - 1, y_cells - 1), surface_level(i - 1, y_cells - 1)) +
													view_control::state.up_flow;
		new_flow(i, y_cells - 1) = MOD_FRICTION * flow(i, y_cells - 1) + dh * dt;
    }
}

void pipe_model_solver::initialize_water_height(const std::vector<double> &in)
{
    for (size_t i = 0; i < x_cells; ++i)
	{
        for (size_t j = 0; j < y_cells; ++j)
			water_height(i, j) = in[i * x_cells + j];
    }
}

void pipe_model_solver::initialize_flow(size_t x_cells, size_t y_cells)
{
    for (size_t i = 0; i < x_cells; ++i)
	{
        for (size_t j = 0; j < y_cells; ++j)
			flow(i, j) = 0.0;
    }
}

void pipe_model_solver::initialize_surface_level(const std::vector<double> &in)
{
    for (size_t i = 0; i < x_cells; ++i)
	{
        for (size_t j = 0; j < y_cells; ++j)
            surface_level(i, j) = in[i * x_cells + j];
    }
}

double pipe_model_solver::cell_flow(double w0, double h0, double w1, double h1)
{
	using namespace view_control;
	double diff;
	double drop;
	
	if (state.weather == MOD_FLOOD)
		drop = 0.0;
	else
		drop = MOD_DF;
	diff = fabs(w0 + h0 - w1 + h1);
	if ((w1 < 0.001 && h1 > w0 + h0) || (w0 < 0.001 && h0 > w1 + h1) ||
		diff < 0.001)
		return (drop);
	if (w0 + h0 > w1 + h1)
	{
		if (state.weather != MOD_SNOW)
			return (-diff * (state.df + MOD_DF * ((1 - state.dec_flow_all) / 2)));
			else
				return (-MOD_DF);
	}
	if (w0 + h0 < w1 + h1)
	{
		if (state.weather != MOD_SNOW)
			return (diff * (1.0 + (MOD_DF) * ((1 + state.dec_flow_all) / 2)));
		else
			return (MOD_DF);
	}
	return (0.0);
}

grid pipe_model_solver::calculate_flow(double dt)
{    
	grid new_flow(x_cells, y_cells);
	for (size_t j = 1; j < y_cells - 1; j++)
	{
		for (size_t i = 1; i < x_cells - 1; i++)
		{
			double dh = cell_flow(water_height(i, j), surface_level(i,j),
							water_height(i + 1, j), surface_level(i + 1, j)) +
						cell_flow(water_height(i, j), surface_level(i,j),
							water_height(i - 1, j), surface_level(i - 1, j)) +
						cell_flow(water_height(i, j), surface_level(i,j),
							water_height(i, j + 1), surface_level(i, j + 1)) +
						cell_flow(water_height(i, j), surface_level(i,j),
							water_height(i, j - 1), surface_level(i, j - 1));
			new_flow(i, j) = MOD_FRICTION * flow(i, j) + dh * dt;
		}
	}
	apply_boundary_conditions(new_flow, dt);
	apply_corner_conditions(new_flow, dt);
    return(new_flow);
}

void pipe_model_solver::snow(grid &new_flow)
{
	std::uniform_int_distribution<int> unif(0, x_cells - 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	new_flow(unif(gen), unif(gen)) += 0.003;
	new_flow(unif(gen), unif(gen)) += 0.004;
	new_flow(unif(gen), unif(gen)) += 0.002;
}

void pipe_model_solver::rain(grid &new_flow)
{
	std::uniform_int_distribution<int> unif(0, x_cells - 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	new_flow(unif(gen), unif(gen)) += 0.02;
	new_flow(unif(gen), unif(gen)) += 0.03;
	new_flow(unif(gen), unif(gen)) += 0.04;
}
         
const grid &pipe_model_solver::get_water_height() const
{
    return (water_height);
}

const grid &pipe_model_solver::get_surface_level() const
{
    return (surface_level);
}
