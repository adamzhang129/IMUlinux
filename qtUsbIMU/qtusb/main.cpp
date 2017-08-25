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
// #include <c/thread/mutex.hpp>
#include <camera_info_manager/camera_info_manager.h>

sensor_msgs::CameraInfo cam_info_left;
sensor_msgs::CameraInfo cam_info_right;

typedef camera_info_manager::CameraInfoManager CameraInfoManager;

//Instantiate publishers
image_transport::Publisher pubImgLeft;
image_transport::Publisher pubImgRight;
ros::Publisher pubImu;



// using namespace cv;
int main(int argc, char *argv[])
{
    

    
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh("~");
    cout<<"image_tranport----" << nh.getNamespace()<<endl;

    image_transport::ImageTransport it(nh);

    pubImgLeft = it.advertise("/stereo/right/image_raw", 1);
    pubImgRight = it.advertise("/stereo/left/image_raw", 1);
    pubImu = nh.advertise<sensor_msgs::Imu>("/stereo/Imu", 1); 

    

    sensor_msgs::ImagePtr imgMsgLeft;
    sensor_msgs::ImagePtr imgMsgRight;
    sensor_msgs::Imu msgImu;
  
    // QImage img;
    QImage imgRight;
    QImage imgLeft;

    ros::NodeHandle nh_left("~set_camera_info_left"), nh_right("~set_camera_info_right");

    CameraInfoManager cam_info_manager_left(nh_left);
    CameraInfoManager cam_info_manager_right(nh_right);
  
    const std::string cname_left = "stereoleft";
    const std::string cname_right = "stereoright";
  
    cam_info_manager_left.setCameraName(cname_left);
  
    const std::string camera_info_url_left =
        "./calibration/stereoleft.yaml";
  
    if (cam_info_manager_left.validateURL(camera_info_url_left)) {
      cam_info_manager_left.loadCameraInfo(camera_info_url_left);
    }
  
    cam_info_manager_right.setCameraName(cname_right);
    const std::string camera_info_url_right =
        "./calibration/stereoright.yaml";
  
    if (cam_info_manager_right.validateURL(camera_info_url_right)) {
      cam_info_manager_right.loadCameraInfo(camera_info_url_right);
    }
  
    sensor_msgs::CameraInfo camera_info_left;
    sensor_msgs::CameraInfo camera_info_right;
  
    camera_info_left = cam_info_manager_left.getCameraInfo();
    camera_info_right = cam_info_manager_right.getCameraInfo();
  
    ros::Publisher pubCamInfoLeft =
        nh_left.advertise<sensor_msgs::CameraInfo>("/stereo/left/camera_info", 1);
    ros::Publisher pubCamInfoRight = 
        nh_right.advertise<sensor_msgs::CameraInfo>("/stereo/right/camera_info", 1);

    cout<< "left-----" <<  nh_left.getNamespace() <<endl;
    cout<<"right-----" << nh_right.getNamespace()   <<endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    ros::Rate loop_rate(10);
    // while (nh.ok()) {
    //     ros::Time time_in_this_loop = ros::Time::now();
    //     //processing left and right images===========
    //     imgLeft = w.img2ROSLeft;
    //     imgRight = w.img2ROSRight;

    //     cv::Mat  matLeft( imgLeft.height(), imgLeft.width(),
    //                 CV_8UC1,
    //                 const_cast<uchar*>(imgLeft.bits()),
    //                 static_cast<size_t>(imgLeft.bytesPerLine())
    //                 );
    //     cv::Mat  matRight( imgRight.height(), imgRight.width(),
    //                 CV_8UC1,
    //                 const_cast<uchar*>(imgRight.bits()),
    //                 static_cast<size_t>(imgRight.bytesPerLine())
    //                 );
    //     imgMsgLeft = cv_bridge::CvImage(std_msgs::Header(), "mono8", matLeft).toImageMsg();
    //     imgMsgLeft->header.frame_id = "stereo";
    //     imgMsgLeft->header.stamp = time_in_this_loop;

    //     imgMsgRight = cv_bridge::CvImage(std_msgs::Header(), "mono8", matRight).toImageMsg();
    //     imgMsgRight->header.frame_id = "stereo";
    //     imgMsgRight->header.stamp = time_in_this_loop;
    //     // imgMsgLeft.header.frame_id
        
    //     pubImgLeft.publish(imgMsgLeft);
    //     pubImgRight.publish(imgMsgRight);

        
        
    //     // processing Imu data=========================
    //     msgImu.header.frame_id = "stereo";
    //     msgImu.header.stamp = time_in_this_loop;

    //     msgImu.linear_acceleration.x =  w.m_IMU2ROS->accelData[0];
    //     msgImu.linear_acceleration.y =  w.m_IMU2ROS->accelData[1];
    //     msgImu.linear_acceleration.z =  w.m_IMU2ROS->accelData[2];
    //     msgImu.angular_velocity.x =  w.m_IMU2ROS->gyroData[0];
    //     msgImu.angular_velocity.y =  w.m_IMU2ROS->gyroData[1];
    //     msgImu.angular_velocity.z =  w.m_IMU2ROS->gyroData[2]; 

    //     pubImu.publish(msgImu);            
        
    //     pubCamInfoLeft.publish(camera_info_left);
    //     pubCamInfoRight.publish(camera_info_right);

    //     ros::spinOnce();
    //     loop_rate.sleep();

    //     qApp->processEvents();// force QT to process this loop
    // }
    
    
    return a.exec();
}
