#include "Localisation.h"

#include <bits/exception.h>
#include <omnetpp/ccanvas.h>
#include <omnetpp/ccomponent.h>
#include <omnetpp/checkandcast.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cmodule.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/csimplemodule.h>
#include <omnetpp/csimulation.h>
#include <omnetpp/regmacros.h>
#include <omnetpp/simtime.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

#include "../../common/InitStages.h"
#include "../../common/IntrusivePtr.h"
#include "../../common/IProtocolRegistrationListener.h"
#include "../../common/lifecycle/OperationalMixin.h"
#include "../../common/lifecycle/OperationalMixinImpl.h"
#include "../../common/ModuleAccess.h"
#include "../../common/packet/chunk/FieldsChunk.h"
#include "../../common/packet/Message.h"
#include "../../common/packet/Packet.h"
#include "../../common/Protocol.h"
#include "../../common/ProtocolTag_m.h"
#include "../../common/Ptr.h"
#include "../../common/Simsignals.h"
#include "../../common/Units.h"
#include "../../linklayer/common/InterfaceTag_m.h"
#include "../../mobility/contract/IMobility.h"
#include "../../networklayer/common/L3AddressResolver.h"
#include "../../networklayer/common/L3AddressTag_m.h"
#include "../../networklayer/common/NetworkInterface.h"
#include "../../networklayer/contract/ipv4/Ipv4Address.h"
#include "../../networklayer/contract/IInterfaceTable.h"
#include "../../networklayer/ipv4/Ipv4InterfaceData.h"
#include "../../physicallayer/wireless/common/contract/packetlevel/SignalTag_m.h"
#include "LocalisationHello_m.h"

namespace inet {
Define_Module(Localisation);
Localisation::Localisation() {
}
Localisation::~Localisation() {
    cancelAndDelete(selfMsg);
}

void Localisation::initialize(int stage) {
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"),
                this);
        event = new cMessage("event");
        type=getParentModule()->par("type").stdstringValue();
        helloInterval = par("helloInterval");
        broadcastDelay = &par("broadcastDelay");
        if(nodeIs("station")){lastAddress=nullptr;}


    } else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {
        registerProtocol(Protocol::manet, gate("socketOut"), gate("socketIn"));
    }
}

void Localisation::handleSelfMessage(cMessage *msg) {
    if (msg == event && nodeIs("target")) {
            findMe();
    }


}

bool comparePosData(const PosData& a, const PosData& b) {
    if (a.rank != b.rank) {
        return a.rank < b.rank;
    } else {
        return a.rssi > b.rssi;
    }
}

void Localisation::handleMessageWhenUp(cMessage *msg) {

    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
    } else if (nodeIs("target") || (nodeIs("target")&& rank>0)) {
        getParentModule()->bubble("recieved posInfo");
        try{

        auto recHello =  staticPtrCast<CalculatedPos>(check_and_cast<Packet*>(msg)->peekData<CalculatedPos>()->dupShared());
        pos=Coord(recHello->getX(),recHello->getY());
        rank = recHello->getRank();
        type="anchor";} catch (const std::exception &e) {
        }
    } else if (nodeIs("anchor")) {
        getParentModule()->bubble("recieved Broadcast");
        auto recHello =  staticPtrCast<WhereIam>(check_and_cast<Packet*>(msg)->peekData<WhereIam>()->dupShared());

        L3Address srcAddress = recHello->getSrcAddress();


            sendAnchorDataToStation(getAdressOf("station"),srcAddress, msg);



    } else if (nodeIs("station")) {
            try {

                auto recHello =  staticPtrCast<AnchorData>(check_and_cast<Packet*>(msg)->peekData<AnchorData>()->dupShared());
                int rank = recHello->getRank();
                L3Address targetAddress =recHello->getTargetAddress();

                double x = recHello->getX();
                double y = recHello->getY();
                double rssi = recHello->getRssi();
                double rssiRef = getParentModule()->getParentModule()->par(
                        "rssiRef");
                double n = getParentModule()->getParentModule()->par("n");
                PosData newPosData = {rank, rssi, x, y};
                dictOfAnchorData[targetAddress].emplace_back(newPosData);
                dictOfAnchorData[targetAddress].sort(comparePosData);
                if(dictOfAnchorData[targetAddress].size()>2){
                    int maxRank = -1;
                    auto it = dictOfAnchorData[targetAddress].begin();
                    for (int i = 0; i < 3 ; i++, it++) {
                        const auto& posData = *it;
                        bestData[std::make_tuple(posData.x, posData.y)]=calculateDistance(
                                posData.rssi, rssiRef, n);
                        maxRank = std::max(maxRank, posData.rank);
                    }
                    Coord position=calculatePosition(bestData);
                    std::cout << targetAddress <<" pos  :   " << position.x <<","<< position.y << " rank : "<< rank<< endl;
                    sendPostion(targetAddress, maxRank+1,position.x,position.y);
                    bestData.clear();
                }
//*lastAddress=targetAddress;



            } catch (const std::exception &e) {
            }
    }

}
L3Address Localisation::getAdressOf(const char *nodeName) {
    L3Address nodeAddress = L3AddressResolver().resolve(nodeName);
    return nodeAddress;

}
Coord Localisation::getMyPosition() {
    cModule *node = getContainingNode(this);
    IMobility *mod = check_and_cast<IMobility*>(node->getSubmodule("mobility"));
    pos = mod->getCurrentPosition();
    return pos;
}
bool Localisation::nodeIs(std::string Type) {
    return type == Type;
}
double Localisation::calculateDistance(double rssi, double rssiRef, double n) {
    return pow(10, (rssiRef - rssi) / (10 * n));
}
struct Localisation::Point {
    double x;
    double y;
};
int Localisation::findCircleCircleIntersection(Point p1, double r1, Point p2, double r2, Point &i1, Point &i2) {
    double d = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

    if (d > r1 + r2) { // no intersection
        return 0;
    }

    if (d < abs(r1 - r2)) { // one circle is inside the other
        return 0;
    }

        double a = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d);
        double h = sqrt(pow(r1, 2) - pow(a, 2));
        double x2 = p1.x + a * (p2.x - p1.x) / d;
        double y2 = p1.y + a * (p2.y - p1.y) / d;
        double rx = -(p2.y - p1.y) * (h / d);
        double ry = -(p2.x - p1.x) * (h / d);

        i1.x = x2 + rx;
        i1.y = y2 - ry;

        i2.x = x2 - rx;
        i2.y = y2 + ry;

    if (d == r1 + r2 || d == abs(r1 - r2)) { // tangent circles
        return 1;
    } else {
        return 2;
    }
}
Coord Localisation::calculatePosition(std::map<std::tuple<double, double>, double> dictOfAnchorData) {

    std::vector<Localisation::Point> inter ;
    auto it = dictOfAnchorData.begin();
    double x3 = std::get<0>(it->first);
    double y3 = std::get<1>(it->first);
    double r3 = it->second;
    ++it;
    double x1 = std::get<0>(it->first);
    double y1 = std::get<1>(it->first);
    double r1 = it->second;
    ++it;
    double x2 = std::get<0>(it->first);
    double y2 = std::get<1>(it->first);
    double r2 = it->second;




     Point p1 = {x1, y1};
     Point p2 = {x2, y2};
     Point p3 = {x3, y3};

     Point i1, i2;
     int numIntersections1 = findCircleCircleIntersection(p1, r1, p2, r2, i1, i2);
     Point i3, i4;
     int numIntersections2 = findCircleCircleIntersection(p1, r1, p3, r3, i3, i4);
     Point i5, i6;
     int numIntersections3 = findCircleCircleIntersection(p2, r2, p3, r3, i5, i6);

     if(numIntersections1==2)
     {
         double e1  =abs(  r3-( sqrt(pow(x3 - i1.x, 2) + pow(y3 - i1.y, 2)))  );
         double e2  =abs(  r3-( sqrt(pow(x3 - i2.x, 2) + pow(y3 - i2.y, 2)))  );
         if(e2>e1)
             inter.push_back(i1);
         else
             inter.push_back(i2);
     }
     else if(numIntersections1==1)
        {
                inter.push_back(i1);
        }

     if(numIntersections2==2)
          {
              double e3  =abs(  r2-( sqrt(pow(x2 - i3.x, 2) + pow(y2 - i3.y, 2)))  );
              double e4  =abs(  r2-( sqrt(pow(x2 - i4.x, 2) + pow(y2 - i4.y, 2)))  );
              if(e4>e3)
                  inter.push_back(i3);
              else
                  inter.push_back(i4);
          }
     else if(numIntersections2==1)
             {
                     inter.push_back(i3);
             }

     if(numIntersections3==2)
          {
              double e5  =abs(  r1-( sqrt(pow(x1 - i5.x, 2) + pow(y1 - i5.y, 2)))  );
              double e6  =abs(  r1-( sqrt(pow(x1 - i6.x, 2) + pow(y1 - i6.y, 2)))  );
              if(e6>e5)
                  inter.push_back(i5);
              else
                  inter.push_back(i6);
          }
          else if(numIntersections3==1)
             {
                     inter.push_back(i5);
             }

double xg=0,yg=0;
int i=0;
     for (std::vector<Localisation::Point>::iterator it = inter.begin(); it != inter.end(); it++) {
         xg += it->x;
         yg += it->y;
         i++;

        }
     yg=yg/i;
     xg=xg/i;



     cCanvas *d = getParentModule()->getParentModule()->getCanvas();
    point = new cOvalFigure("point");
    point->setBounds(cFigure::Rectangle(-1, -1, 1, 1));
    point->setFilled(true);
    point->setFillColor(cFigure::RED);
    point->setPosition(cFigure::Point(xg, yg),
            cFigure::ANCHOR_CENTER);
    d->addFigure(point);
    return Coord(xg,yg);

}

double Localisation::calculateRssi(cMessage *msg) {
    auto radioMsg = check_and_cast<Packet*>(msg);
    auto signalPowerInd = radioMsg->getTag<SignalPowerInd>();
    auto rxPower = signalPowerInd->getPower().get();
    double signalPowerdBm = 10 * log10(rxPower / 1e-3);
    return signalPowerdBm;
}
void Localisation::sendPostion(L3Address destAddress,int rank,double x,double y) {
    auto posInfo = makeShared<CalculatedPos>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    posInfo->setChunkLength(b(128));
    posInfo->setSrcAddress(source);
    posInfo->setRank(rank);
    posInfo->setX(x);
    posInfo->setY(y);

    auto packet = new Packet("posInfo", posInfo);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(destAddress);
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    posInfo = nullptr;
    scheduleAt(simTime() + helloInterval, event);
    getParentModule()->bubble("Sending posInfo");

}
void Localisation::sendAnchorDataToStation(L3Address stationAddress,L3Address targetAddress,cMessage *msg) {
    auto data = makeShared<AnchorData>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    data->setChunkLength(b(128));
    data->setRank(rank);
    data->setTargetAddress(targetAddress);
    data->setX(pos.x);
    data->setY(pos.y);
    data->setRssi(calculateRssi(msg));
    std::cout << getFullPath() << "   :   " << calculateRssi(msg) << endl;
    auto packet = new Packet("Data", data);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(stationAddress);
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    data = nullptr;
    cancelEvent(event);
    scheduleAt(simTime() + helloInterval, event);
    getParentModule()->bubble("Sending anchor data");

}
void Localisation::findMe() {
    auto hello = makeShared<WhereIam>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    hello->setChunkLength(b(128));
    hello->setSrcAddress(source);
    auto packet = new Packet("Hello", hello);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(
            Ipv4Address(255, 255, 255, 255));
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    hello = nullptr;
    cancelEvent(event);
    scheduleAt(simTime() + helloInterval + broadcastDelay->doubleValue(),
            event);
    getParentModule()->bubble("Broadcasting hello");
}
void Localisation::start() {
    if ( nodeIs("anchor")) {
                rank = 0;
                pos=getMyPosition();

            }

    for (int i = 0; i < ift->getNumInterfaces(); i++) {
        auto ie = ift->getInterface(i);
        auto name = ie->getInterfaceName();
        if (strstr(name, "wlan") != nullptr) {
            interface80211ptr = ie;
            break;
        }
    }
    Ipv4Address source =
                (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    std::cout << " Myaddresss  :   " << source << endl;
    scheduleAt(simTime() + uniform(0.0, par("maxVariance").doubleValue()),
            event);
}
void Localisation::stop() {
    cancelEvent(event);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}
void Localisation::socketDataArrived(UdpSocket *socket, Packet *packet) {
    emit(packetReceivedSignal, packet);
}
void Localisation::socketErrorArrived(UdpSocket *socket,
        Indication *indication) {
    delete indication;
}
void Localisation::socketClosed(UdpSocket *socket) {
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}
}
