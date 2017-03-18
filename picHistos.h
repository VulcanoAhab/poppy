// include guard
#ifndef __Histons_H_INCLUDED__
#define __Histons_H_INCLUDED__

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
  MatND parse(Mat img);


  public:
    void set_images(Mat imone, Mat imtwo);
    void load_images(string imone, string imtwo);
    double process_images();


};


#endif
