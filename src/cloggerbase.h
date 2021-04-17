#pragma once
#include <string>
#include <mutex>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "clogstring.h"
#include "clogpriority.h"

#define LL_WRITE(_what) \
    if(m_outToFile)    { m_logstream << _what; } \
    if(m_outToConsole) { if(m_priority->isError()) { std::cerr << _what; } else { std::cout << _what; } }
#define LL_WRITE_PRIORITIZED(_what) if(m_priority->priority() <= m_maxPriority) { LL_WRITE(_what) }


namespace ll
{

enum EControl
{
  endl,
  currentPriorityCaption,
  currentPriorityName
};

class CLoggerBase
{
public:
  CLoggerBase(const bool                    &prefixLineWithDateTime,
              const std::string             &path,
              const std::string             &filenameFormat,
              const std::string             &filenameDatetimeFormat,
              const std::string             &datetimeFormat,
              const bool                    &outToFile,
              const bool                    &outToConsole,
              const CLogPriority::TPriority &maxPriority);
  virtual ~CLoggerBase();


  const unsigned short          &precision() const;
  const std::string             &path() const;
  const std::string             &filenameFormat() const;
  const std::string             &filenameDatetimeFormat() const;
  const std::string             &datetimeFormat() const;
  const bool                    &outToFile() const;
  const bool                    &outToConsole() const;
  const bool                    &prefixLineWithDateTime() const;
  const CLogPriority::TPriority &maxPriority() const;

  void setPrecision(const unsigned short &precision);
  void setPath(const std::string &path);
  void setFilenameFormat(const std::string &filenameFormat);
  void setFilenameDatetimeFormat(const std::string &filenameDatetimeFormat);
  void setDatetimeFormat(const std::string &datetimeFormat);
  void setOutToFile(const bool &outToFile);
  void setOutToConsole(const bool &outToConsole);
  void setPrefixLineWithDateTime(const bool &prefixLineWithDateTime);
  void setMaxPriority(const CLogPriority::TPriority &priority);


protected:
  std::ofstream m_logstream;

  void start(const CLogPriority &priority);
  void write(const EControl &value);
  void write(const CLogString &value);
  template<typename TValue> void write(const TValue &value)
  {
    LL_WRITE_PRIORITIZED(std::fixed << std::setprecision(m_precision) << value);
  }

private:
  void stop();
  void updateFilePath();

  unsigned short           m_precision;
  bool                     m_outToFile;
  bool                     m_outToConsole;
  bool                     m_prefixLineWithDateTime;
  std::string              m_filenameDatetimeFormat;
  std::string              m_filenameFormat;
  std::string              m_datetimeFormat;
  std::string              m_filename;
  std::string              m_path;
  std::mutex               m_mutex;
  const CLogPriority      *m_priority;
  CLogPriority::TPriority  m_maxPriority;
};

}
