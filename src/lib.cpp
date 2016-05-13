/*
 * HumanActiviyRecognition/src/frames.cpp
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

#include <stdio.h>

#include "../include/const.hpp"
#include "../include/pre.hpp"
#include "../include/lib.hpp"

extern int nframes;

/* doCleanAll : To clean all the frames and
 * calculated dft features
 */
void doCleanAll(void)
{
	for (int i = 0; i < nframes; i++) {
		sprintf(filename, FRAME_OUTPUT"%d.jpg", i);
		remove(filename);
		sprintf(filename, GMM_OUTPUT"%d.jpg", i);
		remove(filename);
		sprintf(filename, DFT_OUTPUT"%d.xml", i);
		remove(filename);
	}
}
