#include <iostream>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/video.hpp"


using namespace cv;
using namespace std;


double getPSNR(const Mat& I1, const Mat& I2) {

  //카이제곱 :: OpenCV Scene Change Detection(장면 전환 검출)
  // prototype testing

  Mat s1;
  absdiff(I1, I2, s1); // |I1 - I2|
  s1.convertTo(s1, CV_32F); // cannot make a square on 8 bits
  s1 = s1.mul(s1); // |I1 - I2|^2
  Scalar s = sum(s1); // sum elements per channel
  double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

  if (sse <= 1e-10) return 0;

  double mse = sse / (double)(I1.channels() * I1.total());
  double psnr = 10.0*log10((255 * 255) / mse);
  return psnr;


}

void merge(const Mat &m1, Mat &result) {
  resize(result, result, Size(m1.cols,  m1.rows));
  m1.copyTo(result(Rect(0, 0, m1.cols, m1.rows)));
}

void processVideo(char* videoFilename) {

  //set values
  double psnrV, CHANGE_DETECT_RATIO = 15.0;
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
