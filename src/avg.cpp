/*
 * HumanActiviyRecognition/src/avg.cpp
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
#include "../include/lib.hpp"

using namespace std;
using namespace cv;

/* doCalculateAverage : To calculate the averages of the DFT features 
 * considering 10 frames at a time.
 */
void doCalculateAverage(void)
{
	Mat features[60], result;
	result = Mat::zeros(120, 180, CV_32F);

	char filename[25];

	int i, j, c;

	#define TRAIN_FRAME_START	1050
	#define TRAIN_FRAME_END		TRAIN_FRAME_START + 60
	#define TRAIN_AVG_STEP		10

	for (i = TRAIN_FRAME_START; i < TRAIN_FRAME_END; ) {
		for (j = i ; j < i + 10; j++) {
			sprintf(filename, DFT_OUTPUT"%d.xml", j);
			FileStorage fs(filename, FileStorage::READ);
			fs["dft"]>>features[j - TRAIN_FRAME_START];
			result += features[j - TRAIN_FRAME_START];
			fs.release();
		}
		result = result / (float) TRAIN_AVG_STEP;
		sprintf(filename, DATABASE_OUTPUT"%d.xml", (i - TRAIN_FRAME_START) / 10);
		FileStorage fs(filename, FileStorage::WRITE);
		fs<<"feature"<<result;
		fs.release();
		i = i + TRAIN_AVG_STEP;
	}

	cout<<"Feature database created."<<endl;
}
