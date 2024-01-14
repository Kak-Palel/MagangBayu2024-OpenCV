#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Mat gambar_gray;
// int thresh = 100;
// RNG rng(12345);

// void thresh_callback(int, void* )
// {
//     Mat canny_output;
//     Canny(gambar_gray, canny_output, thresh, thresh*2 );
//     vector<vector<Point> > contours;
//     findContours( canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );

//     vector<vector<Point> > contours_poly( contours.size() );
//     vector<Rect> boundRect( contours.size() );
//     vector<Point2f>centers( contours.size() );
//     vector<float>radius( contours.size() );

//     for( size_t i = 0; i < contours.size(); i++ )
//     {
//         approxPolyDP( contours[i], contours_poly[i], 3, true );
//         boundRect[i] = boundingRect( contours_poly[i] );
//         minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
//     }

//     Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );

//     for( size_t i = 0; i< contours.size(); i++ )
//     {
//         Scalar color = Scalar(0, 0, 255);
//         drawContours( drawing, contours_poly, (int)i, color );
//         rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2 ); 
//         // circle( drawing, centers[i], (int)radius[i], color, 2 );
//     }
//     imshow("Contours", drawing);
// }

Scalar greenLow = Scalar(65, 127, 51);
Scalar greenHigh = Scalar(90, 255, 255);

int main()
{
    Mat gambar;

    gambar = imread("C:/Users/farre/projects/Magang OpenCV/tugas1.png");
    if ( !gambar.data )
    {
        printf("Banh gambarnya mana banh\n");
        return -1;
    }

    imshow("Ni paus aseli", gambar);

    Mat gambar_background;
    gambar.copyTo(gambar_background);

    Mat mask;
    cvtColor(gambar, gambar, COLOR_BGR2HSV);
    inRange(gambar, greenLow, greenHigh, mask);

    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // drawContours(gambar_background, contours, -1, (0, 255, 0), 3);

    for(size_t i = 0; i < contours.size(); ++i)
    {
        Rect boundRect = boundingRect(contours[i]);
        if(boundRect.area()>500 && (boundRect.width < 100 || boundRect.height < 100))
        {
            rectangle(gambar_background, boundRect.tl(), boundRect.br(), Scalar(0, 0, 255), 3);
        }
    }

    // namedWindow("Ni paus dek", WINDOW_AUTOSIZE );
    imshow("Ni paus dikotak", gambar_background);
    // imshow("Ijo", mask);

    // const int max_thresh = 255;
    // createTrackbar( "Canny thresh:", "Ni paus dek", &thresh, max_thresh, thresh_callback );
    // thresh_callback( 0, 0 );

    waitKey(0);
    return 0;
}