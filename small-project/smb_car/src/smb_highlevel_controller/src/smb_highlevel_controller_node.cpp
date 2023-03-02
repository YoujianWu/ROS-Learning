//
// Created by kook on 22-11-19.
//
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>


void scan_callback(const sensor_msgs::LaserScan scan_msg) {
    float Distance_min = 100;
    int i=0;
    for( i=0 ; i<360 ; i++ ) //在ros index里面查到range数组的大小为360
    {
        if(Distance_min > scan_msg.ranges[i])
        {
            Distance_min = scan_msg.ranges[i];
        }
    }
    ROS_INFO("The minimal distance is %f mile",Distance_min);

}

int main(int argc, char* argv[]) {

    ros::init(argc, argv, "smb_highlevel_controller_node");
    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("/scan",10,&scan_callback);
    //ros::Rate loopRate(10);

    while (ros::ok()) {

        ros::spinOnce();
        // loopRate.sleep();

    }
    return 0;

}