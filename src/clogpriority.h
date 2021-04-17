#pragma once

namespace ll
{

class CLogPriority
{
public:
  using TPriority = unsigned short;
  constexpr CLogPriority(const char      *caption,
                         const char      *name,
                         const TPriority &priority,
                         const bool      &isError)
    : m_caption(caption),
      m_name(name),
      m_priority(priority),
      m_isError(isError) {}

  const char *caption() const
  {
    return m_caption ;
  }
  const char *name() const
  {
    return m_name ;
  }
  const unsigned short &priority() const
  {
    return m_priority;
  }
  const bool &isError() const
  {
    return m_isError ;
  }

private:
  const char      *m_caption;
  const char      *m_name;
  const TPriority  m_priority;
  const bool       m_isError;
};

namespace priority
{
constexpr CLogPriority critical("CRI", "Critical", 0, true);
constexpr CLogPriority error ("ERR", "Error", 1, true);
constexpr CLogPriority warning("WRN", "Warning", 2, true);
constexpr CLogPriority info("NFO", "Info", 3, false);
constexpr CLogPriority debug("DBG", "Debug", 4, false);
}

}
