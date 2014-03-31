
#ifdef FILESYSTEM_USE_BOOST
#include <boost/filesystem.hpp>
namespace filesystem = boost::filesystem;
#else
#include <filesystem>
namespace filesystem = std::tr2::sys;
#endif
