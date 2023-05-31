//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.Localisation;


import inet.applications.contract.IApp;
import inet.node.aodv.AodvRouter;


module Localisation like IApp
{
    parameters:
    
        @class(Localisation);
        @display("i=block/network2");
        string routingTableModule = default("^.ipv4.routingTable");
        string interfaceTableModule = default("^.interfaceTable");
        string networkProtocolModule = default("^.ipv4.ip");
        string netmask = default("255.255.0.0");  // netmask for the ad-hoc network
        string address = default("192.168.0.55");
        double maxVariance = default(1); // This is the maximum of a random value to determine when the first hello message will be sent out// the expiry time of the routing entries
        double helloInterval @unit(s) = default(3s);
        volatile double broadcastDelay @unit(s) = default(uniform(0s,0.01s));
    gates:
        input socketIn;
        output socketOut;
}



module LocalisationNode extends AodvRouter
{
    parameters:
        string type = default("target");
        

    submodules:
        localisation: Localisation {
            @display("p=825,226");
        }
    connections:
        localisation.socketOut --> at.in++;
        localisation.socketIn <-- at.out++;
}

