#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Wrong number of arguments provided\n";
        return -1;
    }
    VideoCapture videoCapture(argv[1]);
    if (!videoCapture.isOpened()) {
        cerr << "Video file not found\n";
        return -1;
    }
    string outDir{argv[2]};
    if (outDir.back() != '/') {
        outDir += '/';
    }
    if (!fs::is_directory(outDir) || !fs::exists(outDir)) {
        fs::create_directory(outDir);
    }
    Mat src;
    for (size_t frame = 0;; frame++) {
        if (!videoCapture.read(src)) {
            cout << "Reading done, frames captured: " << frame << "\n";
            break;
        }
        // write out the image to the file
        string outFile = outDir + to_string(frame) + ".jpg";
        imwrite(outFile, src);
    }
    return 0;
}