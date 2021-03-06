/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Rtdb_TYPES_H
#define Rtdb_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace cn { namespace oge { namespace kdm { namespace rtdb { namespace thrift { namespace api {

struct RtSummaryType {
  enum type {
    MAX_VAL = 1,
    MIN_VAL = 2,
    AVG_VAL = 3
  };
};

extern const std::map<int, const char*> _RtSummaryType_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const RtSummaryType::type& val);

struct RtDataState {
  enum type {
    NOT_EXISTS = 1,
    PROCESS_FAIL = 2
  };
};

extern const std::map<int, const char*> _RtDataState_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const RtDataState::type& val);

struct ErrorCode {
  enum type {
    OTHER = 0,
    NOT_IMPLEMENT = 1,
    INVALID_PARAM = 2,
    CONNECT_FAILD = 3
  };
};

extern const std::map<int, const char*> _ErrorCode_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const ErrorCode::type& val);

class RequestException;

class RtValue;

class RtSnapshotData;

class RtHistoryData;

class RtSummaryValue;

class RtSummaryData;

typedef struct _RequestException__isset {
  _RequestException__isset() : message(false) {}
  bool message :1;
} _RequestException__isset;

class RequestException : public ::apache::thrift::TException {
 public:

  RequestException(const RequestException&);
  RequestException& operator=(const RequestException&);
  RequestException() : code((ErrorCode::type)0), message() {
  }

  virtual ~RequestException() throw();
  ErrorCode::type code;
  std::string message;

  _RequestException__isset __isset;

  void __set_code(const ErrorCode::type val);

  void __set_message(const std::string& val);

  bool operator == (const RequestException & rhs) const
  {
    if (!(code == rhs.code))
      return false;
    if (__isset.message != rhs.__isset.message)
      return false;
    else if (__isset.message && !(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const RequestException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RequestException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(RequestException &a, RequestException &b);

std::ostream& operator<<(std::ostream& out, const RequestException& obj);


class RtValue : public virtual ::apache::thrift::TBase {
 public:

  RtValue(const RtValue&);
  RtValue& operator=(const RtValue&);
  RtValue() : time(0), value(0) {
  }

  virtual ~RtValue() throw();
  int64_t time;
  double value;

  void __set_time(const int64_t val);

  void __set_value(const double val);

  bool operator == (const RtValue & rhs) const
  {
    if (!(time == rhs.time))
      return false;
    if (!(value == rhs.value))
      return false;
    return true;
  }
  bool operator != (const RtValue &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RtValue & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(RtValue &a, RtValue &b);

std::ostream& operator<<(std::ostream& out, const RtValue& obj);

typedef struct _RtSnapshotData__isset {
  _RtSnapshotData__isset() : state(false), data(false) {}
  bool state :1;
  bool data :1;
} _RtSnapshotData__isset;

class RtSnapshotData : public virtual ::apache::thrift::TBase {
 public:

  RtSnapshotData(const RtSnapshotData&);
  RtSnapshotData& operator=(const RtSnapshotData&);
  RtSnapshotData() : state((RtDataState::type)0) {
  }

  virtual ~RtSnapshotData() throw();
  RtDataState::type state;
  RtValue data;

  _RtSnapshotData__isset __isset;

  void __set_state(const RtDataState::type val);

  void __set_data(const RtValue& val);

  bool operator == (const RtSnapshotData & rhs) const
  {
    if (__isset.state != rhs.__isset.state)
      return false;
    else if (__isset.state && !(state == rhs.state))
      return false;
    if (__isset.data != rhs.__isset.data)
      return false;
    else if (__isset.data && !(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const RtSnapshotData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RtSnapshotData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(RtSnapshotData &a, RtSnapshotData &b);

std::ostream& operator<<(std::ostream& out, const RtSnapshotData& obj);

typedef struct _RtHistoryData__isset {
  _RtHistoryData__isset() : state(false), data(false) {}
  bool state :1;
  bool data :1;
} _RtHistoryData__isset;

class RtHistoryData : public virtual ::apache::thrift::TBase {
 public:

  RtHistoryData(const RtHistoryData&);
  RtHistoryData& operator=(const RtHistoryData&);
  RtHistoryData() : state((RtDataState::type)0) {
  }

  virtual ~RtHistoryData() throw();
  RtDataState::type state;
  std::vector<RtValue>  data;

  _RtHistoryData__isset __isset;

  void __set_state(const RtDataState::type val);

  void __set_data(const std::vector<RtValue> & val);

  bool operator == (const RtHistoryData & rhs) const
  {
    if (__isset.state != rhs.__isset.state)
      return false;
    else if (__isset.state && !(state == rhs.state))
      return false;
    if (__isset.data != rhs.__isset.data)
      return false;
    else if (__isset.data && !(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const RtHistoryData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RtHistoryData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(RtHistoryData &a, RtHistoryData &b);

std::ostream& operator<<(std::ostream& out, const RtHistoryData& obj);

typedef struct _RtSummaryValue__isset {
  _RtSummaryValue__isset() : maxVal(false), minVal(false), avgVal(false) {}
  bool maxVal :1;
  bool minVal :1;
  bool avgVal :1;
} _RtSummaryValue__isset;

class RtSummaryValue : public virtual ::apache::thrift::TBase {
 public:

  RtSummaryValue(const RtSummaryValue&);
  RtSummaryValue& operator=(const RtSummaryValue&);
  RtSummaryValue() : avgVal(0) {
  }

  virtual ~RtSummaryValue() throw();
  RtValue maxVal;
  RtValue minVal;
  double avgVal;

  _RtSummaryValue__isset __isset;

  void __set_maxVal(const RtValue& val);

  void __set_minVal(const RtValue& val);

  void __set_avgVal(const double val);

  bool operator == (const RtSummaryValue & rhs) const
  {
    if (__isset.maxVal != rhs.__isset.maxVal)
      return false;
    else if (__isset.maxVal && !(maxVal == rhs.maxVal))
      return false;
    if (__isset.minVal != rhs.__isset.minVal)
      return false;
    else if (__isset.minVal && !(minVal == rhs.minVal))
      return false;
    if (__isset.avgVal != rhs.__isset.avgVal)
      return false;
    else if (__isset.avgVal && !(avgVal == rhs.avgVal))
      return false;
    return true;
  }
  bool operator != (const RtSummaryValue &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RtSummaryValue & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(RtSummaryValue &a, RtSummaryValue &b);

std::ostream& operator<<(std::ostream& out, const RtSummaryValue& obj);

typedef struct _RtSummaryData__isset {
  _RtSummaryData__isset() : state(false), data(false) {}
  bool state :1;
  bool data :1;
} _RtSummaryData__isset;

class RtSummaryData : public virtual ::apache::thrift::TBase {
 public:

  RtSummaryData(const RtSummaryData&);
  RtSummaryData& operator=(const RtSummaryData&);
  RtSummaryData() : state((RtDataState::type)0) {
  }

  virtual ~RtSummaryData() throw();
  RtDataState::type state;
  std::vector<RtSummaryValue>  data;

  _RtSummaryData__isset __isset;

  void __set_state(const RtDataState::type val);

  void __set_data(const std::vector<RtSummaryValue> & val);

  bool operator == (const RtSummaryData & rhs) const
  {
    if (__isset.state != rhs.__isset.state)
      return false;
    else if (__isset.state && !(state == rhs.state))
      return false;
    if (__isset.data != rhs.__isset.data)
      return false;
    else if (__isset.data && !(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const RtSummaryData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RtSummaryData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(RtSummaryData &a, RtSummaryData &b);

std::ostream& operator<<(std::ostream& out, const RtSummaryData& obj);

}}}}}} // namespace

#endif
