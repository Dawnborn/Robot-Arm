# Probot_demo
---
Control the robot arm to iterately reach the vertices of a 20*20 cm cube.
## Environment
Ubuntu 18.04 LTS
ROS Melodic
ros-melodic-moveit
## Install and Running
under `catkin_ws`, run
```
catkin_make
```
then in a new terminal under `catkin_ws`
```
source devel/setup.bash
roslaunch probot_anno_moveit_config demo.launch 
```
in a third terminal
```
source devel/setup.bash
rosrun probot_demo moveit_ik_demo 
```
## Robotic Model
Generatded by `moveit_setup_assistant` and loading `probot_description/urdf/probot_anno.urdf`.