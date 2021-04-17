#pragma once

#include <sstream>
#include <string>

namespace ll
{

class CLogString
{
public:
  CLogString(const unsigned short &precision = 2);
  virtual ~CLogString();

  template <typename T> inline CLogString &operator<<(const T &value)
  {
    m_stream << value;
    return *this;
  }

  const std::string str() const
  {
    return m_stream.str();
  }

  inline operator std::string() const
  {
    return str();
  }

private:
  std::ostringstream m_stream;
  unsigned short m_precision;
};

}
