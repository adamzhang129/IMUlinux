#include <QtGui/QApplication>
//#include <QApplication>
#include "mainwindow.h"

#include <ros/ros.h>
#include <sstream>
#include "std_msgs/String.h"

#include <image_transport/image_transport.h>

// #include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


#include <QImage>



// using namespace cv;
int main(int argc, char *argv[])
{
    


    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);
    
    // cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    // cv::Mat image;
    // cv::cvtColor(image1,image,CV_RGB2GRAY);
    sensor_msgs::ImagePtr msg;
  
    ros::Rate loop_rate(15);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    
    QImage img;
    QImage imgRight;
    
    while (nh.ok()) {
        
        img = w.output2ROSImg;

        cv::Mat  mat( img.height(), img.width(),
                    CV_8UC1,
                    const_cast<uchar*>(img.bits()),
                    static_cast<size_t>(img.bytesPerLine())
                    );
        
        
        msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", mat).toImageMsg();

        pub.publish(msg);
        
        qApp->processEvents();
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    
    return a.exec();
}
