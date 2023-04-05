#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/**
 *
 * @param a the image with the forground obj
 * @param b the new background
 * @return
 */
Mat blue_screen_matting(Mat a, Mat b) {
    // extract foreground
//    vector<double> Ck{249, 100, 47};
//    vector<double> Ck{103, 199, 99};
    vector<double> Ck{0, 255, 0};
    double a2 = 1.27;
    double a1 = 1.0 / (Ck[1] - a2 * Ck[0]);
    cout << a1 << " " << a2 << endl;
    Mat img[3];
    split(a, img);
//    cout << img[0] << endl;
    Mat alpha1 = /*max(0, min(1.0,*/ 1 - a1 * (min(Ck[1], img[1]) - a2 * img[0]);
    Mat alphaexp;
    exp((0.5 - alpha1) * 20, alphaexp);
    Mat alpha = 1.0 / (1.0 + alphaexp);
//    show_float_image("alpha", alpha * 255);
//    cout << alpha << endl;
    Mat bgrf[3];
    for (int i = 0; i < 3; i++) {
        bgrf[i] = img[i] - (1 - alpha) * Ck[i];
    }
    Mat dst, mat;
    vector<cv::Mat> copies{1 - alpha, 1 - alpha, 1 - alpha};
    cv::merge(copies, mat);
    merge(bgrf, 3, dst);

//    show_float_image("foreground", dst);
//    show_float_image("back", b);
//    show_float_image("image", a);
    Mat final = dst + b.mul(mat, 1.0);
//    show_float_image("Result", final);
    Mat temp;
    final.convertTo(temp, CV_8U);
    return temp;
//    waitKey(0);
}

int main(int, char **) {
    VideoCapture videoCapture("../data/dino.mp4");
    if (!videoCapture.isOpened()) {
        cerr << "Video"
                " file not found\n";
        return -1;
    }
    double fps = videoCapture.get(CAP_PROP_FPS);
    cout << "Frames per second : " << fps << endl;
    TickMeter tm;
    Mat src;

    Mat back = cv::imread("../data/base.jpg", cv::IMREAD_COLOR);
    Mat back2;
    back.convertTo(back2, CV_32F);


    VideoWriter writer;
    int codec = VideoWriter::fourcc('m', 'p', '4', 'v');
    writer.open("./output.mp4", codec, fps, Size(2560, 1440));

    for (size_t frame = 0;; frame++) {
        tm.start();
        if (!videoCapture.read(src)) {
            cout << "Video Terminated, frames read: " << frame << "\n";
            break;
        }
        Mat src2;
        src.convertTo(src2, CV_32F);
        Mat temp = blue_screen_matting(src2, back2);
        writer.write(temp);
        tm.stop();
    }
    cout << "We played it back at " << tm.getFPS() << endl;
    return 0;
}