#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "tf/transform_datatypes.h"
#include "nav_msgs/Odometry.h"

class turtle_tf {
    private:
        ros::NodeHandle n;
        tf::TransformBroadcaster br;
        tf::Transform transform; 
        ros::Subscriber sub;
        tf::Quaternion q;

    public:
        turtle_tf(){
            sub = n.subscribe("/t265/odom", 100, &turtle_tf::callback, this);
        }

        void callback(const nav_msgs::Odometry::ConstPtr& msg){

            float x = msg->pose.pose.position.x;
            float y = msg->pose.pose.position.y;
            float z = msg->pose.pose.position.z;
            ros::Time timestamp = msg->header.stamp;

            transform.setOrigin(tf::Vector3(x, y, z));

            tf::quaternionMsgToTF(msg->pose.pose.orientation, q);

            transform.setRotation(q);

            br.sendTransform(tf::StampedTransform( transform, timestamp, "odom", "t265"));
        }


};

int main(int argc, char **argv){
    ros::init(argc, argv, "tf_publisher");
    
    turtle_tf my_turtle_TF;
    ros::spin();
    return 0;
}