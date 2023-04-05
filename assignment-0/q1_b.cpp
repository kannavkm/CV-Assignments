#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    Mat src;
    if (argc < 4) {
        cerr << "Wrong arguments provided\n";
        return -1;
    }
    vector<string> files{argv + 2, argv + argc};
    VideoWriter writer;
    double fps = stod(argv[1]);
    cout << "Frames per second: " << fps << "\n";
    int codec = VideoWriter::fourcc('m', 'p', '4', 'v');
    src = imread(files[0], IMREAD_COLOR);
    writer.open("./output.mp4", codec, fps, src.size());
    if (!writer.isOpened()) {
        cerr << "Could not open the output video file for write\n";
        return -1;
    }
    for (auto &x: files) {
        src = imread(x, IMREAD_COLOR);
        writer.write(src);
    }
    return 0;
}