#include <string>

class FileSystem {
public:

    static bool exists(const std::string& path);
    static bool copyFile(const std::string& from, const std::string& to);
    static bool createDirectory(const std::string& path);
    
    static bool removeFile(const std::string& path);
    static bool removeDirectory(const std::string& path);

    /**
     * Returns the writable user config directory.
     * Ensures that it exists.
     */
    static std::string userConfigDir();

};