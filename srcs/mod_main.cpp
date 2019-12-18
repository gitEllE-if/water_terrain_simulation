/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:17:53 by laleta            #+#    #+#             */
/*   Updated: 2019/11/29 05:38:22 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod1.hpp"
#include "mod_solver.hpp"
#include "mod_render.hpp"
#include "mod_map.hpp"

bool	check_in(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		std::cout << "usage:  ./mod1 surface_file [water_file]" << std::endl <<
		"example:./mod1 map/demo1.mod1 map/water.txt" << std::endl <<
		"[ENTER] - start" << std::endl << "[SPACE] - stop" << std::endl <<
		"[1] - water  [2] - rain  [3] - snow" << std::endl <<
		"[Z] - sound  [X] - mute" << std::endl <<
		"[<] - slow   [>] - fast" << std::endl <<
		"[-] - leak   [+] - rise   [0] - none" << std::endl;
		return (false);
	}
	for (int i = 1; i < argc; i++)
	{
		try
		{
			boost::filesystem::path file_path(argv[i]);
			if (!boost::filesystem::exists(file_path) ||
				!boost::filesystem::is_regular_file(file_path))
			{
				std::cout << "error: map_file fail" << std::endl;
				return (false);
			}
		}
		catch (boost::filesystem::filesystem_error &e)
		{
			std::cerr << e.what() << std::endl;
			return (false);
		}
	}
	return (true);
}

int		main(int argc, char **argv)
{
	if (!check_in(argc, argv))
		return (1);
	map_surf_water map(argc, argv);
    pipe_model_solver solver(GRID_WIDTH, GRID_HEIGHT, MOD_DT);
    solver.initialize_water_height(map.water);
    solver.initialize_flow(GRID_WIDTH, GRID_HEIGHT);
    solver.initialize_surface_level(map.surface);
    std::vector<GLfloat> water_height(map.water.begin(), map.water.end());
    std::vector<GLfloat> surface_level(map.surface.begin(), map.surface.end());
    for (size_t i = 0; i < water_height.size(); ++i)
        water_height[i] += surface_level[i];
    visual_engine visual_engine(GRID_WIDTH, GRID_HEIGHT, MOD_DX, 800, 800,
																&surface_level);
    visual_engine.update_vertex_values(&water_height, &surface_level);
    while(!visual_engine.should_stop())
	{
		visual_engine.render();
        if (visual_engine.start_simulation())
		{
			solver.run();
			std::vector<double> const *wh = &solver.get_water_height().get_base();
			water_height = std::vector<GLfloat>(wh->begin(), wh->end());
			for (size_t i = 0; i < water_height.size(); ++i)
			{
				if ((i >= 0 && i <= 99) || (i >= 9900 && i <= 9999) ||
					i % 100 == 0 || (i + 1) % 100 == 0)
					water_height[i] = 0.0;
				else
					water_height[i] += surface_level[i];
			}
            visual_engine.update_vertex_values(&water_height);
        }
    }
    return 0;
}
