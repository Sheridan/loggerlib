# loggerlib
Simple C++ logger library is designed to easily integrate logging capabilities into your application.

# Examlpe
```c++
  int i = 1;
  std::string std_string = "std::string";
  const char *cc_string = "const char * string";

  logger->log(ll::priority::debug)   << ll::currentPriorityName << " " << i << " | " << 123 << ll::endl;
  logger->log(ll::priority::info)    << ll::currentPriorityName << " " << i << " | " << std_string << ll::endl;
  logger->log(ll::priority::warning) << ll::currentPriorityName << " " << std_string << " | " << cc_string << ll::endl;
  logger->log(ll::priority::error)   << ll::currentPriorityName << " " << std_string << " | " << i << " | " << cc_string << ll::endl;

  LL_TYPE_LOG_TEST(int, 1);
  LL_TYPE_LOG_TEST(unsigned int, 2);
  LL_TYPE_LOG_TEST(short int, 3);
  LL_TYPE_LOG_TEST(long long int, 4);

  LL_TYPE_LOG_TEST(float, 1.23);
  LL_TYPE_LOG_TEST(double,  4.567);

  LL_TYPE_LOG_TEST(const char *, "abcd");
  LL_TYPE_LOG_TEST(std::string, "abcd");

  logger->log(ll::priority::info) << "Custom test: " << ll_test::STest(1, 2) << " - " << ll_test::STest(4, 5) << ll::endl;

  logger->log(ll::priority::info) << "--------------------- Max priority test ---------------------" << ll::endl;

  logger->log(ll::priority::debug)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::info)     << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::warning)  << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::error)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::critical) << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;

  logger->log(ll::priority::info) << "Set max priority as " << ll::priority::warning.name() << ll::endl;
  logger->setMaxPriority(ll::priority::warning.priority());

  logger->log(ll::priority::debug)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::info)     << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::warning)  << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::error)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::critical) << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
```

# Extending
## Types
```c++
namespace ns
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

...

logger->log(ll::priority::info) << "Custom test: " << ll_test::STest(1, 2) << " - " << ll_test::STest(4, 5) << ll::endl;

}
```

## Priority
```c++
constexpr ll::CLogPriority mypriority("MYP", "My Priority", 5, false);
...
logger->log(mypriority) << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
```
# Output
```
2021-04-18 00:14:09 DBG | Debug 1 | 123
2021-04-18 00:14:09 NFO | Info 1 | std::string
2021-04-18 00:14:09 WRN | Warning std::string | const char * string
2021-04-18 00:14:09 ERR | Error std::string | 1 | const char * string
2021-04-18 00:14:09 NFO | int testing. Must out `1`
2021-04-18 00:14:09 NFO | Out: 1
2021-04-18 00:14:09 NFO | unsigned int testing. Must out `2`
2021-04-18 00:14:09 NFO | Out: 2
2021-04-18 00:14:09 NFO | short int testing. Must out `3`
2021-04-18 00:14:09 NFO | Out: 3
2021-04-18 00:14:09 NFO | long long int testing. Must out `4`
2021-04-18 00:14:09 NFO | Out: 4
2021-04-18 00:14:09 NFO | float testing. Must out `1.23`
2021-04-18 00:14:09 NFO | Out: 1
2021-04-18 00:14:09 NFO | double testing. Must out `4.567`
2021-04-18 00:14:09 NFO | Out: 5
2021-04-18 00:14:09 NFO | const char * testing. Must out `"abcd"`
2021-04-18 00:14:09 NFO | Out: abcd
2021-04-18 00:14:09 NFO | std::string testing. Must out `"abcd"`
2021-04-18 00:14:09 NFO | Out: abcd
2021-04-18 00:14:09 NFO | Custom test: (1,2.00) - (4,5.00)
2021-04-18 00:14:09 NFO | --------------------- Custom priority test ---------------------
2021-04-18 00:14:09 MYP | My Priority (MYP)
2021-04-18 00:14:09 NFO | --------------------- Max priority test ---------------------
2021-04-18 00:14:09 MYP | My Priority (MYP)
2021-04-18 00:14:09 DBG | Debug (DBG)
2021-04-18 00:14:09 NFO | Info (NFO)
2021-04-18 00:14:09 WRN | Warning (WRN)
2021-04-18 00:14:09 ERR | Error (ERR)
2021-04-18 00:14:09 CRI | Critical (CRI)
2021-04-18 00:14:09 NFO | Set max priority as Warning
2021-04-18 00:14:09 WRN | Warning (WRN)
2021-04-18 00:14:09 ERR | Error (ERR)
2021-04-18 00:14:09 CRI | Critical (CRI)
```

# Dependencies
[cpptoolslib](https://github.com/Sheridan/cpptoolslib)
