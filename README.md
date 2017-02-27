# README  
This repository contains the source code for the idle state ROS node in the NTNU Cyborg.  

Node name: cyborg_idle  
Language: C++  
Numbers of actionlib server(s): 1  

## Requirements:
* ROS

## Features:
*The idle state: The Cyborg`s idle state decreases the PAD values. Available at actionlib server topic cyborg_idle/idle.

## Usage:
$ rosrun cyborg_idle idle
