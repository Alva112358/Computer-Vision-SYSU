#include "CImg.h"
#include <cmath>
#include <iostream>
using namespace cimg_library;
using namespace std;

#define PI 3.1415926535
struct Color {
	double red;
	double green;
	double blue;
	Color(double _r, double _g, double _b) : red(_r), green(_g), blue(_b) {}
};

struct point {
	double x;
	double y;
	point(double _x, double _y) : x(_x), y(_y) {}
};

double convertToRad(double degree) {
	return PI * degree / 180;
}

class MyImage {
public:
	MyImage();
	void processOne(CImg<unsigned char> &SrcImg);
	void processTwo(CImg<unsigned char> &SrcImg);
	void processThree(CImg<unsigned char> &SrcImg);
	void processThreeCImg(CImg<unsigned char> &SrcImg);
	void processFour(CImg<unsigned char> &SrcImg);
	void processFourCImg(CImg<unsigned char> &SrcImg);
	void processFive(CImg<unsigned char> &SrcImg);
	void processFiveCImg(CImg<unsigned char> &SrcImg);
	void processSix(CImg<unsigned char> &SrcImg, int chooseNumber);
	void drawCircle(CImg<unsigned char> &SrcImg, point center, double radius, Color color);
	void drawLine(CImg<unsigned char> &SrcImg, point from, double angle, double len, Color color);
};

MyImage::MyImage() {}


//����һ������1.bmp�ļ�������CImg.display()��ʾ
void MyImage::processOne(CImg<unsigned char> &SrcImg) {
	SrcImg.display();
}


//���������1.bmp�ļ��İ�ɫ�����̺�ɫ����ɫ��������ɫ
void MyImage::processTwo(CImg<unsigned char> &SrcImg) {
	cimg_forXY(SrcImg, x, y) {
		if (SrcImg(x, y, 0) == 0 && SrcImg(x, y, 1) == 0 && SrcImg(x, y, 2) == 0) {
			SrcImg(x, y, 0) = 0;
			SrcImg(x, y, 1) = 255;
			SrcImg(x, y, 2) = 0; 
		}

		if (SrcImg(x, y, 0) == 255 && SrcImg(x, y, 1) == 255 && SrcImg(x, y, 2) == 255) {
			SrcImg(x, y, 0) = 255;
			SrcImg(x, y, 1) = 0;
			SrcImg(x, y, 2) = 0;
		}
	}
	SrcImg.display();
}


//����������ͼ�ϻ���һ��Բ������Բ������(50,50)���뾶Ϊ30�������ɫΪ��ɫ
//δʹ����CImg���ͼ�����Ĳ�����
void MyImage::processThree(CImg<unsigned char> &SrcImg) {
	point center(50, 50);
	double radius = 30;
	Color color(0, 0, 255);
	drawCircle(SrcImg, center, radius, color);
}


//ʹ����CImg���ͼ�����Ĳ�����
void MyImage::processThreeCImg(CImg<unsigned char> &SrcImg) {
	point center(50, 50);
	double radius = 30;
	unsigned char color[] = {0, 0, 255};
	SrcImg.draw_circle(center.x, center.y, radius, color);
}


//�����ģ���ͼ�ϻ���һ��ͼ������Բ������(50,50)���뾶Ϊ3�������ɫΪ��ɫ
//δʹ����CImg���ͼ�����Ĳ�����
void MyImage::processFour(CImg<unsigned char> &SrcImg) {
	point center(50, 50);
	double radius = 3;
	Color color(255, 255, 0);
	drawCircle(SrcImg, center, radius, color);	
}


//ʹ����CImg���ͼ�����Ĳ�����
void MyImage::processFourCImg(CImg<unsigned char> &SrcImg) {
	point center(50, 50);
	double radius = 3;
	unsigned char color[] = {255, 255, 0};
	SrcImg.draw_circle(center.x, center.y, radius, color);
}

//�����壺��ͼ�ϻ���һ�� ��ͼ�ϻ���һ�� ��Ϊ100��ֱ�߶Σ��������Ϊ�������Ϊ(0, 0)�������Ϊ35�ȣ�ֱ�ߵ���ɫΪ��ɫ
//δʹ����CImg���ͼ�����Ĳ�����
void MyImage::processFive(CImg<unsigned char> &SrcImg) {
	point from(0, 0);
	double angle = 35;
	double len = 100;
	Color color(0, 0, 255);
	drawLine(SrcImg, from, angle, len, color);
}

//ʹ����CImg���ͼ�����Ĳ�����
void MyImage::processFiveCImg(CImg<unsigned char> &SrcImg) {
	point from(0, 0);
	double angle = 35;
	double rad = convertToRad(angle);
	unsigned char color[] = {0, 0, 255};
	double to_x = 100 * cos(rad);
	double to_y = 100 * sin(rad);
	point to(to_x, to_y);
	SrcImg.draw_line(from.x, from.y, to.x, to.y, color);
}

//�����Ƿ�ѡ��ʹ����CImg���ͼ�����ĺ���������Ϊ��Ӧ��bmpͼƬ
//���ѡ�����ʹ����CImg���ͼ���������������0���������Ϊ2.bmp�����򱣴�Ϊ3.bmp
void MyImage::processSix(CImg<unsigned char> &SrcImg, int chooseNumber) {
	//With the use of CImg.
	if (chooseNumber == 0) {
		SrcImg.save("2.bmp");
	} 
	//Not use CImg.
	else if (chooseNumber == 1){
		SrcImg.save("3.bmp");
	}
}

//���������Ļ�Բ�����ĸ�������
void MyImage::drawCircle(CImg<unsigned char> &SrcImg, point center, double radius, Color color) {
	cimg_forXY(SrcImg, x, y) {
		double x1 = pow(x - center.x, 2);
		double y1 = pow(y - center.y, 2);
		double distance = sqrt(x1 + y1);

		if (distance <= radius) {
			SrcImg(x, y, 0) = color.red;
			SrcImg(x, y, 1) = color.green;
			SrcImg(x, y, 2) = color.blue;
		}
	}
}

//�����廭ֱ�߷����ĸ�������
void MyImage::drawLine(CImg<unsigned char> &SrcImg, point from, double angle, double len, Color color) {
	double rad = convertToRad(angle);
	double k = tan(rad);
	cimg_forXY(SrcImg, x, y) {
		int dis = from.y + k * (x - from.x);
		if (y == dis && x >= 0 && x <= len * cos(rad)) {
			SrcImg(x, y, 0) = color.red;
			SrcImg(x, y, 1) = color.green;
			SrcImg(x, y, 2) = color.blue;				
		}
	}
}

int main() {
	MyImage image;
	CImg<unsigned char> SrcImg;
	int chooseNumber = 0;
	SrcImg.load_bmp("1.bmp");
	cout << "If use CImg, then input 0, otherwise input 1" << endl;
	cout << "Please input the method number: ";
	cin >> chooseNumber;
	//������Ľ��Ϊ0���������ͼƬ��ʹ����CImg���ͼ�����Ľ��
	//�����Ҫ��������ĳһ���������뽫��Ӧ�ķ���ע�͵�
	if (chooseNumber == 0) {
		image.processOne(SrcImg);
		image.processTwo(SrcImg);
		image.processThreeCImg(SrcImg);
		image.processFourCImg(SrcImg);
		image.processFiveCImg(SrcImg);
		image.processSix(SrcImg, chooseNumber);		
	}

	//������Ľ��Ϊ1���������ͼƬ��δʹ��CImg���ͼ�����Ľ��
	//�����Ҫ��������ĳһ���������뽫��Ӧ�ķ���ע�͵�
	else if (chooseNumber == 1){
		image.processOne(SrcImg);
		image.processTwo(SrcImg);
		image.processThree(SrcImg);
		image.processFour(SrcImg);
		image.processFive(SrcImg);
		image.processSix(SrcImg, chooseNumber);		
	}
	return 0;
}

