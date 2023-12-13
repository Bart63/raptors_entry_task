
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


class RaptorNode
{
public:
    RaptorNode()
    {
        ros::NodeHandle n;
        sub = n.subscribe("RaptorIN", 100, &RaptorNode::messageCallback, this);
        pub = n.advertise<std_msgs::String>("RaptorOUT", 100);
    }

    void messageCallback(const std_msgs::String::ConstPtr& msg)
    {
        std::string originalMessage = msg->data;
        std::string signature = getSignature();
        std::string modifiedMessage = originalMessage + signature;

        std_msgs::String modifiedMsg;
        modifiedMsg.data = modifiedMessage;
        pub.publish(modifiedMsg);
    }

    std::string getSignature()
    {
        std::time_t ts = std::time(0);
        std::stringstream ss;
        ss << "<BartoszDurys/" << ts << ">";
        return ss.str();
    }

private:
    ros::Subscriber sub;
    ros::Publisher pub;
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "raptor_node");

    RaptorNode raptorNode;

    ros::spin();

    return 0;
}