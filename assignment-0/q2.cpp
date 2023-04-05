#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <filesystem>
#include <iostream>

using namespace cv;
using namespace std;

namespace fs = std::filesystem;

int main(int, char **) {
    VideoCapture videoCapture(0);
    if (!videoCapture.isOpened()) {
        cerr << "Camera file not found\n";
        return -1;
    }
    double fps = videoCapture.get(CAP_PROP_FPS);
    cout << "Frames per second : " << fps << endl;
    if (!fs::is_directory("./output") || !fs::exists("./output")) {
        fs::create_directory("./output");
    }
    TickMeter tm;
    Mat src;
    for (size_t frame = 0;; frame++) {
        tm.start();
        if (!videoCapture.read(src)) {
            cout << "Video Terminated, frames read: " << frame << "\n";
            break;
        }
        string outFile = "./output/" + to_string(frame) + ".jpg";
        imwrite(outFile, src);
        imshow("Live Video", src);
        if (waitKey(1) >= 0) {
            break;
        }
        tm.stop();
    }
    cout << "We played it back at " << tm.getFPS() << endl;
    return 0;
}