
#include "kamitact_manipulator/kamitact_manipulator.h"
KTManipulatorController::KTManipulatorController()
    : node_handle_(""),
    priv_node_handle_("~"),
    timer_thread_state_(false){

        control_period_ = priv_node_handle_.param<double>("control_period", 0.010f);

        //open_manipulator_.initOpenManipulator(using_platform_, usb_port, baud_rate, control_period_);

        initPublisher();
        initSubscriber();
        initServer();
    }

void KTManipulatorController::startTimerThread()
{
  ////////////////////////////////////////////////////////////////////
  /// Use this when you want to increase the priority of threads.
  ////////////////////////////////////////////////////////////////////
  //  pthread_attr_t attr_;
  //  int error;
  //  struct sched_param param;
  //  pthread_attr_init(&attr_);

  //  error = pthread_attr_setschedpolicy(&attr_, SCHED_RR);
  //  if (error != 0)   log::error("pthread_attr_setschedpolicy error = ", (double)error);
  //  error = pthread_attr_setinheritsched(&attr_, PTHREAD_EXPLICIT_SCHED);
  //  if (error != 0)   log::error("pthread_attr_setinheritsched error = ", (double)error);

  //  memset(&param, 0, sizeof(param));
  //  param.sched_priority = 31;    // RT
  //  error = pthread_attr_setschedparam(&attr_, &param);
  //  if (error != 0)   log::error("pthread_attr_setschedparam error = ", (double)error);

  //  if ((error = pthread_create(&this->timer_thread_, &attr_, this->timerThread, this)) != 0)
  //  {
  //    log::error("Creating timer thread failed!!", (double)error);
  //    exit(-1);
  //  }
  // timer_thread_state_ = true;
  ////////////////////////////////////////////////////////////////////

  int error;
  if ((error = pthread_create(&this->timer_thread_, NULL, this->timerThread, this)) != 0)
  {
    log::error("Creating timer thread failed!!", (double)error);
    exit(-1);
  }
  timer_thread_state_ = true;
}

void *KTManipulatorController::timerThread(void *param)
{
  KTManipulatorController *controller = (OpenManipulatorController *) param;
  static struct timespec next_time;
  static struct timespec curr_time;

  clock_gettime(CLOCK_MONOTONIC, &next_time);

  while(controller->timer_thread_state_)
  {
    next_time.tv_sec += (next_time.tv_nsec + ((int)(controller->getControlPeriod() * 1000)) * 1000000) / 1000000000;
    next_time.tv_nsec = (next_time.tv_nsec + ((int)(controller->getControlPeriod() * 1000)) * 1000000) % 1000000000;

    double time = next_time.tv_sec + (next_time.tv_nsec*0.000000001);
    controller->process(time);

    clock_gettime(CLOCK_MONOTONIC, &curr_time);
    /////
    double delta_nsec = controller->getControlPeriod() - ((next_time.tv_sec - curr_time.tv_sec) + ((double)(next_time.tv_nsec - curr_time.tv_nsec)*0.000000001));
    //log::info("control time : ", controller->getControlPeriod() - delta_nsec);
    if (delta_nsec > controller->getControlPeriod())
    {
      //log::warn("Over the control time : ", delta_nsec);
      next_time = curr_time;
    }
    else
      clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_time, NULL);
    /////
  }
  return 0;
}



void KTManipulatorController::publishJointStates(){
    sensor_msgs::JointState js_msg;
    js_msg.header.stamp = ros::Time::now();

    js_msg.name.resize(10);
    js_msg.name = {"Rev2","Rev4","Rev6","Rev8","Rev10","Rev11","Rev12",
        "Rev13","Rev14","Rev15"};

    js_msg.position.resize(10);
    js_msg.position[0] = -1.0 * (float)count / 40.0;
    js_msg.position[1] = 2.0 * (float)count / 40.0;

    kt_manipulator_joint_states_pub_.publish(js_msg);
}

int main(int argc, char **argv)
{
    // init
    ros::init(argc, argv, "kamitact_manipulator_controller");
    ros::NodeHandle node_handle("");

    KTManipulatorController ktm_controller();

    // update
    om_controller.startTimerThread();
    ros::Timer publish_timer = node_handle.createTimer(ros::Duration(om_controller.getControlPeriod()), &OpenManipulatorController::publishCallback, &om_controller);
    ros::Rate loop_rate(100);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

