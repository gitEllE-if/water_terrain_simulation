#pragma once

#include "mod1.hpp"
#include "mod_camera.hpp"

class	sim_state
{
	public:
		sim_state(double flow, double dtime);
		double			left_flow;
		double			right_flow;
		double			up_flow;
		double			down_flow;
		double			dt;
		double			df;
		int32_t			weather;
		int32_t			dec_flow;
		int32_t			dec_flow_all;
		bool			run;
		bool			mouse_track;
		bool			mute;
		sf::SoundBuffer	buffer[3];
		sf::Sound		sound[3];
		void 			resize_flow(double *flow);
		void			resize_dtime(double dtime);
		void			resize_dflow(double dtime);
	private:
		double			flow_size;
};

namespace view_control
{
    extern camera		cam;
    extern bool			keys[1024];
    extern GLfloat		delta_time;
	extern sim_state	state;

    void	key_callback(GLFWwindow* window, int key, int scancode, int action,
																	int mode);
    void	mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void	do_camera_movement();
	void	set_mod_state();
}
