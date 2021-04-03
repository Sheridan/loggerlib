# loggerlib
Simple C++ logger library is designed to easily integrate logging capabilities into your application.

# Examlpe
Implement some defines
```c++
#include <loggerlib.h>
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
ll::CLogger *logger = new ll::CLogger();
int i = 1;
std::string std_string = "std::string";
const char * cc_string = "const char * string";

LL_LOG_DBG("Debug" << i << 123);
LL_LOG_NFO("Information" << i << std_string);
LL_LOG_WRN("Warning" << std_string << cc_string);
LL_LOG_ERR("Error" << std_string << i << cc_string);
delete logger;
```
