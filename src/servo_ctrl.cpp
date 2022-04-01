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
         ctrl_servo = nh.advertise<rogi_link_msgs::RogiLink>(
            "send_serial", 1);
    }
    cmd_theta = nh.subscribe("/cmd_servo",1,&Servo_Ctrl::cmdsrvCallback,this);
    emergency_stop_sub = nh.subscribe("/emergency_stop_flag", 1,
                                &Servo_Ctrl::EmergencyStopFlagCallback, this);
    init_Handles();

    last_sub_vel_time = std::chrono::system_clock::now();

    update();
}

void Servo_Ctrl::init_Handles()
{
    rogi_link_msgs::RogiLink init_msg;
    // Wait Mr.Yoshida
    // init_msg.id = hoge;
    // init_msg.date[0] = hogehoge;
    ctrl_servo.publish(init_msg);
}

void Servo_Ctrl::init_variables()
{
    theta = 0;
    msg_id = (char)s_id;
}

void Servo_Ctrl::cmdsrvCallback(const std_msgs::Float64 &arg)
{
    
}

void Servo_Ctrl::EmergencyStopFlagCallback(const std_msgs::Empty::ConstPtr &msg)
{
    emergency_stop_flag = !emergency_stop_flag;
}

bool Servo_Ctrl::isSubscribed()
{
    auto current_time = std::chrono::system_clock::now();
    const auto vel_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                             current_time - last_sub_vel_time_).count();

    if (vel_elapsed < lost_time_threshold_) {
        return true;
    } else {
        return false;
    }
}

void Servo_Ctrl::publishMsg()
{
    rogi_link_msgs::RogiLink control_msg;
    //Wait Mr.Yoshida
    //control_msg.id = hoge;
    //*(float *)(&control_msg.data[0]) = theta;
    ctrl_servo.publish(control_msg);
}

void Servo_Ctrl::cmd_servo()
{

}

void Servo_Ctrl::reset()
{

}

void Servo_Ctrl::Update()
{

}