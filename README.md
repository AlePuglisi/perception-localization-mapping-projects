# perception-localization-mapping-projects

ROS Noetic | mobile robot | odometry | slam_toolbox | C++

This repository contains the assignment description and my team's solutions for the two projects of the course in <br/>
[Perception Localization and Mapping](https://www11.ceda.polimi.it/schedaincarico/schedaincarico/controller/scheda_pubblica/SchedaPublic.do?&evn_default=evento&c_classe=837910&__pj0=0&__pj1=22e9c7f323b7d3a5839ccc4b7486a513).
<br/> <br/>
The pdf [ROS_basics](https://github.com/AlePuglisi/perception-localization-mapping-projects/blob/main/ROS_basic.pdf) contains my post-lecture notes on the laboratory sessions.

## first_project (odometry)

> [!IMPORTANT]
> Even if in the pdf assignment there is a Google Drive link to the project data,
> <br/>unfortunately that Drive is updated to the most recent academic year assignment (not to the one described in this Repo, 2023).<br/>
> I will upload the bag file used for this project if I find it!
<br/>
<img width=400 height=250 src="https://github.com/user-attachments/assets/06a8f912-daf4-48cb-baec-d58b6a6a3042">   <img width=350 height=250 src="https://github.com/user-attachments/assets/f02ca1b0-1b82-4ff7-bef7-37536381eb14">
<br/>
We were asked to compute robot odometry given a ROS Bag file, containing the recording of a navigation session for an autonomous shuttle at Politecnico di Milano. 
The Bag file contains information about the wheel encoder and a 2D LIDAR point cloud for visualization (in RViz).

The main functions of **odom_node** are:
- Listen to the encoder information, when information arrives it updates odometry using the bicycle kinematic model for the vehicle.
- when encoder data arrives, using a TF broadcaster, the new estimated position is published
- A standard odometry message and a custom message are published (also as encoder callback).

**first_project** package provide also: 
- A Service **reset_odom**, to reset odometry data (x, y, theta).
- A launch file that runs odom_node, initialize sim_time and odometric variables.
  Run four static TF publishers for the vehicle wheels' position with respect to base_link. 

### Run the code:
After installing **first_project** package (catkin_make on the workspace), as with any other ROS package (remember to source): 

The bag file has to be played in a separate terminal to test the code. 
Otherwise, this can be tested by publishing "fake" encoder data in the proper topic "speed_steer", with data of the expected type. 

```bash
# Terminal 1:
rosbag play <robot.bag>

#Or the alternative way to publish encoder data if bag not available
```

```bash
# Terminal 2:
roslaunch first_project odom_launch.launch 
```

To visualize TF and LIDAR signals, RViz has to be run in another Terminal:
```bash
# Terminal 3:
rosrun rviz rviz
```

Then, in RViz add by topic all the useful information to look at (then it is possible to save a custom RViz config to run automatically). 
<br/>We were not very skilled with ROS, the best practice is to start RViz in the launch itself and define a .rviz configuration file. 


For further details on the task, refer to [first_project assignment](https://github.com/AlePuglisi/perception-localization-mapping-projects/blob/main/first_project.pdf) <br/>
(being the first project with ROS, the structure of the node is not optimal)

## second_project (mapping, slam, and waypoint navigation)

... COMING SOON, README WIP ...

For further details on the task, refer to [second_project assignment](https://github.com/AlePuglisi/perception-localization-mapping-projects/blob/main/second_project.pdf) <br/>


