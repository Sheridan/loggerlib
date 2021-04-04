#pragma once

#include "clogger.h"

namespace ll_test
{

struct STest
{
  int a;
  float b;
  STest(const int &_a, const float &_b) : a(_a), b(_b) {}
};

class CLogger : public ll::CLogger<ll_test::CLogger>
{
public:
  friend CLogger &operator<<(CLogger &logger, const STest &value)
  {
    logger.write(LL_STRINGSTREAM_STR("(" << value.a << "," << value.b << ")"));
    return logger;
  }
};

}

ll_test::CLogger *logger;

#define LL_LOG_START(_what) logger->start() << _what;
#define LL_LOG_STOP         logger->stop();
#define LL_LOG(_what) do { LL_LOG_START(_what); LL_LOG_STOP; } while(false)
#define LL_LOG_LINE(_caption) std::string(std::string(_caption " in file " __FILE__ " at line " LL_STR(__LINE__) " in method ") + std::string(__func__))
#ifdef LL_DEBUG
  #define LL_LOG_DBG(_what) { LL_LOG("[Debg] " << _what); }
#else  // LL_DEBUG
  #define LL_LOG_DBG(_what)
#endif // LL_DEBUG
#define LL_LOG_NFO(_what) { LL_LOG("[Info] " << _what); }
#define LL_LOG_WRN(_what) { LL_LOG("[Warn] " << _what); }
#define LL_LOG_ERR(_what) { LL_LOG("[Errr] " << _what); }
#define LL_LOG_CRY(_what) { LL_LOG("[Errr] " << _what); throw std::runtime_error(_what); }

#define LL_TYPE_LOG_TEST(_type, _value) \
    LL_LOG_NFO(#_type " testing. Must out `" #_value "`") \
    { \
      _type t = _value; \
      LL_LOG_NFO("Out: " << t); \
    }

int main(void);
