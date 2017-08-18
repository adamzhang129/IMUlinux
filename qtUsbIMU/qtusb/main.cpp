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

#include <sensor_msgs/Imu.h>



// using namespace cv;
int main(int argc, char *argv[])
{
    


    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pubLeft = it.advertise("camera/image/left", 1);
    image_transport::Publisher pubRight = it.advertise("camera/image/right", 1);
    ros::Publisher pubImu = nh.advertise<sensor_msgs::Imu>("Imu", 1);
    
    // cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    // cv::Mat image;
    // cv::cvtColor(image1,image,CV_RGB2GRAY);
    sensor_msgs::ImagePtr msgLeft;
    sensor_msgs::ImagePtr msgRight;
    sensor_msgs::Imu msgImu;
  
    ros::Rate loop_rate(15);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    
    // QImage img;
    QImage imgRight;
    QImage imgLeft;

    IMUDataStruct*mIMU;
    
    while (nh.ok()) {
        
        imgLeft = w.img2ROSLeft;
        imgRight = w.img2ROSRight;

        cv::Mat  matLeft( imgLeft.height(), imgLeft.width(),
                    CV_8UC1,
                    const_cast<uchar*>(imgLeft.bits()),
                    static_cast<size_t>(imgLeft.bytesPerLine())
                    );
        cv::Mat  matRight( imgRight.height(), imgRight.width(),
                    CV_8UC1,
                    const_cast<uchar*>(imgRight.bits()),
                    static_cast<size_t>(imgRight.bytesPerLine())
                    );
        
        
        msgLeft = cv_bridge::CvImage(std_msgs::Header(), "mono8", matLeft).toImageMsg();
        msgRight = cv_bridge::CvImage(std_msgs::Header(), "mono8", matRight).toImageMsg();
        msgImu.linear_acceleration.x =  w.m_IMU2ROS->accelData[0];
        msgImu.linear_acceleration.y =  w.m_IMU2ROS->accelData[1];
        msgImu.linear_acceleration.z =  w.m_IMU2ROS->accelData[2];
        msgImu.angular_velocity.x =  w.m_IMU2ROS->gyroData[0];
        msgImu.angular_velocity.y =  w.m_IMU2ROS->gyroData[1];
        msgImu.angular_velocity.z =  w.m_IMU2ROS->gyroData[2];               
        pubImu.publish(msgImu);            
        
        pubLeft.publish(msgLeft);
        pubRight.publish(msgRight);


        qApp->processEvents();
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    
    return a.exec();
}
