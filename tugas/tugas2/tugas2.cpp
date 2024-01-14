#include <stdio.h>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    //gambar
    Mat gambar;

    gambar = imread("C:/Users/farre/projects/Magang OpenCV/tugas2.jpg");
    if ( !gambar.data )
    {
        printf("Banh gambarnya mana banh\n");
        return -1;
    }

    //tunjukin gambarnya sebelum di prosess
    imshow("Ni gambar aseli", gambar);

    //di copy hehe
    Mat gambar_background;
    gambar.copyTo(gambar_background);

    //ini masking yang warna biru doang sama di blur (somehow jumlah contours nya lebih sedikit kalo di blur which means lebih akurat)
    Mat mask;
    cvtColor(gambar, gambar, COLOR_BGR2HSV);
    blur(gambar, gambar, Size(3, 3));
    inRange(gambar, Scalar(80, 200, 200), Scalar(150, 255, 255), mask);

    //ngitung contours
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    //hapus semua contours kecuali yang buat bentuk 'H'
    while(contours.size() > 1)
    {
        contours.erase(contours.begin()+1);
    }

    //gambar contours nya hehe
    drawContours(gambar_background, contours, -1, (0, 255, 0), 3);

    //ini nyari jumlah sudut, bentuk 2d pasti jumlah sisi sama sudutnya sama kecuali lingkaran
    vector<Point> sudut;
    approxPolyDP(contours[0], sudut, arcLength(contours[0], true)*0.02, true);

    //ini jumlah sisi nya di tarok di gambar
    const string jumlahSudutString = to_string(sudut.size());
    putText(gambar_background, jumlahSudutString, Point(30, 100), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 0), 2);

    //nampilin hasil akhir
    imshow("Ni gambar final", gambar_background);

    //udaaahhh yeyeyeyyeye
    waitKey(0);
    return 0;
}

//bang udah bang
