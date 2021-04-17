#include "clogstring.h"
#include <iomanip>

namespace ll
{

CLogString::CLogString(const unsigned short &precision)
  : m_precision(precision)
{
  m_stream << std::fixed << std::setprecision(m_precision);
}

CLogString::~CLogString()
{}

}
