#ifdef REGEX_USE_BOOST
#include <boost/regex.hpp>
namespace regexns = boost;
#else
#include <regex>
namespace regexns = std;
#endif
