/*
 * HumanActiviyRecognition/src/dft.cpp
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
#include "../include/dft.hpp"

using namespace cv;
using namespace std;

/* doDiscreteFourierTransform : To perform DFT on the extracted
 * foreground object. 
 */
void doDiscreteFourierTransform(char input[])
{
	char filename[25];
	Mat frame, padded, complex, mag;
	int i = 0, m, n;

	while (TRUE) {
		sprintf(filename, GMM_OUTPUT"%d.jpg", i);
		frame = imread(filename, IMREAD_GRAYSCALE);

		if (frame.empty())
			break;
		else {
			m = getOptimalDFTSize( frame.rows );
			n = getOptimalDFTSize( frame.cols );
			copyMakeBorder(frame, padded, 0, m - frame.rows, 0, n - frame.cols, BORDER_CONSTANT, Scalar::all(0));

			Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
			merge(planes, 2, complex);

			dft(complex, complex); 

			split(complex, planes);
			magnitude(planes[0], planes[1], planes[0]);
			mag = planes[0];

			mag += Scalar::all(1);
			log(mag, mag);

			mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

			int cx = mag.cols/2;
			int cy = mag.rows/2;

			Mat q0(mag, Rect(0, 0, cx, cy));
			Mat q1(mag, Rect(cx, 0, cx, cy));
			Mat q2(mag, Rect(0, cy, cx, cy));
			Mat q3(mag, Rect(cx, cy, cx, cy));

			Mat tmp; 
			q0.copyTo(tmp);
			q3.copyTo(q0);
			tmp.copyTo(q3);

			q1.copyTo(tmp);
			q2.copyTo(q1);
			tmp.copyTo(q2);

			normalize(mag, mag, 0, 1, NORM_MINMAX);

			sprintf(filename, DFT_OUTPUT"%d.xml", i);

			FileStorage fs(filename, FileStorage::WRITE);

			fs<<"dft"<<mag;

			fs.release();
		}

		i++;
	}
}
