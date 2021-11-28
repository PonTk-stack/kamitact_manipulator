#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

#include <string>
#include <math.h>

#include "kamitact_manipulator/kamitact_manipulator.h"
#include "kamitact_manipulator/common.h"

using namespace kamitact_manipulator;


enum{
    INIT_POSITION,
    FINISH,
};

uint8_t task = 0;

int main(int argc, char** argv)
{

    const char* nodeName = "kamitact_manipulator_node";
    uint8_t task = 0;
    const char* pubName = "/publisher";
    // Init ROS node
    ros::init(argc, argv, StringCat(nodeName," start"));
    ros::NodeHandle priv_nh("~");
    ros::Publisher joint_pub = priv_nh.advertise<sensor_msgs::JointState>(StringCat(nodeName,pubName), 10);
    //priv_nh.getParam("target_object", target_object);

    ros::Rate loop_rate(25);
    task = INIT_POSITION ;

    while(ros::ok()){
        ros::spinOnce();
        //process(); //service request. send head x y z, quatanion
        loop_rate.sleep();
        if( task == FINISH ){
            break;
        }
    }
    ROS_INFO("kamitact_manipulator_node end");
    return 0;

}
