#include <ros/ros.h>

std::string node_name = "servo_ctrl";

int main(int argc, char **argv)
{
    ros::init(argc, argv, node_name);
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    /**
    if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                       ros::console::levels::Debug)) {
        ros::console::notifyLoggerLevelsChanged();
    }
    **/

    int loop_rate = 30;
    int s_id = 0x10;
    int period = 20;//パルス周期（ms）
    int range = 180;//最大回転角（deg）
    int min_p_width = 550;//0度の時のパルス幅
    int max_p_width = 2400;//最大の時のパルス幅
    int lost_time_threshold = 500;
    bool gazebo_mode = false;

    pnh.getParam("control_frequency", loop_rate);
    pnh.getParam("servo_id",s_id);
    pnh.getParam("period",period);
    pnh.getParam("range",range);
    pnh.getParam("min_pulse_width",min_p_width);
    pnh.getParam("max_pulse_width",max_p_width);
    pnh.getParam("lost_time_threshold", lost_time_threshold);
    pnh.getParam("gazebo_mode", gazebo_mode);

    return 0;
}
