#include "lltest.h"

int main(void)
{
  logger = new ll::CLogger();

  LL_TYPE_LOG_TEST(int          , 1);
  LL_TYPE_LOG_TEST(unsigned int , 2);
  LL_TYPE_LOG_TEST(short int    , 3);
  LL_TYPE_LOG_TEST(long long int, 4);

  LL_TYPE_LOG_TEST(float , 1.23);
  LL_TYPE_LOG_TEST(double, 4.567);

  LL_TYPE_LOG_TEST(const char *, "abcd");
  LL_TYPE_LOG_TEST(std::string , "abcd");

  LL_LOG_DBG("Debug");
  LL_LOG_NFO("Information");
  LL_LOG_WRN("Warning");
  LL_LOG_ERR("Error");
  try
  {
    LL_LOG_CRY("Crytical");
  }
  catch(const std::exception& e)
  {
    LL_LOG_NFO("Catched crytical: " << e.what());
  }

  delete logger;
}
