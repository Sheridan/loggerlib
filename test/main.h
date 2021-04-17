#pragma once

#include <loggerlib/loggerlib.h>

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
    logger.write(ll::CLogString() << "(" << value.a << "," << value.b << ")");
    return logger;
  }
};

}

ll_test::CLogger *logger;

#define LL_TYPE_LOG_TEST(_type, _value) \
    logger->log(ll::priority::info) << #_type " testing. Must out `" #_value "`" << ll::endl; \
    { \
      _type t = _value; \
      logger->log(ll::priority::info) << "Out: " << t << ll::endl; \
    }

constexpr ll::CLogPriority mypriority("MYP", "My Priority", 5, false);

int main(void);
