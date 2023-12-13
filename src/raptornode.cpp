
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "constants.h"

#include <sstream>
#include <nlohmann/json.hpp>


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
        // Assume try-catch is not needed
        nlohmann::json jsonMsg = nlohmann::json::parse(msg->data);
    
        // ... and no checking if a key exists
        std::string originalMessage = jsonMsg["message"];
    
        std::string signature = getSignature(originalMessage);
    
        std::string firstName = RaptorConstants::FIRSTNAME;
        std::string lastName = RaptorConstants::LASTNAME;

        nlohmann::json newJsonMsg;
        newJsonMsg[firstName + lastName] = signature;
        std::string strMsg = newJsonMsg.dump();

        std_msgs::String modifiedMsg;
        modifiedMsg.data = strMsg;
        pub.publish(modifiedMsg);
    }

    std::string getSignature(std::string originalMessage)
    {
        std::time_t ts = std::time(0);
        std::stringstream ss;
        ss << "<" << originalMessage << " / " << ts << ">";
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