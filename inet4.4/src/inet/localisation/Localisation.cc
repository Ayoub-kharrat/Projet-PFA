#include "Localisation.h"

#include <bits/exception.h>
#include <omnetpp/ccanvas.h>
#include <omnetpp/checkandcast.h>
#include <omnetpp/cmessage.h>
#include <omnetpp/cmodule.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cpar.h>
#include <omnetpp/csimplemodule.h>
#include <omnetpp/csimulation.h>
#include <omnetpp/regmacros.h>
#include <omnetpp/simtime.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

#include "../common/InitStages.h"
#include "../common/IntrusivePtr.h"
#include "../common/IProtocolRegistrationListener.h"
#include "../common/lifecycle/OperationalMixin.h"
#include "../common/lifecycle/OperationalMixinImpl.h"
#include "../common/ModuleAccess.h"
#include "../common/packet/chunk/Chunk.h"
#include "../common/packet/chunk/FieldsChunk.h"
#include "../common/packet/Message.h"
#include "../common/packet/Packet.h"
#include "../common/Protocol.h"
#include "../common/ProtocolTag_m.h"
#include "../common/Ptr.h"
#include "../common/Simsignals.h"
#include "../common/Units.h"
#include "../linklayer/common/InterfaceTag_m.h"
#include "../mobility/contract/IMobility.h"
#include "../networklayer/common/L3AddressResolver.h"
#include "../networklayer/common/L3AddressTag_m.h"
#include "../networklayer/common/NetworkInterface.h"
#include "../networklayer/contract/ipv4/Ipv4Address.h"
#include "../networklayer/contract/IInterfaceTable.h"
#include "../networklayer/ipv4/Ipv4InterfaceData.h"
#include "../physicallayer/wireless/common/contract/packetlevel/SignalTag_m.h"
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
        NewTarget = new cMessage("NewTarget");
        NewAnchor = new cMessage("NewAnchor");

        type = getParentModule()->par("type").stdstringValue();
        helloInterval = par("helloInterval");
        broadcastDelay = &par("broadcastDelay");

    } else if (stage == INITSTAGE_ROUTING_PROTOCOLS) {
        registerProtocol(Protocol::manet, gate("socketOut"), gate("socketIn"));
    }
}

void Localisation::handleSelfMessage(cMessage *msg) {

    if (msg == event && nodeIs("target")) {

        findMe();

    }

    if (msg == NewAnchor) {
        updateAnchor();
        cancelEvent(NewAnchor);

    }
    if (msg == NewTarget) {
        updateTarget();
        cancelEvent(NewTarget);

    }

}

bool comparePosData(const PosData &a, const PosData &b)
{
    if (a.rank != b.rank) {
        return a.rank < b.rank;
    } else {
        return a.rssi > b.rssi;
    }
}

void Localisation::handleMessageWhenUp(cMessage *msg) {

    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
    } else {
        if (nodeIs("target") || (nodeIs("anchor") && rank > 0)) {

            try {
                //std::cout << " target  :   " << endl;
                auto recHello =
                        staticPtrCast<CalculatedPos>(
                                check_and_cast<Packet*>(msg)->peekData<
                                        CalculatedPos>()->dupShared());
                getParentModule()->bubble("recieved posInfo");
                pos = Coord(recHello->getX(), recHello->getY());
                rank = recHello->getRank();
                type = "anchor";
            } catch (const std::exception &e) {
            }
        }
        if (nodeIs("anchor")) {
            try {
                auto recHello =
                        staticPtrCast<WhereIam>(
                                check_and_cast<Packet*>(msg)->peekData<WhereIam>()->dupShared());
                getParentModule()->bubble("recieved Broadcast");

                L3Address srcAddress = recHello->getSrcAddress();
                std::cout << " pos  :   " << srcAddress << endl;

                sendAnchorDataToStation(getAdressOf("station"), srcAddress,
                        msg);
            }

            catch (const std::exception &e) {
            }

        }
        if (nodeIs("station")) {
            try {

                auto recHello =
                        staticPtrCast<helloTarget>(
                                check_and_cast<Packet*>(msg)->peekData<
                                        helloTarget>()->dupShared());
                getParentModule()->bubble("recieved hello from new target");

                L3Address targetAddress = recHello->getSrcAddress();
                updateStation(targetAddress);
            } catch (const std::exception &e) {
            }
            try {

                auto recHello =
                        staticPtrCast<AnchorData>(
                                check_and_cast<Packet*>(msg)->peekData<
                                        AnchorData>()->dupShared());
                getParentModule()->bubble("recieved Data");

                int rank = recHello->getRank();
                L3Address targetAddress = recHello->getTargetAddress();

                double x = recHello->getX();
                double y = recHello->getY();
                double rssi = recHello->getRssi();

                std::cout << " station  :   x:" << x << " y: " << y << " rssi: "
                        << rssi << " rank: " << rank << " "
                        << " targetAddress: " << targetAddress << endl;
                PosData newPosData = { rank, rssi, x, y };
                dictOfAnchorData[targetAddress].emplace_back(newPosData);
                dictOfAnchorData[targetAddress].sort(comparePosData);

                if (dictOfAnchorData[targetAddress].size() >= 3) {

                    //triMinZone(targetAddress);
                    triMinDist(targetAddress);

                }

            } catch (const std::exception &e) {
            }
        }
    }

}

void Localisation::triMinZone(L3Address targetAddress) {
    double rssiRef = getParentModule()->getParentModule()->par("rssiRef");
    double n = getParentModule()->getParentModule()->par("n");
    int maxRank = -1;
    int lastrank = 0;
    auto it = dictOfAnchorData[targetAddress].begin();

    int i = 0;

    while (1) {
        const auto &posData = *it;
        if (i >= 3 && lastrank < posData.rank) {
            break;
        }
        bestData[std::make_tuple(posData.x, posData.y)] = std::make_tuple(calculateDistance(posData.rssi, rssiRef, n), posData.rank);
        maxRank = std::max(maxRank, posData.rank);
        lastrank = posData.rank;

        i++, it++;

        if (it == dictOfAnchorData[targetAddress].end())
            break;
    }

    best3Data.clear();
    double size = -1;
    int minSumRang = 0;
    // loop over all combinations of three elements from bestData
    for (auto it1 = bestData.begin(); it1 != bestData.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != bestData.end(); ++it2) {
            for (auto it3 = std::next(it2); it3 != bestData.end(); ++it3) {
                // insert the three elements into best3Data as a tuple
                best3Data[it1->first] = std::get<0>(it1->second);
                best3Data[it2->first] = std::get<0>(it2->second);
                best3Data[it3->first] = std::get<0>(it3->second);
                int sumRang = (std::get<1>(it1->second)
                        + std::get<1>(it2->second) + std::get<1>(it3->second));
                if (size == -1
                        || (size > calculateArea(best3Data)
                                && sumRang <= minSumRang)) {
                    size = calculateArea(best3Data);
                    minSumRang = sumRang;
                    finalData = best3Data;
                }
                best3Data.clear();

            }
        }
    }

    if (lastbestData != finalData) {

        /* std::cout
         << "*********************************bestData***************************************"
         << std::endl;
         std::string result = "";
         for (const auto &entry : bestData) {
         std::tuple<double, double> key = entry.first;
         double value = std::get<0>(entry.second) ;

         result += "(" + std::to_string(std::get<0>(key))
         + "," + std::to_string(std::get<1>(key))
         + "): " + std::to_string(value) + "\n";
         }
         std::cout << result << endl;
         std::cout
         << "************************************************************************"
         << std::endl;
         std::cout
         << "*********************************finalData***************************************"
         << std::endl;
         std::string result2 = "";
         for (const auto &entry : finalData) {
         std::tuple<double, double> key = entry.first;
         double value = entry.second;
         result2 += "(" + std::to_string(std::get<0>(key))
         + "," + std::to_string(std::get<1>(key))
         + "): " + std::to_string(value) + "\n";
         }
         std::cout << result2 << endl;
         std::cout
         << "************************************************************************"
         << std::endl;
         */

        Coord position = calculatePosition(finalData, targetAddress);
        bestData.clear();
        std::cout << targetAddress << " pos  :   " << position.x << "-"
                << position.y << endl;
        sendPostion(targetAddress, maxRank + 1, position.x, position.y);
    } else {
        bestData.clear();
    }
    lastbestData = finalData;
}
void Localisation::triMinDist(L3Address targetAddress) {
    double rssiRef = getParentModule()->getParentModule()->par("rssiRef");
    double n = getParentModule()->getParentModule()->par("n");
    int maxRank = -1;
    auto it = dictOfAnchorData[targetAddress].begin();
    best3Data.clear();

    for (int i = 0; i < 3; i++, it++) {
        const auto &posData = *it;
        best3Data[std::make_tuple(posData.x, posData.y)] = calculateDistance(posData.rssi, rssiRef, n);
        maxRank = std::max(maxRank, posData.rank);
    }

    /* std::cout << "*********************************bestData***************************************" << std::endl;
     std::string result2 = "";
     for (const auto &entry : best3Data) {
     std::tuple<double, double> key = entry.first;
     double value = entry.second;
     result2 += "(" + std::to_string(std::get<0>(key)) + ","
     + std::to_string(std::get<1>(key)) + "): "
     + std::to_string(value) + "\n";
     }
     std::cout << result2 << endl;
     std::cout << "************************************************************************" << std::endl;*/

    if (lastbestData != best3Data) {
        lastbestData = best3Data;
        Coord position = calculatePosition(best3Data, targetAddress);
        best3Data.clear();
        std::cout << targetAddress << " pos  :   " << position.x << "-"
                << position.y << endl;
        sendPostion(targetAddress, maxRank + 1, position.x, position.y);
    } else {
        best3Data.clear();
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
int Localisation::findCircleCircleIntersection(Point p1, double r1, Point p2,
        double r2, Point &i1, Point &i2) {
    double d = sqrt(
            (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

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

double Localisation::CalcuArea(double x1, double y1, double x2, double y2,
        double x3, double y3) {
    double a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double b = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    double c = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
double Localisation::calculateArea(
        std::map<std::tuple<double, double>, double> dictOfAnchorData) {

    std::vector<Localisation::Point> inter;
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

    Point p1 = { x1, y1 };
    Point p2 = { x2, y2 };
    Point p3 = { x3, y3 };

    Point i1, i2;
    int numIntersections1 = findCircleCircleIntersection(p1, r1, p2, r2, i1,
            i2);
    Point i3, i4;
    int numIntersections2 = findCircleCircleIntersection(p1, r1, p3, r3, i3,
            i4);
    Point i5, i6;
    int numIntersections3 = findCircleCircleIntersection(p2, r2, p3, r3, i5,
            i6);

    if (numIntersections1 == 2) {
        double e1 = abs(r3 - (sqrt(pow(x3 - i1.x, 2) + pow(y3 - i1.y, 2))));
        double e2 = abs(r3 - (sqrt(pow(x3 - i2.x, 2) + pow(y3 - i2.y, 2))));
        if (e2 > e1)
            inter.push_back(i1);
        else
            inter.push_back(i2);
    } else if (numIntersections1 == 1) {
        inter.push_back(i1);
    }

    if (numIntersections2 == 2) {
        double e3 = abs(r2 - (sqrt(pow(x2 - i3.x, 2) + pow(y2 - i3.y, 2))));
        double e4 = abs(r2 - (sqrt(pow(x2 - i4.x, 2) + pow(y2 - i4.y, 2))));
        if (e4 > e3)
            inter.push_back(i3);
        else
            inter.push_back(i4);
    } else if (numIntersections2 == 1) {
        inter.push_back(i3);
    }

    if (numIntersections3 == 2) {
        double e5 = abs(r1 - (sqrt(pow(x1 - i5.x, 2) + pow(y1 - i5.y, 2))));
        double e6 = abs(r1 - (sqrt(pow(x1 - i6.x, 2) + pow(y1 - i6.y, 2))));
        if (e6 > e5)
            inter.push_back(i5);
        else
            inter.push_back(i6);
    } else if (numIntersections3 == 1) {
        inter.push_back(i5);
    }

    double area = CalcuArea(inter[0].x, inter[0].y, inter[1].x, inter[1].y,
            inter[2].x, inter[2].y);
    return area;
}
Coord Localisation::calculatePosition(
        std::map<std::tuple<double, double>, double> dictOfAnchorData,
        L3Address targetAddress) {

    std::vector<Localisation::Point> inter;
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

    Point p1 = { x1, y1 };
    Point p2 = { x2, y2 };
    Point p3 = { x3, y3 };

    Point i1, i2;
    int numIntersections1 = findCircleCircleIntersection(p1, r1, p2, r2, i1,
            i2);
    Point i3, i4;
    int numIntersections2 = findCircleCircleIntersection(p1, r1, p3, r3, i3,
            i4);
    Point i5, i6;
    int numIntersections3 = findCircleCircleIntersection(p2, r2, p3, r3, i5,
            i6);

    if (numIntersections1 == 2) {
        double e1 = abs(r3 - (sqrt(pow(x3 - i1.x, 2) + pow(y3 - i1.y, 2))));
        double e2 = abs(r3 - (sqrt(pow(x3 - i2.x, 2) + pow(y3 - i2.y, 2))));
        if (e2 > e1)
            inter.push_back(i1);
        else
            inter.push_back(i2);
    } else if (numIntersections1 == 1) {
        inter.push_back(i1);
    }

    if (numIntersections2 == 2) {
        double e3 = abs(r2 - (sqrt(pow(x2 - i3.x, 2) + pow(y2 - i3.y, 2))));
        double e4 = abs(r2 - (sqrt(pow(x2 - i4.x, 2) + pow(y2 - i4.y, 2))));
        if (e4 > e3)
            inter.push_back(i3);
        else
            inter.push_back(i4);
    } else if (numIntersections2 == 1) {
        inter.push_back(i3);
    }

    if (numIntersections3 == 2) {
        double e5 = abs(r1 - (sqrt(pow(x1 - i5.x, 2) + pow(y1 - i5.y, 2))));
        double e6 = abs(r1 - (sqrt(pow(x1 - i6.x, 2) + pow(y1 - i6.y, 2))));
        if (e6 > e5)
            inter.push_back(i5);
        else
            inter.push_back(i6);
    } else if (numIntersections3 == 1) {
        inter.push_back(i5);
    }

    double xg = 0, yg = 0;
    int i = 0;
    for (std::vector<Localisation::Point>::iterator it = inter.begin();
            it != inter.end(); it++) {
        xg += it->x;
        yg += it->y;
        i++;

    }
    yg = yg / i;
    xg = xg / i;

    /*
     point1 = new cOvalFigure("point1");
     point1->setBounds(cFigure::Rectangle(0, 0, r1*2, r1*2));
     point1->setFilled(false);
     point1->setFillColor(cFigure::RED);
     point1->setPosition(cFigure::Point(x1, y1),
     cFigure::ANCHOR_CENTER);
     cCanvas *d = getParentModule()->getParentModule()->getCanvas();
     d->addFigure(point1);

     point2 = new cOvalFigure("point2");
     point2->setBounds(cFigure::Rectangle(0, 0, r2*2, r2*2));
     point2->setFilled(false);
     point2->setFillColor(cFigure::RED);
     point2->setPosition(cFigure::Point(x2, y2),
     cFigure::ANCHOR_CENTER);
     d->addFigure(point2);

     point3 = new cOvalFigure("point3");
     point3->setBounds(cFigure::Rectangle(0, 0, r3*2, r3*2));
     point3->setFilled(false);
     point3->setFillColor(cFigure::RED);
     point3->setPosition(cFigure::Point(x3, y3),
     cFigure::ANCHOR_CENTER);
     d->addFigure(point3);

     point4 = new cOvalFigure("point4");
     point4->setBounds(cFigure::Rectangle(0, 0, 1, 1));
     point4->setFilled(true);
     point4->setFillColor(cFigure::BLUE);
     point4->setPosition(cFigure::Point(inter[0].x,inter[0].y),
     cFigure::ANCHOR_CENTER);
     d->addFigure(point4);

     point5 = new cOvalFigure("point5");
     point5->setBounds(cFigure::Rectangle(0, 0, 1, 1));
     point5->setFilled(true);
     point5->setFillColor(cFigure::RED);
     point5->setPosition(cFigure::Point(inter[1].x,inter[1].y),
     cFigure::ANCHOR_CENTER);
     d->addFigure(point5);

     point6 = new cOvalFigure("point6");
     point6->setBounds(cFigure::Rectangle(-1, -1, 1, 1));
     point6->setFilled(true);
     point6->setFillColor(cFigure::RED);
     point6->setPosition(cFigure::Point(inter[2].x,inter[2].y),
     cFigure::ANCHOR_CENTER);
     d->addFigure(point6);*/

    if (point != nullptr && lastAdr == targetAddress) {
        point->setFillColor(cFigure::YELLOW);
    }
    lastAdr = targetAddress;

    cCanvas *d = getParentModule()->getParentModule()->getCanvas();

    point = new cOvalFigure("point");
    point->setBounds(cFigure::Rectangle(-1, -1, 1, 1));
    point->setFilled(true);
    point->setFillColor(cFigure::RED);
    point->setPosition(cFigure::Point(xg, yg), cFigure::ANCHOR_CENTER);
    d->addFigure(point);
    return Coord(xg, yg);

}

double Localisation::calculateRssi(cMessage *msg) {
    auto radioMsg = check_and_cast<Packet*>(msg);
    auto signalPowerInd = radioMsg->getTag<SignalPowerInd>();
    auto rxPower = signalPowerInd->getPower().get();
    double signalPowerdBm = 10 * log10(rxPower / 1e-3);
    return signalPowerdBm;
}
void Localisation::sendPostion(L3Address destAddress, int rank, double x,
        double y) {
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
    getParentModule()->bubble("Sending posInfo");

}
void Localisation::sendAnchorDataToStation(L3Address stationAddress,
        L3Address targetAddress, cMessage *msg) {
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

void Localisation::findMe()

{
    auto FindMe = makeShared<WhereIam>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    FindMe->setChunkLength(b(128));
    FindMe->setSrcAddress(source);
    auto packet = new Packet("FindMe", FindMe);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(
            Ipv4Address(255, 255, 255, 255));
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    FindMe = nullptr;
    cancelEvent(event);
    scheduleAt(simTime() + helloInterval + broadcastDelay->doubleValue(),
            event);
    getParentModule()->bubble("Broadcasting FindMe");
}

void Localisation::updateAnchor() {
    auto helloStation = makeShared<helloAnchor>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    helloStation->setChunkLength(b(128));
    helloStation->setSrcAddress(source);
    auto packet = new Packet("helloStation", helloStation);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(
            getAdressOf("station"));
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    helloStation = nullptr;
    getParentModule()->bubble(" hello for station");
}

void Localisation::updateTarget() {
    auto helloStation = makeShared<helloTarget>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    helloStation->setChunkLength(b(128));
    helloStation->setSrcAddress(source);
    auto packet = new Packet("helloStation", helloStation);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(
            getAdressOf("station"));
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    helloStation = nullptr;

    getParentModule()->bubble(" hello for station");
}

void Localisation::updateStation(L3Address targetAddress) {
    auto hellooTarget = makeShared<helloTarget>();
    Ipv4Address source =
            (interface80211ptr->getProtocolData<Ipv4InterfaceData>()->getIPAddress());
    hellooTarget->setChunkLength(b(128));
    hellooTarget->setSrcAddress(source);
    auto packet = new Packet("hellooTarget", hellooTarget);
    packet->addTagIfAbsent<L3AddressReq>()->setDestAddress(targetAddress);
    packet->addTagIfAbsent<L3AddressReq>()->setSrcAddress(source);
    packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(
            interface80211ptr->getInterfaceId());
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::manet);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    send(packet, "socketOut");
    packet = nullptr;
    hellooTarget = nullptr;
    getParentModule()->bubble(" hello for target");
}

void Localisation::start() {
    std::cout << " start  :   " << endl;

    if (nodeIs("anchor")) {
        rank = 0;
        pos = getMyPosition();
    }

    for (int i = 0; i < ift->getNumInterfaces(); i++) {
        auto ie = ift->getInterface(i);
        auto name = ie->getInterfaceName();

        if (strstr(name, "wlan") != nullptr) {
            interface80211ptr = ie;
            break;
        }
    }
    if (nodeIs("anchor")) {
        rank = 0;
        pos = getMyPosition();
        scheduleAt(simTime(), NewAnchor);
    } else if (nodeIs("target")) {
        scheduleAt(simTime() + 0.5, event);
        scheduleAt(simTime(), NewTarget);

    }

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
