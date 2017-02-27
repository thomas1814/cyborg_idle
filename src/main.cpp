#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <ctime>
#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/String.h>
#include <actionlib/server/simple_action_server.h>
#include <cyborg_controller/StateMachineAction.h>
#include <cyborg_controller/EmotionalFeedback.h>

typedef actionlib::SimpleActionServer<cyborg_controller::StateMachineAction> Server; // Create a ROS server with actions
ros::Publisher publisher;

void server_idle(const cyborg_controller::StateMachineGoalConstPtr& goal, Server* as){
	ROS_INFO_STREAM("Cyborg_idle: Executing idle state...");
	int count = 0;
	bool running = true;
	while (running) {
		// Check that preempt has not been requested by the client
		if (as->isPreemptRequested() || !ros::ok()) {
			as->setPreempted();
			running = false;
		}

		// Sleep for a while
		unsigned long milisec = 2000;
		struct timespec req={0};
		time_t sec=(int)(milisec/1000);
		milisec=milisec-(sec*1000);
		req.tv_sec=sec;
		req.tv_nsec=milisec*1000000L;
		nanosleep(&req,&req);

		// Encrease "bordom" by lowering PAD values...
		if (count >= 4) {
			cyborg_controller::EmotionalFeedback message;
			message.delta_pleasure = -0.05;
			message.delta_arousal = -0.05;
			message.delta_dominance = -0.05;
			publisher.publish(message);
			count = 0;
		}
		count++;
	}
}


int main(int argc, char *argv[]){
	std::cout << "Cyborg_idle: Starting program..." << std::endl;
	ros::init(argc, argv, "cyborg_idle");
	ros::NodeHandle n;
	publisher = n.advertise<cyborg_controller::EmotionalFeedback>("cyborg_controller/emotional_feedback", 100);
	Server server(n, ros::this_node::getName() + "/idle", boost::bind(&server_idle, _1, &server), false);
	server.start();
	ROS_INFO_STREAM("Cyborg_idle: Activated...");
	ros::spin();
	server.shutdown();
	std::cout << "Cyborg_idle: End of program..." << std::endl;
	return 0;
}

