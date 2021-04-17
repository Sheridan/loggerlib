#pragma once

#include <limits>
#include <string>
#include "cloggerbase.h"

#define LL_DEFAULT_LOG_DIR "/var/log"
#define LL_DEFAULT_DATETIME_FORMAT "%Y-%m-%d %H:%M:%S"
#define LL_DEFAULT_FILENAME_FORMAT "{dt}.application.log"
#define LL_DEFAULT_FILENAME_DATETIME_FORMAT "%Y-%m-%d_%H-%M-%S"

namespace ll
{

template<typename TLogger>
class CLogger : public CLoggerBase
{
public:
  friend TLogger;
  CLogger(const bool                    &prefixLineWithDateTime = true,
          const std::string             &path                   = LL_DEFAULT_LOG_DIR,
          const std::string             &filenameFormat         = LL_DEFAULT_FILENAME_FORMAT,
          const std::string             &filenameDatetimeFormat = LL_DEFAULT_FILENAME_DATETIME_FORMAT,
          const std::string             &datetimeFormat         = LL_DEFAULT_DATETIME_FORMAT,
          const bool                    &outToFile              = true,
          const bool                    &outToConsole           = true,
          const CLogPriority::TPriority &maxPriority            = std::numeric_limits<CLogPriority::TPriority>::max())
    : CLoggerBase(prefixLineWithDateTime,
                  path,
                  filenameFormat,
                  filenameDatetimeFormat,
                  datetimeFormat,
                  outToFile,
                  outToConsole,
                  maxPriority)
  {
    #ifdef LL_DEBUG
    log(ll::priority::debug) << "Opening log" << ll::endl;
    #endif
  }

  virtual ~CLogger()
  {
    #ifdef LL_DEBUG
    log(ll::priority::debug) << "Closing log" << ll::endl;
    #endif
  }

  TLogger &log(const CLogPriority &priority = ll::priority::info)
  {
    start(priority);
    return static_cast<TLogger &>(*this);
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

  friend TLogger &operator<<(TLogger &logger, const EControl &value)
  {
    logger.write(value);
    return logger;
  }

  template <class TValue> TLogger &operator<<(const TValue &value)
  {
    write(value);
    return static_cast<TLogger &>(*this);
  }

  const std::string &filename() const
  {
    return m_filename;
  }

};

}
