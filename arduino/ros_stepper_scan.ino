#include <AFMotor.h>

#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle nh;

// 200 steps per revolution, 1.8 step per degree
AF_Stepper motor(200, 2);

void messageCb(const std_msgs::Float64 &delta_degree)
{
  int deg_to_steps = abs((int) delta_degree.data / 1.8);
  if (delta_degree.data > 0)
  {
    motor.step(deg_to_steps, FORWARD, MICROSTEP);
  }
  else if (delta_degree.data < 0)
  {
    motor.step(deg_to_steps, BACKWARD, MICROSTEP);
  }
  else
  {
    // do nothing
  } 
  motor.release();
}

ros::Subscriber<std_msgs::Float64> sub("scan_increment", &messageCb);

void setup()
{
  motor.setSpeed(10);
  motor.release();
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
}
