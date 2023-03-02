//
// Created by kook on 22-11-18.
//

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <math.h>
#include <geometry_msgs/Twist.h>

ros::Publisher pub;

void scan_callback(const sensor_msgs::LaserScan scan_msg) {
    //定义一个物体的方位，可以通过x，y以及对应的角度得出
    //可将圆柱体看成在一个圆上，半径是最小激光距离
    float  x;
    float  y;
    float  angle;

    float Distance_min = 100;
    int i;
    for( i=0 ; i<360 ; i++ ) //在ros index里面查到range数组的大小为360
    {
        if(Distance_min > scan_msg.ranges[i])
        {
            Distance_min = scan_msg.ranges[i];
            angle= (scan_msg.angle_min + i*scan_msg.angle_increment);
        }
    }  // 找到最小的激光距离和角度(也就是圆柱体到机器人的连线)

    x=Distance_min*cos(angle);
    y=Distance_min*sin(angle);

    ROS_INFO("The minimal distance is %f mile",Distance_min);
    ROS_INFO("The object's x distance is %f mile",x);
    ROS_INFO("The object's y distance is %f mile",y);
    ROS_INFO("The object's angle is %f rad",angle);

    //控制机器人向圆柱体移动
    geometry_msgs::Twist msgs;
    if(angle>0)
    {
          msgs.angular.z=angle;
    }
    else
    {
        msgs.angular.z=0;
    }
    msgs.linear.x=0.5;
    msgs.linear.y=0.5;

    pub.publish(msgs);


}

int main(int argc, char* argv[]) {

    ros::init(argc, argv, "smb_location");
    ros::NodeHandle nh;

    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Subscriber sub=nh.subscribe("/scan",10,&scan_callback);
    ros::Rate loopRate(10);


    while (ros::ok()) {

        ros::spinOnce();
        loopRate.sleep();
    }

    return 0;

}