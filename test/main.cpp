#include "main.h"

int main(void)
{
  logger = new ll_test::CLogger();

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

  logger->log(ll::priority::info) << "--------------------- Custom priority test ---------------------" << ll::endl;
  logger->log(mypriority)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;

  logger->log(ll::priority::info) << "--------------------- Max priority test ---------------------" << ll::endl;

  logger->log(mypriority)             << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::debug)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::info)     << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::warning)  << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::error)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::critical) << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;

  logger->log(ll::priority::info) << "Set max priority as " << ll::priority::warning.name() << ll::endl;
  logger->setMaxPriority(ll::priority::warning.priority());

  logger->log(mypriority)             << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::debug)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::info)     << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::warning)  << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::error)    << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;
  logger->log(ll::priority::critical) << ll::currentPriorityName << " (" << ll::currentPriorityCaption << ")" << ll::endl;

  delete logger;
}
