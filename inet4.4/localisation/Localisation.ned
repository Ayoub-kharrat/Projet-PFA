package inet.routing.localisation;
import inet.applications.contract.IApp;
module Localisation like IApp
{
    parameters:
        @class("Localisation");
        @display("i=block/network2");
        string station=default("192.168.0.1");
        string routingTableModule = default("^.ipv4.routingTable");
        string interfaceTableModule = default("^.interfaceTable");
        string networkProtocolModule = default("^.ipv4.ip");
        string netmask = default("255.255.0.0");  // netmask for the ad-hoc network
        double maxVariance = default(1); // This is the maximum of a random value to determine when the first hello message will be sent out// the expiry time of the routing entries
        double helloInterval @unit(s) = default(3s); 
        volatile double broadcastDelay @unit(s) = default(uniform(0s,0.01s));
    gates:
        input socketIn;
        output socketOut;
}
