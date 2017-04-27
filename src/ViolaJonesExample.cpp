// ViolaJonesExample.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

#define CLASSIFIER_FILE "src/haarcascade_frontalface_alt.xml"

#define SCALING_FACTOR			1.1
#define MIN_NEIGHBORS			10
#define FACE_MIN_WIDTH			60
#define FACE_MIN_HEIGHT			60
#define FACE_MAX_WIDTH			800
#define FACE_MAX_HEIGHT			800

int main(int argc, char* argv[])
{
	//Caricamento del classificatore
	CascadeClassifier face_cascade;
	if(!face_cascade.load(CLASSIFIER_FILE)){
		cout << "Error loading classifier" << endl;
		return 1;
	}
	Mat cap_img, gray_img;
	vector<Rect> faces;

	//Apertura del flusso video da webcam
	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout << "Error initializing camera" << endl;
		return 1;
	}
	
	//Ciclo di elaborazione
	while(cap.isOpened()){
		if(cap.grab()){
			cap.retrieve(cap_img);
			cvtColor(cap_img, gray_img, CV_BGR2GRAY);
			//Applicazione dell'algoritmo di Viola-Jones
			face_cascade.detectMultiScale(gray_img, faces, SCALING_FACTOR, MIN_NEIGHBORS, 0, cvSize(FACE_MIN_WIDTH,FACE_MIN_HEIGHT), cvSize(FACE_MAX_WIDTH,FACE_MAX_HEIGHT));
			//Disegno dei bounding box intorno ai volti
			for(int i = 0; i < faces.size(); i++){
				Point pt1(faces[i].x+faces[i].width, faces[i].y+faces[i].height);
				Point pt2(faces[i].x, faces[i].y);
				rectangle(cap_img, pt1, pt2, cvScalar(0,0,255), 2, 8, 0);
			}
			imshow("Result", cap_img);
			waitKey(1);
		}
		else{
			cap.release();
		}
	}

	

	return 0;
}
