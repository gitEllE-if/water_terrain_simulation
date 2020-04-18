# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laleta <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/07 19:28:58 by laleta            #+#    #+#              #
#    Updated: 2019/11/29 05:20:37 by laleta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mod
FLAGS = -g -Wall -Wextra -std=c++11
SOURCE = mod_main.cpp mod_render.cpp mod_solver.cpp mod_IDW_interp.cpp\
		mod_camera.cpp mod_shader.cpp mod_map.cpp mod_texture.cpp\
		mod_skybox.cpp mod_grid.cpp mod_GL_interface.cpp mod_mesh.cpp\
		mod_view_control.cpp
HEADER = mod1.hpp mod_render.hpp mod_solver.hpp mod_IDW_interp.hpp\
		mod_camera.hpp mod_shader.hpp mod_map.hpp mod_texture.hpp\
		mod_skybox.hpp mod_grid.hpp mod_GL_interface.cpp mod_mesh.hpp\
		mod_view_control.hpp

INCLUDES = -Iincludes -I$(GLEW_DIR)include -I$(GLFW_DIR)include -I$(GLM_DIR)include -I$(SFML_DIR)include -I$(BOOST_DIR)include

GLEW_DIR = /usr/local/Cellar/glew/2.1.0_1/
GLFW_DIR = /usr/local/Cellar/glfw/3.3.2/
GLM_DIR = /usr/local/Cellar/glm/0.9.9.5/
SFML_DIR = /usr/local/Cellar/sfml/2.5.1/
BOOST_DIR = /usr/local/Cellar/boost/1.72.0/

LIB = -framework OpenGL -lglew -lglfw -lsfml-graphics -lsfml-audio -lboost_system -lboost_filesystem

LIB_DIR = -L$(GLEW_DIR)lib -L$(GLFW_DIR)lib -L$(GLM_DIR)lib -L$(SFML_DIR)lib -L$(BOOST_DIR)lib

VPATH = srcs includes

OBJECT = $(SOURCE:.cpp=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJECT)
	@echo "\033[1;3;34m"
	g++ $(FLAGS) $(OBJECT) -o $@ $(INCLUDES) $(LIB_DIR) -Wl,-rpath,$(SFML_DIR)lib $(LIB)
	@echo "\033[23;32m--[ "$(NAME) ]-- successfully compiled"\033[0m"

%.o : %.cpp $(HEADER)
	@echo "\033[36;3m\c"
	g++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0m\c"

clean :
	@rm -f $(OBJECT)

fclean : clean
	@rm -f $(NAME)

re : fclean all

install : 
	@if [ ! -d $(GLFW_DIR) ] ; then brew install glfw; fi
	@if [ ! -d $(GLM_DIR) ] ; then brew install glm; fi
	@if [ ! -d $(SFML_DIR) ] ; then brew install sfml; fi
	@if [ ! -d $(BOOST_DIR) ] ; then brew install boost; fi
	@if [ ! -d $(GLEW_DIR) ] ; then brew install glew; fi
