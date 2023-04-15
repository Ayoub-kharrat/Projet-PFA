

package inet.examples.localisation;

import inet.localisation.LocalisationNode;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;


network LocalisationExample
{
    parameters:
        @display("bgb=1023.672,610.266;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);
        double n = default(2.0134);//1.75);
        double rssiRef = default(-27.085);

    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            @display("p=809.44196,68.322;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=541.8325,41.9375;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='*' address='145.236.x.x' netmask='255.255.0.0'/></config>");
                @display("p=724.68,41.9375;is=s");
        }
        station: LocalisationNode {
            parameters:
                type = "station";
                loc.netmask = "255.255.0.0";
                @display("i=device/pc;r=,,#707070;p=273.288,151.698");
        }

        target: LocalisationNode {
            parameters:
                type = "target";
                loc.netmask = "255.255.0.0";
                @display("i=device/pocketpc_s;o=0;r=,,#707070;p=517.626,346.242");


        }
        Anchor1: LocalisationNode {
            parameters:

                loc.netmask = "255.255.0.0";
                @display("i=device/receiverdish;r=,,#707070;p=400.612,397.194");
        }
        Anchor2: LocalisationNode {
            parameters:
                loc.netmask = "255.255.0.0";
                @display("i=device/receiverdish;r=,,#707070;p=640.854,418.038");
        }
        Anchor3: LocalisationNode {
            parameters:
                loc.netmask = "255.255.0.0";
                @display("i=device/receiverdish;r=,,#707070;p=540.786,230.442");
        }



    connections allowunconnected:

}
