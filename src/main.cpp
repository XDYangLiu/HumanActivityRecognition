/*
 * HumanActiviyRecognition/src/main.cpp
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
#include <string.h>

#include "../include/opencv.hpp"
#include "../include/const.hpp"
#include "../include/pre.hpp"
#include "../include/dft.hpp"
#include "../include/detect.hpp"
#include "../include/lib.hpp"

using namespace std;
using namespace cv;

static char vname[25];
extern int nframes;

int main(int argc, char ** argv)
{
	if (argc != 2) {
		cout<<"Usage : ./main [video file]"<<endl;
	}
	else {
		strcpy(vname, argv[1]);

		/* Preprocessing */
		cout<<"Preprocessing..."<<endl;
		doPreprocessing(vname);

		/* Background Subtraction with GMM */
		cout<<"Background Subtraction with GMM..."<<endl;
		doBackgroundSubtraction(vname);

		/* Discrete Fourier Transform */
		cout<<"Feature Extraction with DFT..."<<endl;
		doDiscreteFourierTransform(vname);

		/* Calculate averages */
		cout<<"Activity Analysis..."<<endl;
		doActivityRecognition(vname);

		/* Result */
		for (int c = 0; c < nframes; c++) {
			sprintf(filename, FRAME_OUTPUT"%d.jpg", c);
			Mat frame = imread(filename);
			Size enlarge(540, 360);
			resize(frame, frame, enlarge);
			imshow("After Analysis", frame);

			if(waitKey(30)>=0)
				break;
		}

		doCleanAll();
	}

	return 0;
}
