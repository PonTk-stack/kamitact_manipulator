#ifndef KAMITACT_MANIPULATOR_CONTROLLER_H
#define KAMITACT_MANIPULATOR_CONTROLLER_H

namespace kamitact_manipulator_controller{
    class KTManipulatorController{
        private:
            //handler
            ros::NodeHandle node_handle_;
            ros::NodeHandle priv_node_handle_;

            double control_period_;

            //related object
            KTManipulator kt_manipulator_;

            // Thread parameter
            pthread_t timer_thread_;
            pthread_attr_t attr_;
            bool timer_thread_state_;


            /***************************************************************************/
            //publisher and relevant functions
            ros::Publisher kt_manipulator_joint_states_pub_;
            void publishJointStates();

            //subscriber
            //
    };
}
#endif //KAMITACT_MANIPULATOR_CONTROLLER_H
