#pragma once

#include <ros/ros.h>
#include <iostream>
#include <chrono>

#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include "rogi_link_msgs/RogiLink.h"


class Servo_Ctrl
{
    public:
    Servo_Ctrl();
    ~Servo_Ctrl(){};

    private:
    //Handles
    ros::NodeHandle &nh;
    ros::Publisher ctrl_servo;
    ros::Subscriber cmd_theta;

    //configurations
    int loop_rate;
    int s_id;
    int period;//パルス周期（ms）
    int range;//最大回転角（deg）
    int min_p_width;//0度の時のパルス幅
    int max_p_width;//最大の時のパルス幅
    int lost_time_threshold;
    bool gazebo_mode;

    //variables
    float theta;

    //flags
    bool emergency_stop_flag;

    //Timers
    std::chrono::system_clock::time_point last_sub_vel_time_;

    //Methods
    void init_Handles();
    void init_variables();
    void cmdvelCallback(const std_msgs::Float64 &arg);
    void EmergencyStopFlagCallback(const std_msgs::Empty::ConstPtr &msg);
    bool isSubscribed();
    void publishMsg();
    void cmd_servo();
    void reset();
    void update();

};