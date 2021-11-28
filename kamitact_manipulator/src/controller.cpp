#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

#include <string>
#include <math.h>

auto StringCat(const char *s1, const char *s2){
    size_t len = strlen(s1) + strlen(s2);
    char *str = (char *)malloc(len + 1);
    unsigned int i;

    str[i=0] = *s1;
    while ( (str[++i]=*++s1) != '\0'){};
    str[i] = *s2;
    while ( (str[++i]=*++s2) != '\0'){};
    return str;
}



int main(int argc, char** argv)
{
    const char* nodeName = "manipulator_description_controller_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle nh;
    const char* pubName = "/publisher";
    ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>(StringCat(nodeName,pubName), 10);

    ros::Rate loop_rate(10);
    int count = 0;

    sensor_msgs::JointState js0;

    js0.name.resize(10);
    js0.name = {"Rev2","Rev4","Rev6","Rev8","Rev10","Rev11","Rev12",
        "Rev13","Rev14","Rev15"};
    while (ros::ok())
    {
        //std::cout << nodeName << std::endl;
        js0.header.stamp = ros::Time::now();
        js0.position.resize(10);
        js0.position[0] = -1.0 * (float)count / 40.0;
        js0.position[1] = 2.0 * (float)count / 40.0;
        joint_pub.publish(js0);
        count++;

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
