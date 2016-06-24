# scan_platform
ros related code to control a platform for 3D scanning of objects

# Run Test:
 - roscore
 - sudo chmod a+rw /dev/ttyACM0 or USB0 whichever shows
 - rosrun rosserial_python serial_node.py /dev/ttyACM0 (or USB0)
 - rostopic pub --once /scan_increment std_msgs/Float64 "data: 180.0"


 # To Take Scan:
 - roscore
 - sudo chmod a+rw /dev/ttyACM0 or USB0 whichever shows
 - rosrun rosserial_python serial_node.py /dev/ttyACM0 (or USB0)
 - rosservice call /start_stepper_scan "model_name: 'put_name_of_object_here'"
