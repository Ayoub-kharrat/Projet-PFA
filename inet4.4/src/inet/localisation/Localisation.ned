//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.localisation;


import inet.applications.contract.IApp;
import inet.node.inet.AdhocHost;
import inet.node.wireless.AccessPoint;


module Localisation like IApp
{
    parameters:
        @class(Localisation);
        @display("i=block/network2");
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

module MyAccessPoint
{
    parameters:
        @class(MyAccessPoint);
    gates:
        input in @directIn;
        output out @directOut;
}

module ap extends AccessPoint
{
    parameters:
        string type = default("ap");
    submodules:
        p: MyAccessPoint {
            @display("p=898.684,223.542");
        }
    connections:

        p.out --> p.in;
}

module LocalisationNode extends AdhocHost
{
    parameters:
        string type = default("anchor");
    submodules:
        loc: Localisation {
            @display("p=898.684,223.542");
        }
    connections:
        loc.socketOut --> at.in++;
        loc.socketIn <-- at.out++;
}


//module IdealClock extends AdhocHost
//{
   // parameters:

//@class(IdealClock);
       //  @signal[src](type="wirelessSignal");

     //submodules:

       // source: AdhocHost {
        //    @display("p=311,158");
       // }
   // gates:
  ///      input in;
     //  output out;



