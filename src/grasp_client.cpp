#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <rail_manipulation_msgs/PickupAction.h>
#include <rail_manipulation_msgs/SegmentedObjectList.h>

void objects_callback(const rail_manipulation_msgs::SegmentedObjectList &objects);

int main (int argc, char **argv)
{
  ros::init(argc, argv, "grasp");
  
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/object_recognition_listener/recognized_objects", 100, objects_callback);


  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<rail_manipulation_msgs::PickupAction> pickupClient("tablebot_moveit/common_actions/pickup", true);


  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  pickupClient.waitForServer(); //will wait for infinite time


  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  rail_manipulation_msgs::PickupGoal pickupGoal;
  pickupGoal.lift = true;
  pickupGoal.verify = false;

  //pickupGoal.pose = action.manipulation_pose;
  pickupClient.sendGoal(pickupGoal);


  //wait for the action to return
  while (!pickupClient.getState().isDone())
  {
  }

  if (pickupClient.getState() != actionlib::SimpleClientGoalState::SUCCEEDED || !pickupClient.getResult()->success)
  {
   ROS_INFO("Pickup failed.");
 }
 else
 {
   ROS_INFO("Pickup succeeded!");
 }

  //exit
 return 0;
}

void objects_callback(const rail_manipulation_msgs::SegmentedObjectList &objects)
{
  
}
