#include <string>

class FileSystem {
public:

    static bool exists(const std::string& path);
    static bool createDirectory(const std::string& path);
    static bool copyFile(const std::string& from, const std::string& to);
    
    /**
     * Returns the writable user config directory.
     * Ensures that it exists
     */
    static std::string userConfigDir();

};