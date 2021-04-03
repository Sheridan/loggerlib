#include "clogger.h"
#include "cppt/string.h"
#include "cppt/fs.h"

#include <iomanip>
#include <thread>


namespace ll
{

CLogger::CLogger(const bool        &prefixLineWithDateTime,
                 const std::string &path,
                 const std::string &filenameFormat,
                 const std::string &filenameDatetimeFormat,
                 const bool        &outToFile,
                 const bool        &outToConsole)
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

CLogger::~CLogger()
{
  start() << "Closing log"; stop();
}


#define LL_COUT(_what)                           \
    if(m_outToFile)    { m_logstream << _what; } \
    if(m_outToConsole) {   std::cout << _what; }

#define LL_COUT_SS(_what) \
    std::stringstream ss; \
    ss << _what;          \
    write(ss);

#define LL_COUT_RET(_what)       LL_COUT(_what); return *this;
#define LL_COUT_SS_RET(_what) LL_COUT_SS(_what); return *this;
#define LL_COUT_SS_NUMFORMAT std::fixed << std::setprecision(2)

CLogger &CLogger::start()
{
  m_mutex.lock();
  #ifdef LL_DEBUG
  if(m_outToFile && m_logstream.is_open())
  {
    LL_COUT("---------------------------[You forgot close logstream on finish]---------------------------");
    stop();
  }
  #endif
  if(m_outToFile)
  {
    m_logstream.open(m_filename, std::ofstream::out | std::ofstream::ate | std::ofstream::app);
  }
  std::string time = cppt::string::formatted_current_datetime("[" LL_DEFAULT_DATETIME_FORMAT  "] ");
  #ifdef LL_DEBUG
  LL_COUT_RET(time << "{" << std::this_thread::get_id() << "} ");
  #else
  LL_COUT_RET(time);
  #endif
}

void CLogger::stop()
{
  LL_COUT(std::endl);
  //m_logstream->flush();
  if(m_outToFile)
  {
    m_logstream.close();
  }
  m_mutex.unlock();
}

void CLogger::write(const std::stringstream &value)
{
  LL_COUT(value.str());
}


#define LL_FUNC_LOGGER_OP_SIMPLE(_type) CLogger &CLogger::operator<<(_type value)

LL_FUNC_LOGGER_OP_SIMPLE(const bool &)
{
  std::string sBool = std::string(value ? "true" : "false");
  LL_COUT_RET(sBool);
}

}
