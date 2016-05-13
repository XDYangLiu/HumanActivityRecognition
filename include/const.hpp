/*
 * HumanActiviyRecognition/include/const.hpp
 *
 * Copyright (C) 2016 Debashis Barman (debashisbarman.in)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __HAR_CONST_HPP
#define __HAR_CONST_HPP

#define TRUE	1

#define FRAME_OUTPUT	"./frames/vlayer/"
#define GMM_OUTPUT	"./frames/bg/"
#define DFT_OUTPUT	"./features/"
#define DATABASE_OUTPUT	"./database/"
#define CLASSIFIER_PATH	"./database/kick"

#define THRESHOLD	15120
#define PRECISION	1000000

static char filename[25];

#endif
