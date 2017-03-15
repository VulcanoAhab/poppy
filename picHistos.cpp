#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;


class Histons {

  private:
    Mat cvone;
    Mat cvtwo;
    int compare_method;


    MatND parse(Mat img) {

      Mat hsv;
      MatND hist;
      //parse color system
      cvtColor(img, hsv, COLOR_BGR2HSV);
      // Using 50 bins for hue and 60 for saturation
      int h_bins = 50; int s_bins = 60;
      int histSize[] = { h_bins, s_bins };
      // hue varies from 0 to 179, saturation from 0 to 255
      float h_ranges[] = { 0, 180 };
      float s_ranges[] = { 0, 256 };
      const float* ranges[] = { h_ranges, s_ranges };
      // Use the o-th and 1-st channels
      int channels[] = { 0, 1 };
      //build hist
      calcHist( &hsv, 1, channels, Mat(), hist, 2,
              histSize, ranges, true, false );
      normalize( hist, hist, 0, 1, NORM_MINMAX, -1, Mat() );
      return hist;
    }


  public:

    void load_images(string imone, string imtwo){
      cvone=imread(imone, 1 );
      cvtwo=imread(imtwo, 1 );
      cout << "[+] File One:" << "\t" << imone << endl;
      cout << "[+] File Two:" << "\t" << imtwo << endl;
    }

    double process_images() {
      Mat histone;
      Mat histtwo;
      compare_method=1;
      //parse images
      histone=parse(cvone);
      histtwo=parse(cvtwo);
      //grade it
      return compareHist( histone, histtwo, compare_method );
    }

};


int main () {

  Histons hist;
  return 0;
}
