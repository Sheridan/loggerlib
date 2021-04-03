#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <mutex>

#define LL_DEFAULT_LOG_DIR "/var/log"
#define LL_DEFAULT_DATETIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define LL_DEFAULT_FILENAME_FORMAT "{dt}.application.log"
#define LL_DEFAULT_FILENAME_DATETIME_FORMAT "%Y-%m-%d_%H-%M-%S"

namespace ll
{

#define LL_DECLARE_LOGGER_OP_SIMPLE(_type) CLogger &operator<<(_type value)

class CLogger
{
public:
  CLogger(const bool        &prefixLineWithDateTime = true,
          const std::string &path                   = LL_DEFAULT_LOG_DIR,
          const std::string &filenameFormat         = LL_DEFAULT_FILENAME_FORMAT,
          const std::string &filenameDatetimeFormat = LL_DEFAULT_FILENAME_DATETIME_FORMAT,
          const bool        &outToFile              = true,
          const bool        &outToConsole           = true);
  ~CLogger();

  CLogger &start();
  void      stop();
  template <class T> CLogger &operator<<(const T &value)
  {
    if(m_outToFile)
    {
      m_logstream << value;
    }
    if(m_outToConsole)
    {
      std::cout << value;
    }
    return *this;
  }

  const std::string &filename() const;

  LL_DECLARE_LOGGER_OP_SIMPLE(const bool &);

private:
  bool          m_prefixLineWithDateTime;
  bool          m_outToFile;
  bool          m_outToConsole;
  std::string   m_filename;
  std::ofstream m_logstream;
  std::mutex    m_mutex;
  void write(const std::stringstream &value);
};

}
