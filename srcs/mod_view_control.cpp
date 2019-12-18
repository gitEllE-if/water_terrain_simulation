/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_view_control.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:35:41 by laleta            #+#    #+#             */
/*   Updated: 2019/12/09 05:29:29 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_view_control.hpp"

sim_state::sim_state(double flow, double dtime):
	left_flow(0.0), right_flow(0.0), up_flow(0.0), down_flow(0.0),
	dt(dtime), weather(MOD_FLOOD), dec_flow(0), run(false), mouse_track(true),
	mute(true), flow_size(flow)
{
	resize_dflow(dtime);
	buffer[MOD_FLOOD].loadFromFile(DIR_FLOOD AUDIO_WATER);
	buffer[MOD_RAIN].loadFromFile(DIR_RAIN AUDIO_WATER);
	buffer[MOD_SNOW].loadFromFile(DIR_SNOW AUDIO_WATER);
	for (int i = 0; i < 3; i++)
		sound[i].setBuffer(buffer[i]);
}

void sim_state::resize_dflow(double dtime)
{
	df = -5.2778 * dtime + 1.0008;
}

void sim_state::resize_dtime(double time_step)
{
	dt = glm::clamp(dt + time_step, 0.001, 0.01);
}

void sim_state::resize_flow(double *flow)
{
	*flow = glm::clamp(*flow + dec_flow * flow_size, 0.0, flow_size);
}

namespace view_control
{

    camera		cam(glm::vec3(0.0f, 6.0f, -8.0f),
											glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
	sim_state	state(MOD_FLOW_SIZE, MOD_DT);

    bool keys[1024];
    GLfloat delta_time = 0.0;

    void do_camera_movement()
	{
        if (keys[GLFW_KEY_W])
            cam.process_keyboard(FORWARD, delta_time);
        if (keys[GLFW_KEY_S])
            cam.process_keyboard(BACKWARD, delta_time);
        if (keys[GLFW_KEY_A])
            cam.process_keyboard(LEFT, delta_time);
        if (keys[GLFW_KEY_D])
            cam.process_keyboard(RIGHT, delta_time);
    }

	void	set_mod_state()
	{
		if (keys[GLFW_KEY_ENTER])
			state.run = true; 
		if (keys[GLFW_KEY_SPACE])
			state.run = false;
		if (keys[GLFW_KEY_M])
			state.mouse_track = true;
		if (keys[GLFW_KEY_N])
			state.mouse_track = false;
		if (keys[GLFW_KEY_X])
		{
			state.mute = true;
			state.sound[0].stop();
			state.sound[1].stop();
			state.sound[2].stop();
		}
		if (keys[GLFW_KEY_Z])
			state.mute = false;

		if (keys[GLFW_KEY_1])
		{
			state.weather = MOD_FLOOD;
			if (!state.mute)
			{
				state.sound[MOD_FLOOD].play();
				state.sound[MOD_RAIN].stop();
				state.sound[MOD_SNOW].stop();
			}
		}
		if (keys[GLFW_KEY_2])
		{
			state.weather = MOD_RAIN;
			if (!state.mute)
			{
				state.sound[MOD_FLOOD].stop();
				state.sound[MOD_RAIN].play();
				state.sound[MOD_SNOW].stop();
			}
		}
		if (keys[GLFW_KEY_3])
		{
			state.weather = MOD_SNOW;
			if (!state.mute)
			{
				state.sound[MOD_FLOOD].stop();
				state.sound[MOD_RAIN].stop();
				state.sound[MOD_SNOW].play();
			}
		}
		if (keys[GLFW_KEY_MINUS])
			state.dec_flow = -1;
		if (keys[GLFW_KEY_EQUAL])
			state.dec_flow = 1;
		if (keys[GLFW_KEY_0])
			state.dec_flow = 0;
		if (keys[GLFW_KEY_COMMA])
		{
			state.resize_dtime(-MOD_DT);
			state.resize_dflow(state.dt);
		}
		if (keys[GLFW_KEY_PERIOD])
		{
			state.resize_dtime(MOD_DT);
			state.resize_dflow(state.dt);
		}
		if (state.weather != MOD_SNOW)
		{
			if (keys[GLFW_KEY_UP])
				state.resize_flow(&state.up_flow);
			if (keys[GLFW_KEY_DOWN])
				state.resize_flow(&state.down_flow);
			if (keys[GLFW_KEY_LEFT])
				state.resize_flow(&state.left_flow);
			if (keys[GLFW_KEY_RIGHT])
				state.resize_flow(&state.right_flow);
		}
	}

    void scroll_callback([[maybe_unused]]GLFWwindow *window,
								[[maybe_unused]]double xoffset, double yoffset)
	{
        cam.process_mouse_scroll(yoffset);
    }

    void key_callback(GLFWwindow *window, int key, [[maybe_unused]]int scancode,
										int action, [[maybe_unused]]int mode)
	{

        if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		{
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        }
        if (key >= 0 && key < 1024)
		{
            if (action == GLFW_PRESS)
                keys[key] = true;
            else if (action == GLFW_RELEASE)
                keys[key] = false;
        }
    }

    void mouse_callback([[maybe_unused]]GLFWwindow *window, double xpos,
																	double ypos)
	{

        static GLfloat last_x = 400.0f;
		static GLfloat last_y = 300.0f;
        static bool firstMouseMove = true;
        if (firstMouseMove)
		{
            last_x = (GLfloat)xpos;
            last_y = (GLfloat)ypos;
            firstMouseMove = false;
        }
        GLfloat xoffset = xpos - last_x;
        GLfloat yoffset = last_y - ypos;
        last_x = xpos;
        last_y = ypos;
		if (state.mouse_track)
        	cam.process_mouse_move(xoffset, yoffset);
    }
}
