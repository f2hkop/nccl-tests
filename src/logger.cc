#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>
#include "logger.h"

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void initialize(const std::string& logFilePath) {
        this->logFilePath = logFilePath;
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        logMessages.push_back(message);
    }

    void saveToFile() {
        std::lock_guard<std::mutex> lock(logMutex);
        std::ofstream logFile(logFilePath, std::ios::out | std::ios::app);
        if (logFile.is_open()) {
            for (const auto& message : logMessages) {
                logFile << message << std::endl;
            }
            logFile.close();
        } else {
            std::cerr << "Failed to open log file: " << logFilePath << std::endl;
        }
        logMessages.clear();
    }

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string logFilePath;
    std::vector<std::string> logMessages;
    std::mutex logMutex;
};