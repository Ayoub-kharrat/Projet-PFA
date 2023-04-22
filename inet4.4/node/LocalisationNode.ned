

package inet.examples.localisation;
import inet.common.scenario.ScenarioManager;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.aodv.AodvRouter;
import inet.node.inet.WirelessHost;
import inet.node.localisation.LocalisationNode;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;


network LocalisationExample
{
    parameters:

        @display("bgb=800,800;bgg=1,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        double n = default(2.0134);
        double rssiRef = default(-53.0026);

    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            @display("p=553.152,20.904;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=553.152,54.672;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=554.76,90.048004;is=s");
        }
        scenarioManager: ScenarioManager {
            @display("p=554.76,127.032;is=s");
        }
        station: LocalisationNode {
            parameters:
                type = "station";
                localisation.netmask = "255.255.0.0";
                @display("i=device/pc;r=,,#707070;p=114.168,90.048004");
        }

        target: LocalisationNode {
            parameters:

                localisation.netmask = "255.255.0.0";
                @display("i=device/pocketpc_s;o=0;r=,,#707070;p=115,115");


        }
        Anchor1: LocalisationNode {
            parameters:
                type = "anchor";
                localisation.netmask = "255.255.0.0";
                @display("i=device/receiverdish;r=,,#707070;p=100,100");
        }
        Anchor2: LocalisationNode {
            parameters:
                type = "anchor";
                localisation.netmask = "255.255.0.0";
                @display("i=device/receiverdish;r=,,#707070;p=130,100");
        }
        Anchor3: LocalisationNode {
            parameters:
                type = "anchor";
                localisation.netmask = "255.255.0.0";
                @display("i=device/receiverdish;r=,,#707070;p=115,130");
        }



    connections allowunconnected:

}
