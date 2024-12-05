#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "nav_msgs/Odometry.h"
#include "first_project/Odom.h"
#include "first_project/reset_odom.h"
#include "tf/transform_broadcaster.h"
#include "first_project/reset_odom.h"

#include <sstream>

double v;
double alfa;
double x=0; /*initialize odometry, so it works only if runned not from launch*/
double y=0;
double th=0;
double d = 2.8;
bool first_call=true;
double dt;
ros::Time previous, current;


nav_msgs::Odometry msgodom;
first_project::Odom msgcustomodom;

ros::Publisher pubodom;
ros::Publisher pubodomcustom; 

void odomCallback(const  geometry_msgs::Quaternion::ConstPtr& msg){
    v = msg->x;
    alfa = msg->y;

    if (first_call){
        dt=0.1;
        first_call=false;
    }
    else{
        current = ros::Time::now();
        dt=(current-previous).toSec();
        ROS_INFO("%f",dt);
    }
    /*kinematic of bicycle approx. with base frame on the middle of the vehicle, considering front steering and back traction */
    double gamma = atan(tan(alfa)/2); /*angle of middle body velocity*/
    /*Rouge-Kutta integration for a better approximation*/
    double delta_th = (v/d)*tan(alfa)*dt;
    double delta_x = (v/cos(gamma))*cos(th+ delta_th/2)*dt;
    double delta_y = (v/cos(gamma))*sin(th+ delta_th/2)*dt;
   
    x += delta_x;
    y += delta_y;
    th += delta_th;

    /*Fill custom Odom message*/
    msgcustomodom.x=x;
    msgcustomodom.y=y;
    msgcustomodom.th=th;

    ros::Time stamp = ros::Time::now();
    std::stringstream ss;
    ss << stamp.sec << "." << stamp.nsec;
    msgcustomodom.timestamp= ss.str();

    /*Fill Odometry message*/
    msgodom.header.stamp = ros::Time::now();
    msgodom.header.frame_id = "odom";
    msgodom.pose.pose.position.x= x;
    msgodom.pose.pose.position.y= y;
    msgodom.pose.pose.position.z= 0.0;
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
    msgodom.pose.pose.orientation = odom_quat;
    msgodom.child_frame_id = "base_link";
    msgodom.twist.twist.linear.x = (v/cos(gamma))*cos(th);
    msgodom.twist.twist.linear.y = (v/cos(gamma))*sin(th);
    msgodom.twist.twist.angular.z = v*tan(alfa)/d;  

    /*define and broadcast the tf*/
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(x, y, 0));
    tf::Quaternion q;
    q.setRPY(0, 0, th);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));  

    pubodom.publish(msgodom);
    pubodomcustom.publish(msgcustomodom);
    previous = ros::Time::now(); /*update time for integration*/
};

/*SERVICE server function*/
bool reset(first_project::reset_odom::Request &req, first_project::reset_odom::Response &res){
    x=0;
    y=0;
    th=0;
    res.resetted = true;
    return true;
};

int main(int argc, char **argv){
    ros::init(argc, argv, "odom_node");

    ros::NodeHandle n;
    ros::Subscriber subodom;

    ros::ServiceServer service = n.advertiseService("reset_odom", reset);

    
    pubodom = n.advertise<nav_msgs::Odometry>("odometry", 1000);
    pubodomcustom = n.advertise<first_project::Odom>("custom_odometry", 1000);
    subodom= n.subscribe("speed_steer", 1000, odomCallback);

    n.getParam("/starting_x", x);
    n.getParam("/starting_y", y);
    n.getParam("/starting_th", th);

    ros::Rate loop_rate(10);
    ros::spin();
    
    return 0;
}