#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <mutex>

#include "cppt/string.h"
#include "cppt/fs.h"

#define LL_DEFAULT_LOG_DIR "/var/log"
#define LL_DEFAULT_DATETIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define LL_DEFAULT_FILENAME_FORMAT "{dt}.application.log"
#define LL_DEFAULT_FILENAME_DATETIME_FORMAT "%Y-%m-%d_%H-%M-%S"

// #define LL_DECLARE_LOGGER_OP_SIMPLE(_type) TLogger &operator<<(_type value)

#define LL_COUT_SS_NUMFORMAT std::fixed << std::setprecision(2)

#define LL_WRITE(_what)                                                   \
    if(m_outToFile)    { m_logstream << LL_COUT_SS_NUMFORMAT << _what; } \
    if(m_outToConsole) {   std::cout << LL_COUT_SS_NUMFORMAT << _what; }

#define LL_STRINGSTREAM_STR(_what) ((std::ostringstream&)(std::ostringstream("") << LL_COUT_SS_NUMFORMAT << _what)).str()

namespace ll
{

template<typename TLogger>
class CLogger
{
public:
  friend TLogger;
  CLogger(const bool        &prefixLineWithDateTime = true,
          const std::string &path                   = LL_DEFAULT_LOG_DIR,
          const std::string &filenameFormat         = LL_DEFAULT_FILENAME_FORMAT,
          const std::string &filenameDatetimeFormat = LL_DEFAULT_FILENAME_DATETIME_FORMAT,
          const bool        &outToFile              = true,
          const bool        &outToConsole           = true)
    : m_prefixLineWithDateTime(prefixLineWithDateTime),
      m_outToFile(outToFile),
      m_outToConsole(outToConsole),
      m_filename("")
  {
    if(outToFile)
    {
      std::string filename = filenameFormat;
      if(!cppt::fs::file_exists(path))
      {
        cppt::fs::create_path(path);
      }
      if(!filenameDatetimeFormat.empty() && cppt::string::contains(filenameFormat, "{dt}"))
      {
        filename = cppt::string::replace_all(filename, "{dt}", cppt::string::formatted_current_datetime(filenameDatetimeFormat));
      }
      m_filename = path + "/" + filename;
    }
    start() << "Opening log"; stop();
  }

  virtual ~CLogger()
  {
    start() << "Closing log"; stop();
  }

  TLogger &start()
  {
    m_mutex.lock();
    #ifdef LL_DEBUG
    if(m_outToFile && m_logstream.is_open())
    {
      write("---------------------------[You forgot close logstream on finish]---------------------------");
      stop();
    }
    #endif
    if(m_outToFile)
    {
      m_logstream.open(m_filename, std::ofstream::out | std::ofstream::ate | std::ofstream::app);
    }
    std::string time = cppt::string::formatted_current_datetime("[" LL_DEFAULT_DATETIME_FORMAT "] ");
    #ifdef LL_DEBUG
    write(LL_STRINGSTREAM_STR(time << "{" << std::this_thread::get_id() << "} "));
    #else
    write(time);
    #endif
    return static_cast<TLogger &>(*this);
  }

  void stop()
  {
    LL_WRITE(std::endl);
    //m_logstream->flush();
    if(m_outToFile)
    {
      m_logstream.close();
    }
    m_mutex.unlock();
  }

  template <class TValue> friend TLogger &operator<<(TLogger &logger, const TValue &value)
  {
    logger.write(value);
    return logger;
  }

  friend TLogger &operator<<(TLogger &logger, const bool &value)
  {
    logger.write(value ? "true" : "false");
    return logger;
  }


  // template <class TValue> TLogger &operator<<(const TValue &value)
  // {
  //   write(value);
  //   return static_cast<TLogger &>(*this);
  // }

  const std::string &filename() const
  {
    return m_filename;
  }

protected:
  bool          m_outToFile;
  bool          m_outToConsole;
  std::ofstream m_logstream;
  template<typename TValue> void write(const TValue &value)
  {
    LL_WRITE(value);
  }

private:
  bool          m_prefixLineWithDateTime;
  std::string   m_filename;
  std::mutex    m_mutex;
};

}
