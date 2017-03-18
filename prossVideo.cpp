#include <iostream>
#include "picHistos.h"


void merge(const Mat &m1, Mat &result) {
  resize(result, result, Size(m1.cols,  m1.rows));
  m1.copyTo(result(Rect(0, 0, m1.cols, m1.rows)));
}


void processVideo(char* videoFilename) {

  //set values
  double histComp;
  char control;

  //create the capture object
  VideoCapture capture(videoFilename);
  if(!capture.isOpened()){
    //error in opening the video input
    cerr << "[-] Unable to open video file: " << videoFilename << endl;
    exit(EXIT_FAILURE);
  }
  //results
  namedWindow("Scene Change Detection");
  Size frameSize = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
                        (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
  //frames deal
  int frames_total=capture.get(CV_CAP_PROP_FRAME_COUNT);
  cout << "[+] Loaded video. Frames total: " << frames_total << endl;
  Mat frame, prevFrame, posFrame, result(frameSize, CV_8UC3);

  //iter video
  for (int i=0; i < frames_total; i++){

    if (!capture.read(frame)){break;}

    if (i < 1) {
        prevFrame = frame.clone();
        posFrame = frame.clone();
        continue;
    }


    psnrV = getPSNR(prevFrame, frame);

    if (psnrV < CHANGE_DETECT_RATIO)
        posFrame = frame.clone();

    if (i % 2 == 0)
        prevFrame = frame.clone();

    merge(posFrame, result);
    imshow("Scene Change Detection", result);

    control = (char)waitKey(10);
    if (control==27){break;}

  }

}

int main( int argc, char** argv )
{

    processVideo(argv[1]);

    waitKey(0);
    return 0;
}
