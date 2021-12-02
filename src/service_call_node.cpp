#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "open_manipulator_msgs/setxyz.h" //kudos
#include <cstdlib>

//float input_x1,input_y1,input_z1;


using namespace std;

//bool setxyz_(open_manipulator_msgs::setxyz::Request &req,
//            open_manipulator_msgs::setxyz::Response &res)

 float service_result_x = 0;
 float service_result_y = 0;
 float service_result_z = 0;


geometry_msgs::Vector3 center_msg;
open_manipulator_msgs::setxyz srv;

void chatterCallback(const geometry_msgs::Vector3::ConstPtr& center_msg)
{
  srv.request.srv_input_x = center_msg->x;
  srv.request.srv_input_y = center_msg->y;
  srv.request.srv_input_z = center_msg->z;


  cout << srv.request.srv_input_x << endl;
  cout << srv.request.srv_input_y << endl;
  cout << srv.request.srv_input_z << endl;

}

int main(int argc, char **argv)
{


  ros::init(argc, argv, "service_call_node");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/darknet_ros_3d/centers", 100, chatterCallback);
  ros::Rate loop_rate(30);
  while (ros::ok())
   {
 // srv.request.srv_input_x;
 // srv.request.srv_input_y;
 // srv.request.srv_input_z;
  ros::ServiceClient client_node = nh.serviceClient<open_manipulator_msgs::setxyz>("client_node");

if (client_node.call(srv) ) {
 //ROS_INFO("receive srv: %d", (float)srv.response.result);
 service_result_x = srv.response.srv_output_x;
 service_result_y = srv.response.srv_output_y;
 service_result_z = srv.response.srv_output_z;


}

else {
  ROS_ERROR("Failed to call service ros_tutorial_srv");
}

ros::spinOnce();

loop_rate.sleep();
}
  ros::spin();
  return 0;
}
