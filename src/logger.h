#include <string>

class Logger {
    public:
        static Logger& getInstance();
        void initialize(const std::string& logFilePath);
        void log(const std::string& message);
        void saveToFile();
}