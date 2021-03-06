#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "Hough.h"
#include "segmentation.h"
#include "wraping.h"
#include "numProcess.h"
#include "canny_source.h"

/* Hough parameter:
   Line1 : 0.4 20
   Line2 : 0.6 20
   Line3 : 0.6 20
   Line4 : 0.4 20
   Line5 : 0.2 20
   Line6 : 0.4 20
 */

void NumberProcess(string filename, string saveFilename) {
	// string filename = "./Test/10.bmp";
	CImg<float> image = CImg<float>(filename.c_str());

	// Edge detect by segmentation algorithm.
	printf("Image Segmentation\n");
	Segmentation s(filename);
	CImg<unsigned char> edgeImage = s.getFinalResult();
	printf("Image Segmentation Finish\n");
	

	printf("\nHough detect\n");
	float thre, dise;
	printf("Please input Hough Threshold One: ");
	cin >> thre;
	printf("Please input Hough Threshold Two: ");
	cin >> dise;
	Hough hough(edgeImage, thre, dise);

	// Get the four intersection of the A4 paper;
	vector<pair<int, int>> intersection = hough.getIntersection();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3 - i; j++) {
			if (intersection[j].first > intersection[j + 1].first) {
				pair<int, int> temp = intersection[j];
				intersection[j] = intersection[j + 1];
				intersection[j + 1] = temp;
			}
		}
	}

	if (intersection[0].second > intersection[1].second) {
		pair<int, int> temp = intersection[0];
		intersection[0] = intersection[1];
		intersection[1] = temp;
	}

	if (intersection[2].second > intersection[3].second) {
		pair<int, int> temp = intersection[2];
		intersection[2] = intersection[3];
		intersection[3] = temp;
	}

	pair<int, int> temp = intersection[1];
	intersection[1] = intersection[2];
	intersection[2] = temp;

	ofstream outfile;
	outfile.open("./Intersection.txt");
	// Show the four intersections.
	for (int i = 0; i < 4; i++) {
		printf("Intersection Point %d: (%d, %d)\n", i + 1, intersection[i].first, intersection[i].second);
		outfile << "(";
		outfile << intersection[i].first;
		outfile << ", ";
		outfile << intersection[i].second;
		outfile << ")" << endl;
	}
	printf("Hough detect Finish\n");

	printf("\nPaper Wraphing\n");
	CImgList<float> TransferMatrix = createTransferMatrix(intersection, image);
	CImg<float> result = Warphing(image, TransferMatrix);
	result.display("Warphing A4 Paper", false);
	result.save("./MiddleResult/Warphing.bmp");
	printf("Paper Wraphing Finish\n");

	// Process number.
	printf("\nNumber segmentation\n");
	int n_threshold = 150;
	int S_value;
	int connect_value;
	printf("Please input Segmentation S_value: ");
	cin >> S_value;
	printf("Please input Segmentation connect_value: ");
	cin >> connect_value;
	Process process(result, n_threshold, S_value, connect_value);

	// Row segmentation.
	printf("\nRow Segmentation");
	process.findDividingLine();
	printf("\nRow Segmentation Finish\n");

	printf("\nCol Segmentation\n");
	process.divideIntoBarItemImg();
	printf("Col Segmentation Finish\n");

	printf("\nDilating Process\n");
	process.image_process(saveFilename);
	printf("Dilating Process Finish\n");

	printf("\nNumber segmentation Finish\n");	
}

int main(int argc, char* argv[]) {
	printf("Computer Vision Final Project:\n");
	string fileName;
	printf("Please input the filename: ");
	cin >> fileName;
	NumberProcess(fileName, "./Segmentation/");
	printf("Computer Vision Final Project Finish!\n");
	printf("Goodbye!\n");
	return 0;
}