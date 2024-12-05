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
        string fname = "../waypoints.csv";
	    vector<string> row;
	    string line, word;
        vector<float> data;
        
    public: 
        string heading;
        vector<vector<float>> goal;
        
        waypoints(){

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


class nav {
    private:
        ros::NodeHandle n;
        MoveBaseClient ac("move_base", true);
        


    public:
        nav(){

            while(!ac.waitForServer(ros::Duration(5.0))){
                ROS_INFO("Waiting for the move_base action server to come up");
            }
        }

        void callback(){

        }


};
 
int main(int argc, char** argv)
{
    ros::init(argc, argv, "navigation_commander");

    waypoints path; // creates path structure with path.goal[i] an array with the different goals from the file 

    nav commander;
 
	return 0;
}