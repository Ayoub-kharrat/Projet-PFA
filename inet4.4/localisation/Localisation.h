#ifndef __INET_Localisation_H
#define __INET_Localisation_H

#include <omnetpp/simtime_t.h>
#include <map>
#include <string>
#include <tuple>

#include "../../applications/base/ApplicationBase.h"
#include "../../common/geometry/common/Coord.h"
#include "../../common/InitStageRegistry.h"
#include "../../networklayer/common/L3Address.h"
#include "../../transportlayer/contract/udp/UdpSocket.h"

namespace inet
{
struct PosData {
    int rank;
    double rssi;
    double x;
    double y;
};
  class Localisation : public ApplicationBase, public UdpSocket::ICallback
  {
  protected:
    bool dontFragment = false;
    cOvalFigure *point;
    bool filled = true;
    // state
    int rank;
    std::string type;
    Coord pos;
    UdpSocket socket;
    cMessage *selfMsg = nullptr;
    cModule *host = nullptr;
    cMessage *event = nullptr;
    simtime_t helloInterval;
    cPar *broadcastDelay = nullptr;
    IInterfaceTable *ift = nullptr;
    L3Address *lastAddress;
    NetworkInterface *interface80211ptr = nullptr;
    std::map<std::tuple<double, double>, double> bestData;
    std::map<L3Address, std::list<PosData>> dictOfAnchorData;
    int interfaceId = -1;
  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    void handleSelfMessage(cMessage *msg);
    // lifecycle
    virtual void handleStartOperation(LifecycleOperation *operation) override { start(); }
    virtual void handleStopOperation(LifecycleOperation *operation) override { stop(); }
    virtual void handleCrashOperation(LifecycleOperation *operation) override { stop(); }
    void start();
    void stop();
    void findMe();
    void sendAnchorDataToStation(L3Address stationAddress,L3Address targetAddress,cMessage *msg);
    void sendPostion(L3Address destAddress,int rank,double x,double y);
    double calculateDistance(double rssi,double rssiRef,double n);
    struct Point;
    int findCircleCircleIntersection(Point p1, double r1, Point p2, double r2, Point &i1, Point &i2);

    Coord calculatePosition(std::map<std::tuple<double, double>, double> dictOfAnchorData);
    Coord getMyPosition();
    bool nodeIs(std::string type);
    double calculateRssi(cMessage *msg);
    L3Address getAdressOf(const char* nodeName );
    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    virtual void socketClosed(UdpSocket *socket) override;
  public:
    Localisation();
    ~Localisation();
  };
} /* namespace inet */
#endif /* INET_MYPROTOCOL_MYPROTOCOL_H_ */
