//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/localisation/LocalisationHello.msg.
//

#ifndef __INET_LOCALISATIONHELLO_M_H
#define __INET_LOCALISATIONHELLO_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class WhereIam;
class CalculatedPos;
class AnchorData;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/common/L3Address_m.h" // import inet.networklayer.common.L3Address


namespace inet {

/**
 * Class generated from <tt>inet/routing/localisation/LocalisationHello.msg:23</tt> by opp_msgtool.
 * <pre>
 * class WhereIam extends FieldsChunk
 * {
 *     L3Address srcAddress;
 * }
 * </pre>
 */
class INET_API WhereIam : public ::inet::FieldsChunk
{
  protected:
    L3Address srcAddress;

  private:
    void copy(const WhereIam& other);

  protected:
    bool operator==(const WhereIam&) = delete;

  public:
    WhereIam();
    WhereIam(const WhereIam& other);
    virtual ~WhereIam();
    WhereIam& operator=(const WhereIam& other);
    virtual WhereIam *dup() const override {return new WhereIam(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const L3Address& getSrcAddress() const;
    virtual L3Address& getSrcAddressForUpdate() { handleChange();return const_cast<L3Address&>(const_cast<WhereIam*>(this)->getSrcAddress());}
    virtual void setSrcAddress(const L3Address& srcAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const WhereIam& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, WhereIam& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/localisation/LocalisationHello.msg:27</tt> by opp_msgtool.
 * <pre>
 * class CalculatedPos extends FieldsChunk
 * {
 *     L3Address srcAddress;
 *     int rank;
 *     double x;
 *     double y;
 * }
 * </pre>
 */
class INET_API CalculatedPos : public ::inet::FieldsChunk
{
  protected:
    L3Address srcAddress;
    int rank = 0;
    double x = 0;
    double y = 0;

  private:
    void copy(const CalculatedPos& other);

  protected:
    bool operator==(const CalculatedPos&) = delete;

  public:
    CalculatedPos();
    CalculatedPos(const CalculatedPos& other);
    virtual ~CalculatedPos();
    CalculatedPos& operator=(const CalculatedPos& other);
    virtual CalculatedPos *dup() const override {return new CalculatedPos(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const L3Address& getSrcAddress() const;
    virtual L3Address& getSrcAddressForUpdate() { handleChange();return const_cast<L3Address&>(const_cast<CalculatedPos*>(this)->getSrcAddress());}
    virtual void setSrcAddress(const L3Address& srcAddress);

    virtual int getRank() const;
    virtual void setRank(int rank);

    virtual double getX() const;
    virtual void setX(double x);

    virtual double getY() const;
    virtual void setY(double y);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CalculatedPos& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CalculatedPos& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/localisation/LocalisationHello.msg:34</tt> by opp_msgtool.
 * <pre>
 * class AnchorData extends FieldsChunk
 * {
 *     int rank;
 *     L3Address targetAddress;
 *     double x;
 *     double y;
 *     double rssi;
 * }
 * </pre>
 */
class INET_API AnchorData : public ::inet::FieldsChunk
{
  protected:
    int rank = 0;
    L3Address targetAddress;
    double x = 0;
    double y = 0;
    double rssi = 0;

  private:
    void copy(const AnchorData& other);

  protected:
    bool operator==(const AnchorData&) = delete;

  public:
    AnchorData();
    AnchorData(const AnchorData& other);
    virtual ~AnchorData();
    AnchorData& operator=(const AnchorData& other);
    virtual AnchorData *dup() const override {return new AnchorData(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getRank() const;
    virtual void setRank(int rank);

    virtual const L3Address& getTargetAddress() const;
    virtual L3Address& getTargetAddressForUpdate() { handleChange();return const_cast<L3Address&>(const_cast<AnchorData*>(this)->getTargetAddress());}
    virtual void setTargetAddress(const L3Address& targetAddress);

    virtual double getX() const;
    virtual void setX(double x);

    virtual double getY() const;
    virtual void setY(double y);

    virtual double getRssi() const;
    virtual void setRssi(double rssi);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AnchorData& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AnchorData& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::WhereIam *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::WhereIam*>(ptr.get<cObject>()); }
template<> inline inet::CalculatedPos *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::CalculatedPos*>(ptr.get<cObject>()); }
template<> inline inet::AnchorData *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::AnchorData*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_LOCALISATIONHELLO_M_H

