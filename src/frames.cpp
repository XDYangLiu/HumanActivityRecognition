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

#include <iostream> 

#include "../include/opencv.hpp"
#include "../include/const.hpp"
#include "../include/pre.hpp"

using namespace std;
using namespace cv;

int nframes;

/* doPreprocessing : To extract frames from the input video
 * and convert it to HSV from RGB.
 */
void doPreprocessing(char input[])
{
	int i = 0;
	Mat frame, hsvFrame, vLayer;

	vector<Mat> hsv;

	Size size(180, 120);

	VideoCapture cap(input);
	
	while (TRUE) {
		cap.read(frame);

		if (frame.empty())
			break;
		else {
			resize(frame, frame, size);
			cvtColor(frame, hsvFrame, COLOR_BGR2HSV);
			split(hsvFrame, hsv);
			vLayer = hsv.at(2);
			sprintf(filename, FRAME_OUTPUT"%d.jpg", i);
			imwrite(filename, vLayer);
			i++;
		}
	}

	nframes = i;
	cout<<i<<" frames are extracted."<<endl;
}
