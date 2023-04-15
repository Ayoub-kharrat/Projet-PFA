//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/clock/model/LocalisationHello.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "LocalisationHello_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

Register_Class(LocalisationHello)

LocalisationHello::LocalisationHello() : ::inet::FieldsChunk()
{
}

LocalisationHello::LocalisationHello(const LocalisationHello& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LocalisationHello::~LocalisationHello()
{
}

LocalisationHello& LocalisationHello::operator=(const LocalisationHello& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LocalisationHello::copy(const LocalisationHello& other)
{
    this->srcAddress = other.srcAddress;
    this->sequencenumber = other.sequencenumber;
    this->nextAddress = other.nextAddress;
    this->hopdistance = other.hopdistance;
    this->type = other.type;
}

void LocalisationHello::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->sequencenumber);
    doParsimPacking(b,this->nextAddress);
    doParsimPacking(b,this->hopdistance);
    doParsimPacking(b,this->type);
}

void LocalisationHello::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->sequencenumber);
    doParsimUnpacking(b,this->nextAddress);
    doParsimUnpacking(b,this->hopdistance);
    doParsimUnpacking(b,this->type);
}

const Ipv4Address& LocalisationHello::getSrcAddress() const
{
    return this->srcAddress;
}

void LocalisationHello::setSrcAddress(const Ipv4Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

unsigned int LocalisationHello::getSequencenumber() const
{
    return this->sequencenumber;
}

void LocalisationHello::setSequencenumber(unsigned int sequencenumber)
{
    handleChange();
    this->sequencenumber = sequencenumber;
}

const Ipv4Address& LocalisationHello::getNextAddress() const
{
    return this->nextAddress;
}

void LocalisationHello::setNextAddress(const Ipv4Address& nextAddress)
{
    handleChange();
    this->nextAddress = nextAddress;
}

int LocalisationHello::getHopdistance() const
{
    return this->hopdistance;
}

void LocalisationHello::setHopdistance(int hopdistance)
{
    handleChange();
    this->hopdistance = hopdistance;
}

const char * LocalisationHello::getType() const
{
    return this->type.c_str();
}

void LocalisationHello::setType(const char * type)
{
    handleChange();
    this->type = type;
}

class LocalisationHelloDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
        FIELD_sequencenumber,
        FIELD_nextAddress,
        FIELD_hopdistance,
        FIELD_type,
    };
  public:
    LocalisationHelloDescriptor();
    virtual ~LocalisationHelloDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LocalisationHelloDescriptor)

LocalisationHelloDescriptor::LocalisationHelloDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LocalisationHello)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LocalisationHelloDescriptor::~LocalisationHelloDescriptor()
{
    delete[] propertyNames;
}

bool LocalisationHelloDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LocalisationHello *>(obj)!=nullptr;
}

const char **LocalisationHelloDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LocalisationHelloDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LocalisationHelloDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LocalisationHelloDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_sequencenumber
        0,    // FIELD_nextAddress
        FD_ISEDITABLE,    // FIELD_hopdistance
        FD_ISEDITABLE,    // FIELD_type
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LocalisationHelloDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "sequencenumber",
        "nextAddress",
        "hopdistance",
        "type",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LocalisationHelloDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequencenumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "nextAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hopdistance") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LocalisationHelloDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_srcAddress
        "unsigned int",    // FIELD_sequencenumber
        "inet::Ipv4Address",    // FIELD_nextAddress
        "int",    // FIELD_hopdistance
        "string",    // FIELD_type
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LocalisationHelloDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LocalisationHelloDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LocalisationHelloDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LocalisationHelloDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LocalisationHello'", field);
    }
}

const char *LocalisationHelloDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LocalisationHelloDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_sequencenumber: return ulong2string(pp->getSequencenumber());
        case FIELD_nextAddress: return pp->getNextAddress().str();
        case FIELD_hopdistance: return long2string(pp->getHopdistance());
        case FIELD_type: return oppstring2string(pp->getType());
        default: return "";
    }
}

void LocalisationHelloDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        case FIELD_sequencenumber: pp->setSequencenumber(string2ulong(value)); break;
        case FIELD_hopdistance: pp->setHopdistance(string2long(value)); break;
        case FIELD_type: pp->setType((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LocalisationHello'", field);
    }
}

omnetpp::cValue LocalisationHelloDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_sequencenumber: return (omnetpp::intval_t)(pp->getSequencenumber());
        case FIELD_nextAddress: return omnetpp::toAnyPtr(&pp->getNextAddress()); break;
        case FIELD_hopdistance: return pp->getHopdistance();
        case FIELD_type: return pp->getType();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LocalisationHello' as cValue -- field index out of range?", field);
    }
}

void LocalisationHelloDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        case FIELD_sequencenumber: pp->setSequencenumber(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_hopdistance: pp->setHopdistance(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_type: pp->setType(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LocalisationHello'", field);
    }
}

const char *LocalisationHelloDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LocalisationHelloDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_nextAddress: return omnetpp::toAnyPtr(&pp->getNextAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LocalisationHelloDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LocalisationHello *pp = omnetpp::fromAnyPtr<LocalisationHello>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LocalisationHello'", field);
    }
}

Register_Class(XedMsg)

XedMsg::XedMsg() : ::inet::FieldsChunk()
{
}

XedMsg::XedMsg(const XedMsg& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

XedMsg::~XedMsg()
{
}

XedMsg& XedMsg::operator=(const XedMsg& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void XedMsg::copy(const XedMsg& other)
{
    this->srcAddress = other.srcAddress;
    this->sequencenumber = other.sequencenumber;
    this->dstAddress = other.dstAddress;
    this->random = other.random;
}

void XedMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->sequencenumber);
    doParsimPacking(b,this->dstAddress);
    doParsimPacking(b,this->random);
}

void XedMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->sequencenumber);
    doParsimUnpacking(b,this->dstAddress);
    doParsimUnpacking(b,this->random);
}

const Ipv4Address& XedMsg::getSrcAddress() const
{
    return this->srcAddress;
}

void XedMsg::setSrcAddress(const Ipv4Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

unsigned int XedMsg::getSequencenumber() const
{
    return this->sequencenumber;
}

void XedMsg::setSequencenumber(unsigned int sequencenumber)
{
    handleChange();
    this->sequencenumber = sequencenumber;
}

const Ipv4Address& XedMsg::getDstAddress() const
{
    return this->dstAddress;
}

void XedMsg::setDstAddress(const Ipv4Address& dstAddress)
{
    handleChange();
    this->dstAddress = dstAddress;
}

double XedMsg::getRandom() const
{
    return this->random;
}

void XedMsg::setRandom(double random)
{
    handleChange();
    this->random = random;
}

class XedMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
        FIELD_sequencenumber,
        FIELD_dstAddress,
        FIELD_random,
    };
  public:
    XedMsgDescriptor();
    virtual ~XedMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(XedMsgDescriptor)

XedMsgDescriptor::XedMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::XedMsg)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

XedMsgDescriptor::~XedMsgDescriptor()
{
    delete[] propertyNames;
}

bool XedMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<XedMsg *>(obj)!=nullptr;
}

const char **XedMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *XedMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int XedMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int XedMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_sequencenumber
        0,    // FIELD_dstAddress
        FD_ISEDITABLE,    // FIELD_random
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *XedMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "sequencenumber",
        "dstAddress",
        "random",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int XedMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequencenumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "dstAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "random") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *XedMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_srcAddress
        "unsigned int",    // FIELD_sequencenumber
        "inet::Ipv4Address",    // FIELD_dstAddress
        "double",    // FIELD_random
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **XedMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *XedMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int XedMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void XedMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'XedMsg'", field);
    }
}

const char *XedMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string XedMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_sequencenumber: return ulong2string(pp->getSequencenumber());
        case FIELD_dstAddress: return pp->getDstAddress().str();
        case FIELD_random: return double2string(pp->getRandom());
        default: return "";
    }
}

void XedMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        case FIELD_sequencenumber: pp->setSequencenumber(string2ulong(value)); break;
        case FIELD_random: pp->setRandom(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XedMsg'", field);
    }
}

omnetpp::cValue XedMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_sequencenumber: return (omnetpp::intval_t)(pp->getSequencenumber());
        case FIELD_dstAddress: return omnetpp::toAnyPtr(&pp->getDstAddress()); break;
        case FIELD_random: return pp->getRandom();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'XedMsg' as cValue -- field index out of range?", field);
    }
}

void XedMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        case FIELD_sequencenumber: pp->setSequencenumber(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_random: pp->setRandom(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XedMsg'", field);
    }
}

const char *XedMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr XedMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_dstAddress: return omnetpp::toAnyPtr(&pp->getDstAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void XedMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    XedMsg *pp = omnetpp::fromAnyPtr<XedMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XedMsg'", field);
    }
}

Register_Class(AnchorData)

AnchorData::AnchorData() : ::inet::FieldsChunk()
{
}

AnchorData::AnchorData(const AnchorData& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

AnchorData::~AnchorData()
{
}

AnchorData& AnchorData::operator=(const AnchorData& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void AnchorData::copy(const AnchorData& other)
{
    this->srcAddress = other.srcAddress;
    this->sequencenumber = other.sequencenumber;
    this->nextAddress = other.nextAddress;
    this->hopdistance = other.hopdistance;
    this->x = other.x;
    this->y = other.y;
    this->rssi = other.rssi;
    this->type = other.type;
}

void AnchorData::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->sequencenumber);
    doParsimPacking(b,this->nextAddress);
    doParsimPacking(b,this->hopdistance);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
    doParsimPacking(b,this->rssi);
    doParsimPacking(b,this->type);
}

void AnchorData::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->sequencenumber);
    doParsimUnpacking(b,this->nextAddress);
    doParsimUnpacking(b,this->hopdistance);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
    doParsimUnpacking(b,this->rssi);
    doParsimUnpacking(b,this->type);
}

const Ipv4Address& AnchorData::getSrcAddress() const
{
    return this->srcAddress;
}

void AnchorData::setSrcAddress(const Ipv4Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

unsigned int AnchorData::getSequencenumber() const
{
    return this->sequencenumber;
}

void AnchorData::setSequencenumber(unsigned int sequencenumber)
{
    handleChange();
    this->sequencenumber = sequencenumber;
}

const Ipv4Address& AnchorData::getNextAddress() const
{
    return this->nextAddress;
}

void AnchorData::setNextAddress(const Ipv4Address& nextAddress)
{
    handleChange();
    this->nextAddress = nextAddress;
}

int AnchorData::getHopdistance() const
{
    return this->hopdistance;
}

void AnchorData::setHopdistance(int hopdistance)
{
    handleChange();
    this->hopdistance = hopdistance;
}

double AnchorData::getX() const
{
    return this->x;
}

void AnchorData::setX(double x)
{
    handleChange();
    this->x = x;
}

double AnchorData::getY() const
{
    return this->y;
}

void AnchorData::setY(double y)
{
    handleChange();
    this->y = y;
}

double AnchorData::getRssi() const
{
    return this->rssi;
}

void AnchorData::setRssi(double rssi)
{
    handleChange();
    this->rssi = rssi;
}

const char * AnchorData::getType() const
{
    return this->type.c_str();
}

void AnchorData::setType(const char * type)
{
    handleChange();
    this->type = type;
}

class AnchorDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
        FIELD_sequencenumber,
        FIELD_nextAddress,
        FIELD_hopdistance,
        FIELD_x,
        FIELD_y,
        FIELD_rssi,
        FIELD_type,
    };
  public:
    AnchorDataDescriptor();
    virtual ~AnchorDataDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AnchorDataDescriptor)

AnchorDataDescriptor::AnchorDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::AnchorData)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

AnchorDataDescriptor::~AnchorDataDescriptor()
{
    delete[] propertyNames;
}

bool AnchorDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AnchorData *>(obj)!=nullptr;
}

const char **AnchorDataDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AnchorDataDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AnchorDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int AnchorDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_sequencenumber
        0,    // FIELD_nextAddress
        FD_ISEDITABLE,    // FIELD_hopdistance
        FD_ISEDITABLE,    // FIELD_x
        FD_ISEDITABLE,    // FIELD_y
        FD_ISEDITABLE,    // FIELD_rssi
        FD_ISEDITABLE,    // FIELD_type
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *AnchorDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "sequencenumber",
        "nextAddress",
        "hopdistance",
        "x",
        "y",
        "rssi",
        "type",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int AnchorDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequencenumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "nextAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hopdistance") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "x") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "y") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "rssi") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *AnchorDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_srcAddress
        "unsigned int",    // FIELD_sequencenumber
        "inet::Ipv4Address",    // FIELD_nextAddress
        "int",    // FIELD_hopdistance
        "double",    // FIELD_x
        "double",    // FIELD_y
        "double",    // FIELD_rssi
        "string",    // FIELD_type
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **AnchorDataDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AnchorDataDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AnchorDataDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AnchorDataDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AnchorData'", field);
    }
}

const char *AnchorDataDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AnchorDataDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_sequencenumber: return ulong2string(pp->getSequencenumber());
        case FIELD_nextAddress: return pp->getNextAddress().str();
        case FIELD_hopdistance: return long2string(pp->getHopdistance());
        case FIELD_x: return double2string(pp->getX());
        case FIELD_y: return double2string(pp->getY());
        case FIELD_rssi: return double2string(pp->getRssi());
        case FIELD_type: return oppstring2string(pp->getType());
        default: return "";
    }
}

void AnchorDataDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        case FIELD_sequencenumber: pp->setSequencenumber(string2ulong(value)); break;
        case FIELD_hopdistance: pp->setHopdistance(string2long(value)); break;
        case FIELD_x: pp->setX(string2double(value)); break;
        case FIELD_y: pp->setY(string2double(value)); break;
        case FIELD_rssi: pp->setRssi(string2double(value)); break;
        case FIELD_type: pp->setType((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AnchorData'", field);
    }
}

omnetpp::cValue AnchorDataDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_sequencenumber: return (omnetpp::intval_t)(pp->getSequencenumber());
        case FIELD_nextAddress: return omnetpp::toAnyPtr(&pp->getNextAddress()); break;
        case FIELD_hopdistance: return pp->getHopdistance();
        case FIELD_x: return pp->getX();
        case FIELD_y: return pp->getY();
        case FIELD_rssi: return pp->getRssi();
        case FIELD_type: return pp->getType();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AnchorData' as cValue -- field index out of range?", field);
    }
}

void AnchorDataDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        case FIELD_sequencenumber: pp->setSequencenumber(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_hopdistance: pp->setHopdistance(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_x: pp->setX(value.doubleValue()); break;
        case FIELD_y: pp->setY(value.doubleValue()); break;
        case FIELD_rssi: pp->setRssi(value.doubleValue()); break;
        case FIELD_type: pp->setType(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AnchorData'", field);
    }
}

const char *AnchorDataDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AnchorDataDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_nextAddress: return omnetpp::toAnyPtr(&pp->getNextAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AnchorDataDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AnchorData *pp = omnetpp::fromAnyPtr<AnchorData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AnchorData'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

