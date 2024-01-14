#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//batas batas value hsv warna hijau
Scalar greenLow = Scalar(65, 127, 51);
Scalar greenHigh = Scalar(90, 255, 255);

int main()
{
    //ni gambar dek  
    Mat gambar;

    gambar = imread("C:/Users/farre/projects/Magang OpenCV/tugas1.png");
    if ( !gambar.data )
    {
        printf("Banh gambarnya mana banh\n");
        return -1;
    }

    //gambarnya ditunjukin dek
    imshow("Ni paus aseli", gambar);

    //gambarnya di copy hehe
    Mat gambar_background;
    gambar.copyTo(gambar_background);

    Mat mask;
    cvtColor(gambar, gambar, COLOR_BGR2HSV);     //ganti ke hsv biar tampilannya kayak habis nyedot bubuk bahagia
    inRange(gambar, greenLow, greenHigh, mask);  //deteksi warna hijau, hasilnya masukin ke gambar "mask"

    //deteksi contours mask
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // drawContours(gambar_background, contours, -1, (0, 255, 0), 3); //ini gajadi hehe

    //gambar kotak berdasarkan contour yang ditemuin di gambar_background
    for(size_t i = 0; i < contours.size(); ++i)
    {
        Rect boundRect = boundingRect(contours[i]);
        if(boundRect.area()>500 && (boundRect.width < 100 || boundRect.height < 100)) //ini buat nge filter kotak kotak kecil yg gaguna
        {
            rectangle(gambar_background, boundRect.tl(), boundRect.br(), Scalar(0, 0, 255), 3);
        }
    }

    //jangan lupa di tunjukin dek gambarnya
    imshow("Ni paus dikotak", gambar_background);

    //ni biar ga langsung keluar
    waitKey(0);
    return 0;
}

//yauda si wir itu ajah, -Farrel Ganendra 5024231036
