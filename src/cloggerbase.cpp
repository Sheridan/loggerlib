#include "cloggerbase.h"
#include <cppt/string.h>
#include <cppt/fs.h>
#include <thread>

namespace ll
{
CLoggerBase::CLoggerBase(const bool                    &prefixLineWithDateTime,
                         const std::string             &path,
                         const std::string             &filenameFormat,
                         const std::string             &filenameDatetimeFormat,
                         const std::string             &datetimeFormat,
                         const bool                    &outToFile,
                         const bool                    &outToConsole,
                         const CLogPriority::TPriority &maxPriority)
  : m_prefixLineWithDateTime(prefixLineWithDateTime),
    m_datetimeFormat(datetimeFormat),
    m_outToFile(outToFile),
    m_outToConsole(outToConsole),
    m_filename(""),
    m_path(path),
    m_filenameFormat(filenameFormat),
    m_filenameDatetimeFormat(filenameDatetimeFormat),
    m_maxPriority(maxPriority)
{
  updateFilePath();
}

CLoggerBase::~CLoggerBase()
{
  stop();
}

void CLoggerBase::start(const CLogPriority &priority)
{
  m_mutex.lock();
  m_priority = &priority;
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
  std::string time = cppt::string::formatted_current_datetime(m_datetimeFormat);
  #ifdef LL_DEBUG
  write(CLogString(m_precision) << time << " " << m_priority->caption() << " " << "{thread id: " << std::this_thread::get_id() << "} | ");
  #else
  write(CLogString(m_precision) << time << " " << m_priority->caption() << " | ");
  #endif
}

void CLoggerBase::stop()
{
  if(m_outToFile && m_logstream.is_open())
  {
    m_logstream.flush();
    m_logstream.close();
  }
  m_mutex.unlock();
}

void CLoggerBase::updateFilePath()
{
  if(m_outToFile)
  {
    std::string filename = m_filenameFormat;
    if(!cppt::fs::file_exists(m_path))
    {
      cppt::fs::create_path(m_path);
    }
    if(!m_filenameDatetimeFormat.empty() && cppt::string::contains(m_filenameFormat, "{dt}"))
    {
      filename = cppt::string::replace_all(filename, "{dt}", cppt::string::formatted_current_datetime(m_filenameDatetimeFormat));
    }
    m_filename = m_path + "/" + filename;
  }
}

void CLoggerBase::write(const EControl &value)
{
  switch(value)
  {
    case EControl::endl:
    {
      LL_WRITE_PRIORITIZED(std::endl);
      stop();
    } break;
    case EControl::currentPriorityCaption:
    {
      LL_WRITE_PRIORITIZED(m_priority->caption())
    } break;
    case EControl::currentPriorityName:
    {
      LL_WRITE_PRIORITIZED(m_priority->name())
    } break;
  }
}

void CLoggerBase::write(const CLogString &value)
{
  LL_WRITE_PRIORITIZED(value.str());
}


void CLoggerBase::setPrecision(const unsigned short &precision)
{
  m_precision = precision;
}

const unsigned short &CLoggerBase::precision() const
{
  return m_precision;
}

void CLoggerBase::setPrefixLineWithDateTime(const bool &prefixLineWithDateTime)
{
  m_prefixLineWithDateTime = prefixLineWithDateTime;
}

void CLoggerBase::setMaxPriority(const CLogPriority::TPriority &priority)
{
  m_maxPriority = priority;
}

const bool &CLoggerBase::prefixLineWithDateTime() const
{
  return m_prefixLineWithDateTime;
}

const CLogPriority::TPriority &CLoggerBase::maxPriority() const
{
  return m_maxPriority;
}

void CLoggerBase::setPath(const std::string &path)
{
  m_path = path;
  updateFilePath();
}

const std::string &CLoggerBase::path() const
{
  return m_path;
}

void CLoggerBase::setFilenameFormat(const std::string &filenameFormat)
{
  m_filename = filenameFormat;
  updateFilePath();
}

const std::string &CLoggerBase::filenameFormat() const
{
  return m_filenameFormat;
}

void CLoggerBase::setFilenameDatetimeFormat(const std::string &filenameDatetimeFormat)
{
  m_filenameDatetimeFormat = filenameDatetimeFormat;
  updateFilePath();
}

const std::string &CLoggerBase::filenameDatetimeFormat() const
{
  return m_filenameDatetimeFormat;
}

void CLoggerBase::setDatetimeFormat(const std::string &datetimeFormat)
{
  m_datetimeFormat = datetimeFormat;
}

const std::string &CLoggerBase::datetimeFormat() const
{
  return m_datetimeFormat;
}

void CLoggerBase::setOutToFile(const bool &outToFile)
{
  m_outToFile = outToFile;
  updateFilePath();
}

const bool &CLoggerBase::outToFile() const
{
  return m_outToFile;
}

void CLoggerBase::setOutToConsole(const bool &outToConsole)
{
  m_outToConsole = outToConsole;
}

const bool &CLoggerBase::outToConsole() const
{
  return m_outToConsole;
}

}
