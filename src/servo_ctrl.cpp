#include "servo_ctrl.h"

Servo_Ctrl::Servo_Ctrl(ros::NodeHandle &_nh, const int &_loop_rate, const int &_s_id, const int &_period,
                const int &_range, const int &_min_p_width, const int &_max_p_width,
                const int &_lost_time_threshold, const bool &_gazebo_mode)
                :nh(_nh),loop_rate(_loop_rate),s_id(_s_id),period(_period),
                range(_range),min_p_width(_min_p_width),max_p_width(_max_p_width),
                lost_time_threshold(_lost_time_threshold),gazebo_mode(_gazebo_mode)
{
    ROS_INFO("Creating omni_wheelctrl");
    ROS_INFO_STREAM("loop_rate [Hz]: " << loop_rate);
    ROS_INFO_STREAM("msg_id: " << s_id);
    ROS_INFO_STREAM("PWM period [ms]: " << period);
    ROS_INFO_STREAM("range: " << range);
    ROS_INFO_STREAM("min_pulse_width [us]: " << min_p_width);
    ROS_INFO_STREAM("max_pulse_width [us]: " << max_p_width);
    ROS_INFO_STREAM("lost_time_threshold [ms]: " << lost_time_threshold);
    ROS_INFO_STREAM("gazebo_mode: " << gazebo_mode);

    init_variables();
    if(gazebo_mode)
    {
        ROS_INFO("I Don't Prepare Gazebo Mode, sorry :-(");
    }else{
         control_pub = nh.advertise<rogi_link_msgs::RogiLink>(
            "send_serial", 1);
    }
    cmd_theta = nh.subscribe
}

