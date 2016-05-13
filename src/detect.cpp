/*
 * HumanActiviyRecognition/src/detect.cpp
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

extern int nframes;

/* doActivityRecognition : To recognize the activity in the 
 * input video file and classify it.
 *
 * FIXME : plese make this code beautiful...
 */
void doActivityRecognition(char input[])
{
	Mat database[6], classifier[3][6], result, features[nframes], temp;
	result = Mat::zeros(120, 180, CV_32F);

	char filename[25];

	int i, j, db = 0, db_id, db_select[3] = { 0 }, match[6] = { 0 }, total = 0;

	Database :
	/* ******************** */
	for (i = 0; i < 6; i++) {
		sprintf(filename, DATABASE_OUTPUT"%d.xml", i);
		FileStorage fs(filename, FileStorage::READ);
		fs["feature"]>>database[i];
		fs.release();
	}

	Classifier :
	/* *********************** */
	for (db = 0; db < 3; db++) {
		for (i = 0; i < 6; i++) {
			sprintf(filename, CLASSIFIER_PATH"%d/%d.xml", db, i);
			FileStorage fs(filename, FileStorage::READ);
			fs["feature"]>>classifier[db][i];
			fs.release();
		}
		cout<<"Database loaded : "<<CLASSIFIER_PATH<<""<<db<<"/"<<endl;
	}

	cout<<endl;

	Comparision :
	/* ******************************* */
	for (i = 0; i < nframes - 59; i++) {

		cout<<"Frames : "<<i<<" - "<<i + 59<<endl;

		/* averaging for the first frame */
		for (j = i; j < i + 10; j++) {
			sprintf(filename, DFT_OUTPUT"%d.xml", j);
			FileStorage fs(filename, FileStorage::READ);
			fs["dft"]>>features[j];
			result += features[j];
			fs.release();
		}

		result /= 10.0;

		/* comparision for the first frame */
		for (db = 0; db < 3; db++) {
			temp = classifier[db][0];

			for (int m = 0; m < result.rows; m++) {
				for (int n = 0; n < result.cols; n++) {
					float a = result.at<float>(m,n);
					float b = temp.at<float>(m,n);						
					if ((int) (a * PRECISION) == (int) (b * PRECISION))
						db_select[db]++;
				}
			}
		}

		if (db_select[0] >= db_select[1] && db_select[0] >= db_select[2])
			db_id = 0;
		else if (db_select[1] >= db_select[0] && db_select[1] >= db_select[2])
			db_id = 1;
		else
			db_id = 2;

		match[0] = db_select[db_id];

		Two :
		/* *********************** */
		if (match[0] >= THRESHOLD) {
			total++;

			/* averaging for the second frame */
			for (j = i + 10; j < i + 20; j++) {
				sprintf(filename, DFT_OUTPUT"%d.xml", j);
				FileStorage fs(filename, FileStorage::READ);
				fs["dft"]>>features[j];
				result += features[j];
				fs.release();
			}

			/* comparision for the second frame */
			temp = classifier[db_id][1];
			result /= 10.0;

			for (int m = 0; m < result.rows; m++) {
				for (int n = 0; n < result.cols; n++) {
					float a = result.at<float>(m,n);
					float b = temp.at<float>(m,n);						
					if ((int) (a * PRECISION) == (int) (b * PRECISION))
						match[1]++;
				}
			}

			Three :
			/* *********************** */
			if (match[1] >= THRESHOLD) {
				total++; 
	
				/* averaging for the third frame */
				for (j = i + 20; j < i + 30; j++) {
					sprintf(filename, DFT_OUTPUT"%d.xml", j);
					FileStorage fs(filename, FileStorage::READ);
					fs["dft"]>>features[j];
					result += features[j];
					fs.release();			
				}

				/* comparision for the third frame */
				temp = classifier[db_id][2];
				result /= 10.0;

				for (int m = 0; m < result.rows; m++) {
					for (int n = 0; n < result.cols; n++) {
						float a = result.at<float>(m,n);
						float b = temp.at<float>(m,n);						
						if ((int) (a * PRECISION) == (int) (b * PRECISION))
							match[2]++;
					}
				}

				Four :
				/* *********************** */
				if (match[2] >= THRESHOLD) {
					total++;

					/* averaging for the fourth frame */
					for (j = i + 30; j < i + 40; j++) {
						sprintf(filename, DFT_OUTPUT"%d.xml", j);
						FileStorage fs(filename, FileStorage::READ);
						fs["dft"]>>features[j];
						result += features[j];
						fs.release();
					}

					/* comparision for the fourth frame */
					temp = classifier[db_id][3];
					result /= 10.0;

					for (int m = 0; m < result.rows; m++) {
						for (int n = 0; n < result.cols; n++) {
							float a = result.at<float>(m,n);
							float b = temp.at<float>(m,n);						
							if ((int) (a * PRECISION) == (int) (b * PRECISION))
								match[3]++;
						}
					}


					Five :
					/* *********************** */
					if (match[3] >= THRESHOLD) {
						total++;

						/* averaging for the fifth frame */
						for (j = i + 40; j < i + 50; j++) {
							sprintf(filename, DFT_OUTPUT"%d.xml", j);
							FileStorage fs(filename, FileStorage::READ);
							fs["dft"]>>features[j];
							result += features[j];
							fs.release();
						}

						/* comparision for the fifth frame */
						temp = classifier[db_id][4];
						result /= 10.0;

						for (int m = 0; m < result.rows; m++) {
							for (int n = 0; n < result.cols; n++) {
								float a = result.at<float>(m,n);
								float b = temp.at<float>(m,n);						
								if ((int) (a * PRECISION) == (int) (b * PRECISION))
									match[4]++;
							}
						}


						Six :
						/* *********************** */
						if (match[4] >= THRESHOLD) {
							total++;

							/* averaging for the sixth frame */
							for (j = i + 50; j < i + 60; j++) {
								sprintf(filename, DFT_OUTPUT"%d.xml", j);
								FileStorage fs(filename, FileStorage::READ);			
								fs["dft"]>>features[j];
								result += features[j];
								fs.release();
							}

							/* comparision for the sixth frame */
							temp = classifier[db_id][5];
							result /= 10.0;

							for (int m = 0; m < result.rows; m++) {
								for (int n = 0; n < result.cols; n++) {
									float a = result.at<float>(m,n);
									float b = temp.at<float>(m,n);						
									if ((int) (a * PRECISION) == (int) (b * PRECISION))
										match[5]++;
								}
							}

							if (match[5] >= THRESHOLD)
								total++;
						}
					}
				}
			}
		}

		/* ************ */
		if (total >= 4) {
			cout<<"Activity : Kick"<<endl;
			cout<<"Frames : "<<i<<" - "<<i+59<<endl;
			
			for (int c = i + 20; c < i + 60; c++) {
				sprintf(filename, FRAME_OUTPUT"%d.jpg", c);
				Mat frame = imread(filename);
				cv::putText(frame, "Kick", cv::Point(30,20), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(0,0,255),  1, cv::LINE_AA);
				imwrite(filename, frame);
			}
			cout<<endl;
		}

		result = Mat::zeros(120, 180, CV_32F);
		
		for (int c = 0; c < 3; c++) {
			db_select[c] = 0;
		}

		for (int c = 0; c < 6; c++) {
			match[c] = 0;
		}

		total = 0;
	}

}
