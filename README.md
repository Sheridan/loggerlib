# loggerlib
Simple C++ logger library is designed to easily integrate logging capabilities into your application.

# Examlpe
Implement some defines
```c++
#include <loggerlib.h>
namespase ns
{
    class CLogger : public ll::CLogger<ns::CLogger> {};
}
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
```
and using
```c++
ns::CLogger *logger = new ns::CLogger();
int i = 1;
std::string std_string = "std::string";
const char * cc_string = "const char * string";

LL_LOG_DBG("Debug " << i << " | " << 123);
LL_LOG_NFO("Information " << i << " | " << std_string);
LL_LOG_WRN("Warning " << std_string << " | " << cc_string);
LL_LOG_ERR("Error " << std_string << " | " << i << " | " << cc_string);

try
{
    LL_LOG_CRY("Crytical");
}
catch(const std::exception &e)
{
    LL_LOG_NFO("Catched crytical: " << e.what());
}
delete logger;
```

# Extending
```c++
namespace ns
{

struct STest
{
  int a;
  float b;
  STest(const int &_a, const float &_b) : a(_a), b(_b) {}
};

class CLogger : public ll::CLogger<ns::CLogger>
{
public:
  friend CLogger &operator<<(CLogger &logger, const STest &value)
  {
    logger.write(LL_STRINGSTREAM_STR("(" << value.a << "," << value.b << ")"));
    return logger;
  }
};

...

LL_LOG_NFO("Custom test" << ns::STest(1, 2) << ns::STest(4, 5));

}
```

# Output
```
[2021-04-04 23:05:20] {1} Opening log
[2021-04-04 23:05:20] {1} [Debg] Debug 1 | 123
[2021-04-04 23:05:20] {1} [Info] Information 1 | std::string
[2021-04-04 23:05:20] {1} [Warn] Warning std::string | const char * string
[2021-04-04 23:05:20] {1} [Errr] Error std::string | 1 | const char * string
[2021-04-04 23:05:20] {1} [Errr] Crytical
[2021-04-04 23:05:20] {1} [Info] Catched crytical: Crytical
[2021-04-04 23:05:20] {1} [Info] Custom test(1,2.00)(4,5.00)
[2021-04-04 23:05:20] {1} Closing log
```

# Dependencies
[cpptoolslib](https://github.com/Sheridan/cpptoolslib)
