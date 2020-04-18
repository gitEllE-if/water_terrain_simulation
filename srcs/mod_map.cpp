#include "mod_map.hpp"

map_surf_water::map_surf_water(int argc, char **argv):
	x_max(INT_MIN), y_max(INT_MIN), z_max(INT_MIN),
	x_min(INT_MAX), y_min(INT_MAX)
{
	if (!get_surface_points(argv[1]))
		exit(1);
	scale_surface_points();
	gen_surface_grid();
	if (argc == 3)
	{
		if (!get_water_grid(argv[2]))
			exit(1);
	}
	else if(!get_water_grid("map/water0.mod"))
		exit(1);
}

bool map_surf_water::get_surface_points(std::string const file_name)
{
	int		n1, n2, n3;
	char	c1, c2, c3, c4;
	int		point_cnt = 0;

	std::ifstream	input(file_name);
	if (!input.is_open())
	{
		std::cerr << std::strerror(errno) << std::endl;
		return (false);
	}
	std::string		str;
    input.exceptions(std::istream::failbit | std::istream::badbit);
	if (input.peek() != '(')
		return (false);
	input >> str;
	while (!str.empty())
	{
		std::stringstream ss(str);
		n1 = ss.peek();
		if (n1 == EOF || n1 == '\0' || n1 == '\n')
		{
			std::cout << "ERROR: wrong map" << std::endl;
			str.clear();
			return (false);
		}
		ss >> c1 >> n1 >> c2 >> n2 >> c3 >> n3 >> c4;
		if (point_cnt >= 50 || ss.fail() || n1 < 0 || n2 < 0 || n3 < 0 ||
			n1 > INT_MAX - 1 || n2 > INT_MAX - 1 || n3 > INT_MAX - 1)
		{
			std::cout << "ERROR: wrong map" << std::endl;
			str.clear();
			return (false);
		}
		x.push_back(n1);
		y.push_back(n2);
		z.push_back(n3);
		point_cnt++;
		str.clear();
		while (input.peek() == ' ')
			input.ignore(1, ' ');
		while (input.peek() == '\n')
			input.ignore(1, '\n');
		if (input.eof() || input.peek() != '(')
			break;
		input >> str;
	}
	return (true);
}

void map_surf_water::scale_surface_points()
{
	size_t n;

	n = x.size();
	for (size_t i = 0; i < n; i++)
	{
		if (x[i] > x_max)
			x_max = x[i];
		if (x[i] < x_min)
			x_min = x[i];
		if (y[i] > y_max)
			y_max = y[i];
		if (y[i] < y_min)
			y_min = y[i];
		if (z[i] > z_max)
			z_max = z[i];
	}
	x_max += x_min;
	y_max += y_min;
	for (size_t i = 0; i < n; i++)
	{
		x[i] = x[i] / x_max * (GRID_WIDTH - 1);
		y[i] = y[i] / y_max * (GRID_HEIGHT - 1);
		z[i] = z[i] / z_max * SURF_HEIGHT; 
	}
	for (size_t i = 0; i < GRID_WIDTH - 1; i += 10)
	{
		x.push_back(i);
		y.push_back(0);
		z.push_back(0.0);
		x.push_back(i);
		y.push_back(GRID_HEIGHT - 1);
		z.push_back(0.0);
	}
	for (size_t i = 1; i < GRID_HEIGHT - 2; i += 10)
	{
		x.push_back(0);
		y.push_back(i);
		z.push_back(0.0);
		x.push_back(GRID_WIDTH - 1);
		y.push_back(i);
		z.push_back(0.0);
	}
}

bool	map_surf_water::get_water_grid(std::string const file_name)
{
	std::ifstream input(file_name);
    input.exceptions(std::istream::failbit | std::istream::badbit);
	if (!input.is_open())
	{
		std::cerr << std::strerror(errno) << std::endl;
		return (false);
	}
	water.resize(GRID_WIDTH * GRID_HEIGHT);
	for (double &value: water)
		input >> value;
	return (true);
}

void	map_surf_water::gen_surface_grid()
{
	IDW_interp idw;
	surface.resize(GRID_WIDTH * GRID_HEIGHT);
	std::uniform_real_distribution<double> unif(0.0, SURF_HEIGHT / 30);
	std::default_random_engine re;
	for (size_t i = 0; i < GRID_HEIGHT; i++)
	{
		for (size_t j = 0; j < GRID_WIDTH; j++)
		{
			if (i == 0 || j == 0 || i == GRID_HEIGHT - 1 || j == GRID_WIDTH - 1)
				surface[j + i * (GRID_HEIGHT)] = 0;
			else
				surface[j + i * (GRID_HEIGHT)] = unif(re) + 
									idw.get_interp_value(j, i, x, y, z);
		}
	}
}
