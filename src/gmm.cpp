/*
 * HumanActiviyRecognition/src/gmm.cpp
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

#include <iostream>
#include <stdio.h>  

#include "../include/opencv.hpp"
#include "../include/const.hpp"
#include "../include/pre.hpp"

using namespace std;
using namespace cv;

/* doBackgroundSubtraction : To perform background subtraction
 * using Gaussian Mixture Model.
 */
void doBackgroundSubtraction(char input[])
{
	Mat vLayer, fgMaskMOG2; 
	
	Ptr<BackgroundSubtractor> pMOG2;	

	char filename[25];

	int i = 0;	

	pMOG2 = createBackgroundSubtractorMOG2();

	while (TRUE) {

		sprintf(filename, FRAME_OUTPUT"%d.jpg", i);
		vLayer = imread(filename, 1);

		if(vLayer.empty()) {
			break;
		}
		else {
			pMOG2->apply(vLayer, fgMaskMOG2);
			sprintf(filename, GMM_OUTPUT"%d.jpg", i);
			imwrite(filename, fgMaskMOG2);
			i++;
		}
	}
}
