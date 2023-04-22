//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/localisation/LocalisationHello.msg.
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

Register_Class(WhereIam)

WhereIam::WhereIam() : ::inet::FieldsChunk()
{
}

WhereIam::WhereIam(const WhereIam& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

WhereIam::~WhereIam()
{
}

WhereIam& WhereIam::operator=(const WhereIam& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void WhereIam::copy(const WhereIam& other)
{
    this->srcAddress = other.srcAddress;
}

void WhereIam::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
}

void WhereIam::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
}

const L3Address& WhereIam::getSrcAddress() const
{
    return this->srcAddress;
}

void WhereIam::setSrcAddress(const L3Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

class WhereIamDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
    };
  public:
    WhereIamDescriptor();
    virtual ~WhereIamDescriptor();

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

Register_ClassDescriptor(WhereIamDescriptor)

WhereIamDescriptor::WhereIamDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::WhereIam)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

WhereIamDescriptor::~WhereIamDescriptor()
{
    delete[] propertyNames;
}

bool WhereIamDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WhereIam *>(obj)!=nullptr;
}

const char **WhereIamDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *WhereIamDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int WhereIamDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int WhereIamDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *WhereIamDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int WhereIamDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *WhereIamDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_srcAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **WhereIamDescriptor::getFieldPropertyNames(int field) const
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

const char *WhereIamDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int WhereIamDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void WhereIamDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'WhereIam'", field);
    }
}

const char *WhereIamDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WhereIamDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        default: return "";
    }
}

void WhereIamDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WhereIam'", field);
    }
}

omnetpp::cValue WhereIamDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'WhereIam' as cValue -- field index out of range?", field);
    }
}

void WhereIamDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WhereIam'", field);
    }
}

const char *WhereIamDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr WhereIamDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void WhereIamDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    WhereIam *pp = omnetpp::fromAnyPtr<WhereIam>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WhereIam'", field);
    }
}

Register_Class(CalculatedPos)

CalculatedPos::CalculatedPos() : ::inet::FieldsChunk()
{
}

CalculatedPos::CalculatedPos(const CalculatedPos& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

CalculatedPos::~CalculatedPos()
{
}

CalculatedPos& CalculatedPos::operator=(const CalculatedPos& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void CalculatedPos::copy(const CalculatedPos& other)
{
    this->srcAddress = other.srcAddress;
    this->rank = other.rank;
    this->x = other.x;
    this->y = other.y;
}

void CalculatedPos::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->rank);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
}

void CalculatedPos::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->rank);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
}

const L3Address& CalculatedPos::getSrcAddress() const
{
    return this->srcAddress;
}

void CalculatedPos::setSrcAddress(const L3Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

int CalculatedPos::getRank() const
{
    return this->rank;
}

void CalculatedPos::setRank(int rank)
{
    handleChange();
    this->rank = rank;
}

double CalculatedPos::getX() const
{
    return this->x;
}

void CalculatedPos::setX(double x)
{
    handleChange();
    this->x = x;
}

double CalculatedPos::getY() const
{
    return this->y;
}

void CalculatedPos::setY(double y)
{
    handleChange();
    this->y = y;
}

class CalculatedPosDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
        FIELD_rank,
        FIELD_x,
        FIELD_y,
    };
  public:
    CalculatedPosDescriptor();
    virtual ~CalculatedPosDescriptor();

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

Register_ClassDescriptor(CalculatedPosDescriptor)

CalculatedPosDescriptor::CalculatedPosDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CalculatedPos)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

CalculatedPosDescriptor::~CalculatedPosDescriptor()
{
    delete[] propertyNames;
}

bool CalculatedPosDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CalculatedPos *>(obj)!=nullptr;
}

const char **CalculatedPosDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CalculatedPosDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CalculatedPosDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int CalculatedPosDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_rank
        FD_ISEDITABLE,    // FIELD_x
        FD_ISEDITABLE,    // FIELD_y
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *CalculatedPosDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "rank",
        "x",
        "y",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int CalculatedPosDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "rank") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "x") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "y") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *CalculatedPosDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_srcAddress
        "int",    // FIELD_rank
        "double",    // FIELD_x
        "double",    // FIELD_y
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **CalculatedPosDescriptor::getFieldPropertyNames(int field) const
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

const char *CalculatedPosDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CalculatedPosDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CalculatedPosDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CalculatedPos'", field);
    }
}

const char *CalculatedPosDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CalculatedPosDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_rank: return long2string(pp->getRank());
        case FIELD_x: return double2string(pp->getX());
        case FIELD_y: return double2string(pp->getY());
        default: return "";
    }
}

void CalculatedPosDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        case FIELD_rank: pp->setRank(string2long(value)); break;
        case FIELD_x: pp->setX(string2double(value)); break;
        case FIELD_y: pp->setY(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CalculatedPos'", field);
    }
}

omnetpp::cValue CalculatedPosDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_rank: return pp->getRank();
        case FIELD_x: return pp->getX();
        case FIELD_y: return pp->getY();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CalculatedPos' as cValue -- field index out of range?", field);
    }
}

void CalculatedPosDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        case FIELD_rank: pp->setRank(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_x: pp->setX(value.doubleValue()); break;
        case FIELD_y: pp->setY(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CalculatedPos'", field);
    }
}

const char *CalculatedPosDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CalculatedPosDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CalculatedPosDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CalculatedPos *pp = omnetpp::fromAnyPtr<CalculatedPos>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CalculatedPos'", field);
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
    this->rank = other.rank;
    this->targetAddress = other.targetAddress;
    this->x = other.x;
    this->y = other.y;
    this->rssi = other.rssi;
}

void AnchorData::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->rank);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
    doParsimPacking(b,this->rssi);
}

void AnchorData::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->rank);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
    doParsimUnpacking(b,this->rssi);
}

int AnchorData::getRank() const
{
    return this->rank;
}

void AnchorData::setRank(int rank)
{
    handleChange();
    this->rank = rank;
}

const L3Address& AnchorData::getTargetAddress() const
{
    return this->targetAddress;
}

void AnchorData::setTargetAddress(const L3Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
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

class AnchorDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_rank,
        FIELD_targetAddress,
        FIELD_x,
        FIELD_y,
        FIELD_rssi,
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
    return base ? 5+base->getFieldCount() : 5;
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
        FD_ISEDITABLE,    // FIELD_rank
        0,    // FIELD_targetAddress
        FD_ISEDITABLE,    // FIELD_x
        FD_ISEDITABLE,    // FIELD_y
        FD_ISEDITABLE,    // FIELD_rssi
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
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
        "rank",
        "targetAddress",
        "x",
        "y",
        "rssi",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int AnchorDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "rank") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "targetAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "x") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "y") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "rssi") == 0) return baseIndex + 4;
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
        "int",    // FIELD_rank
        "inet::L3Address",    // FIELD_targetAddress
        "double",    // FIELD_x
        "double",    // FIELD_y
        "double",    // FIELD_rssi
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
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
        case FIELD_rank: return long2string(pp->getRank());
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_x: return double2string(pp->getX());
        case FIELD_y: return double2string(pp->getY());
        case FIELD_rssi: return double2string(pp->getRssi());
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
        case FIELD_rank: pp->setRank(string2long(value)); break;
        case FIELD_x: pp->setX(string2double(value)); break;
        case FIELD_y: pp->setY(string2double(value)); break;
        case FIELD_rssi: pp->setRssi(string2double(value)); break;
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
        case FIELD_rank: return pp->getRank();
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_x: return pp->getX();
        case FIELD_y: return pp->getY();
        case FIELD_rssi: return pp->getRssi();
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
        case FIELD_rank: pp->setRank(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_x: pp->setX(value.doubleValue()); break;
        case FIELD_y: pp->setY(value.doubleValue()); break;
        case FIELD_rssi: pp->setRssi(value.doubleValue()); break;
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
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
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

