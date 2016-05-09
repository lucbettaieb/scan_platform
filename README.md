# scan_platform
ros related code to control a platform for 3D scanning of objects

run:
 - roscore
 - sudo chmod a+rw /dev/ttyACM0 or USB0 whichever shows
 - rosrun rosserial_python serial_node.py /dev/ttyACM0 (or USB0)
 - rostopic pub --once /scan_increment std_msgs/Float64 "data: 180.0"