
#include "picHistos.h"


MatND Histons :: parse(Mat img) {

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


void Histons :: set_images(Mat imone, Mat imtwo){
      cvone=imone;
      cvtwo=imtwo;

    }

void Histons :: load_images(string imone, string imtwo){
      cvone=imread(imone, 1 );
      cvtwo=imread(imtwo, 1 );
      cout << "[+] File One:" << "\t" << imone << endl;
      cout << "[+] File Two:" << "\t" << imtwo << endl;
    }

double Histons :: process_images() {
      Mat histone;
      Mat histtwo;
      compare_method=1;
      //parse images
      histone=parse(cvone);
      histtwo=parse(cvtwo);
      //grade it
      return compareHist( histone, histtwo, compare_method );
    }



int main (int argc, char* argv[]) {

  if (argc > 1){

    if (argc != 5){
      cout << "[- FAIL -] • [ Usage: " << argv[0] << " -i1 image -i2 image ]" << endl;
      return 0;
    }

    string im1, im2;

    for (int i=0; i < argc; i++){
      if (strcmp(argv[i], "-i1") == 0){
        im1=argv[i+1];
      }
      if  (strcmp(argv[i], "-i2") == 0){
        im2=argv[i+1];
      }
    }

    Histons hist;
    hist.load_images(im1, im2);
    cout << "[+] Hist-Comp-Grade: " << hist.process_images() << endl;

  }
return 0;
}
