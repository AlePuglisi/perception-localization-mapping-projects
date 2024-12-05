#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "ros/ros.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "actionlib/client/simple_action_client.h"
#include "iostream"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; 

class waypoints {

    private:
        string fname;
	    vector<string> row;
	    string line, word;
        vector<float> data;
        
    public: 
        string heading;
        vector<vector<float>> goal;
        
        waypoints(){
            if(!ros::param::get("/path_to_csv", fname)){
                ROS_WARN("Could not get path to file\n");
                fname = "";
            }
                

            fstream file (fname, ios::in);

        	if(file.is_open())
	        {
                getline(file, heading); // if the first line is of heading it ignores it (comment this line if there is no heading)

	        	while(getline(file, line)) // passes through each line of the document
	        	{
	        		row.clear();
                    data.clear();
        
	        		stringstream str(line);
        
	        		while(getline(str, word, ',')) // devides each line in columns using ',' as dividing term
	        			row.push_back(word);

                    data.push_back(std::stof(row[0])); // x
                    data.push_back(std::stof(row[1])); // y
                    data.push_back(std::stof(row[2])); // heading

                    goal.push_back(data); 

	        	}
	        }
	        else
	        	ROS_WARN("Could not open the file\n");
        
        }

};
 
int main(int argc, char** argv)
{
    ros::init(argc, argv, "navigation_commander");
    ros::NodeHandle n;

    waypoints path; // creates path structure with path.goal[i] an array with the different goals from the file 

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    int i = 0;
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";

    while(ros::ok()){
        // Prepare goal target
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = path.goal[i][0];
        goal.target_pose.pose.position.y = path.goal[i][1];
        goal.target_pose.pose.orientation.w = path.goal[i][2];
        
        // Send goal
        ROS_INFO("Sending goal: %d", i+1);
        ac.sendGoal(goal);

        // Wait for goal to be reached
        ac.waitForResult();
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("The robot has arrived at the goal location");
        else
            ROS_INFO("The robot failed to reach the goal location for some reason");

        i++; // move to next goal
    }
 
	return 0;
}