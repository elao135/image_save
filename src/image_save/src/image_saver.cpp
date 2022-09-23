#include <ros/ros.h>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <std_msgs/UInt8MultiArray.h>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;
stringstream ss;

cv::Mat decode;

void imageCallback(const sensor_msgs::CompressedImageConstPtr& msg)
{

    decode = cv::imdecode(cv::Mat(msg->data), 1);    
    cv::waitKey(1);
}

void Saved_Image(int num_images)
{
    std::stringstream filename;
    filename << "/home/cona/db_ws/src/image_save/save_fold"<< "/" << "image" << num_images << ".jpg";
    cv::imwrite(filename.str(), decode);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "video_in");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("usb_cam/image_raw/compressed", 100, imageCallback);
    int num_images=0;
    while(ros::ok())
    {
        ros::Rate loop_rate(1);
        loop_rate.sleep();        
        ros::spinOnce();
        Saved_Image(num_images++);
    }

/*     for (int num_image=0; num_image<25; num_image++)
    {
        std::stringstream filename;
        filename << "/home/cona/catkin_ws/src/image_save/save_fold"<< "/" << "image" << num_image << ".jpg";
        Mat img = imread(filename.str(), IMREAD_GRAYSCALE);

        if (img.empty())
        {
            cerr << "failed to read image" << endl;
        }
        Mat blurred_img;
        blur(img, blurred_img, Size(5,5));
	    char mystr[30];
	    string myText = "blurring";
	    putText(blurred_img, myText, Point(200, 200), 1, 2, Scalar(255, 255, 0), 1, 8);

        imshow("blurred image", blurred_img);
        cv::waitKey(1000);

    }

    for (int num_image=25; num_image<50;num_image++)
    {
        std::stringstream filename;
        filename << "/home/cona/catkin_ws/src/image_save/save_fold"<< "/" << "image" << num_image << ".jpg";
        Mat img = imread(filename.str(), IMREAD_GRAYSCALE);

        Mat blur_gaussian;
        GaussianBlur(img, blur_gaussian,Size(5,5), 1);
	    string myText = "gaussian_blurring";
	    putText(blur_gaussian, myText, Point(200, 200), 1, 2, Scalar(255, 255, 0), 1, 8);        
        imshow("gaussian_blurred image", blur_gaussian);
        cv::waitKey(1000);
    }

    for (int num_image=50; num_image<100;num_image++)
    {
        std::stringstream filename;
        filename << "/home/cona/catkin_ws/src/image_save/save_fold"<< "/" << "image" << num_image << ".jpg";
        Mat img = imread(filename.str(), IMREAD_GRAYSCALE);

        float data[9] = {-1.0,-1.0,-1.0,-1.0,9.0,-1.0,-1.0,-1.0,-1.0};
        Mat kernel(3, 3, CV_32FC1, data);
        
        Mat sharp;
        filter2D(img, sharp, -1, kernel);

        Mat dst;
        addWeighted(img, 0.6, sharp, 0.4, 0, dst);
	    string myText = "sharpening";
	    putText(dst, myText, Point(200, 200), 1, 2, Scalar(255, 255, 0), 1, 8);
        imshow("sharpening", dst);
        cv::waitKey(1000); */


    /* } */
}