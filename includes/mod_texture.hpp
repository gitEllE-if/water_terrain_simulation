/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_texture.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 05:27:01 by laleta            #+#    #+#             */
/*   Updated: 2019/12/09 05:27:04 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"

class texture_2d
{
	public:
		~texture_2d();
		GLuint	texture2d;
		bool	load_texture2d(std::string const file_name);
};
