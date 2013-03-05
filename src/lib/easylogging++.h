///////////////////////////////////////////////////////////////////////////
//                                                                       //
// easylogging++.h - Core of EasyLogging++                               //
//                                                                       //
//   EasyLogging++ v6.10                                                 //
//   Cross platform logging made easy for C++ applications               //
//   Author Majid Khan <mkhan3189@gmail.com>                             //
//   http://www.icplusplus.com                                           //
//   https://github.com/mkhan3189/EasyLoggingPP                          //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, version 3 of the Licence.               //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H

// _LOGGING_ENABLED specifies whether or not writing logs are enabled.
// If this is set to 0, nothing will be logged. On the contrary, 1 means
// logs are enabled.
#define _LOGGING_ENABLED 1

// Following configurations are for each logging level, each with three
// parts; note: *** refers to log level in each of the following description.
//
// PART 1
// ======
// _ENABLE_***_LOGS specifies whether or not *** logs are enabled.
// This is similar to _LOGGING_ENABLED except the level effected is
// specific to config name only. 1 = enabled; 0 = disabled
//
// PART 2
// ======
// _***_LOGS_TO_STANDARD_OUTPUT specifies whether or not *** logs are enabled
// to be written to standard output. Standard output varies from OS to OS,
// typically it is terminal for linux and command prompt for windows.
// This will only effect corresponding log level.
//
// PART 3
// ======
// _***_LOGS_TO_FILE specifies whether or not *** logs are to be written to
// file. It is recommended to be always 1 i.e, enabled. If you wish some logs
// not be recorded to log file then you proabably want to disable those logs

#define _ENABLE_DEBUG_LOGS 0
#define _DEBUG_LOGS_TO_STANDARD_OUTPUT 1
#define _DEBUG_LOGS_TO_FILE 1

#define _ENABLE_INFO_LOGS 0
#define _INFO_LOGS_TO_STANDARD_OUTPUT 1
#define _INFO_LOGS_TO_FILE 1

#define _ENABLE_WARNING_LOGS 1
#define _WARNING_LOGS_TO_STANDARD_OUTPUT 1
#define _WARNING_LOGS_TO_FILE 1

#define _ENABLE_ERROR_LOGS 1
#define _ERROR_LOGS_TO_STANDARD_OUTPUT 1
#define _ERROR_LOGS_TO_FILE 1

#define _ENABLE_FATAL_LOGS 1
#define _FATAL_LOGS_TO_STANDARD_OUTPUT 1
#define _FATAL_LOGS_TO_FILE 1

#define _ENABLE_PERFORMANCE_LOGS 1
#define _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT 1
#define _PERFORMANCE_LOGS_TO_FILE 1

#define _ENABLE_VERBOSE_LOGS 1
#define _VERBOSE_LOGS_TO_STANDARD_OUTPUT 1
#define _VERBOSE_LOGS_TO_FILE 1

#define _ENABLE_QA_LOGS 1
#define _QA_LOGS_TO_STANDARD_OUTPUT 1
#define _QA_LOGS_TO_FILE 1

// Determine whether or not logging is enabled
// Use power of preprocessor directives to determine what to compile
// and what to ignore.
// If you are using g++ and wish to find out how does your program look like
// under the hood, use -E flag of g++ compiler that will expand all the macros
#if ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))

//
// OS evaluation
//
// Windows
#if defined(_WIN32)
#   define _WINDOWS 1
#   define _WINDOWS_32 1
#endif // defined(_WIN32)
#if defined(_WIN64)
#   define _WINDOWS 1
#   define _WINDOWS_64 1
#endif // defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
#   define _LINUX 1
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
#   define _MAC 1
#endif // defined(__APPLE__)

//
// Compiler evaluation
//
// GNU
#if defined(__GNUC__)
#   if defined(__GXX_EXPERIMENTAL_CXX0X__)
#       define _CXX0X 1
#   endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// VC++ (http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx)
#if defined(_MSC_VER)
#   if (_MSC_VER == 1600)
#       define _CXX0X 1
#   elif (_MSC_VER == 1700)
#       define _CXX11 1
#   endif // (_MSC_VER == 1600)
#endif // defined(_MSC_VER)

#define __ENABLE_MUTEX_EVALUATION (((_CXX0X || _CXX11)       ||     \
                                    (defined(QT_CORE_LIB)))   &&    \
                                    (!(defined(_DISABLE_MUTEX))))
//
// Mutex header evaluation
//
#if (__ENABLE_MUTEX_EVALUATION)
#   if (defined(QT_CORE_LIB))
        // Use Qt library QMutex to handle multi-threading application
#       define MUTEX_HEADER <QMutex>
#       define MUTEX_TYPE QMutex
#       define _MUTEX_SPECIFIC_INIT MUTEX_TYPE mutex;
#       define _LOCK_MUTEX easyloggingpp::internal::mutex.lock();
#       define _UNLOCK_MUTEX easyloggingpp::internal::mutex.unlock();
#       define _USING_MUTEX 1
#   else
        // Use std::mutex
        // We need to be careful here and add few extra checks to make sure we have mutex header available.
        // I think we should do a comparison of C++ standards and make a list of supported pre-processors (macros)
        // for mutex headers for different compilers.
#       define MUTEX_HEADER <mutex>
#       define MUTEX_TYPE std::mutex
#       define _MUTEX_SPECIFIC_INIT MUTEX_TYPE mutex;
#       define _LOCK_MUTEX easyloggingpp::internal::mutex.lock();
#       define _UNLOCK_MUTEX easyloggingpp::internal::mutex.unlock();
#       define _USING_MUTEX 1
#   endif // (defined(QT_CORE_LIB)
#else
#   define _MUTEX_SPECIFIC_INIT
#   define _LOCK_MUTEX
#   define _UNLOCK_MUTEX
#   define _USING_MUTEX 0
#endif // (__ENABLE_MUTEX_EVALUATION)

//
// Includes
//
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#if _WINDOWS
#   include <direct.h> // digital mars compiler
#   include <windows.h>
#endif // _WINDOWS
#if _LINUX || _MAC
#   include <sys/stat.h>
#   include <sys/time.h>
#endif // _LINUX || _MAC
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#if (_USING_MUTEX)
#   include MUTEX_HEADER
#endif // (_USING_MUTEX)

namespace easyloggingpp {
namespace configuration {

// This section contains configurations that are to set by developer.
// These sections can be splitted into two parts;
//
//   * Log formats
//   * Miscellaneous configurations
//
// First part contains all the formatting configuration for each log
// level. Developers are expected to only change the values and not
// data type or constant name.
// Format specifiers used are as following:
//
//  SPECIFIER     |                  DESCRIPTION
// ===============|==================================================
//   %level       |   Log level, e.g, INFO, DEBUG, ERROR etc
//   %datetime    |   Current date and time (while writing log)
//   %date        |   Current date only
//   %time        |   Current time only
//   %user        |   User running the application
//   %host        |   Host/computer name the application is running on
//   %func        |   Function of logging
//   %loc         |   Filename and line number of logging
//   %log         |   The actual log message
//   %vlevel      |   Verbose level (only applicable for VERBOSE logs)
//   \n           |   New line character
//   \t           |   Tab character
//
// Further reading on:
// https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#log-format

const std::string    DEFAULT_LOG_FORMAT       =    "[%level] [%datetime] [%func] [%loc] %log\n";
const std::string    DEBUG_LOG_FORMAT         =    "[%level] [%datetime] [%user@%host] [%func] [%loc] %log\n";
const std::string    INFO_LOG_FORMAT          =    DEFAULT_LOG_FORMAT;
const std::string    WARNING_LOG_FORMAT       =    DEFAULT_LOG_FORMAT;
const std::string    ERROR_LOG_FORMAT         =    DEFAULT_LOG_FORMAT;
const std::string    FATAL_LOG_FORMAT         =    DEFAULT_LOG_FORMAT;
const std::string    PERFORMANCE_LOG_FORMAT   =    DEFAULT_LOG_FORMAT;
const std::string    VERBOSE_LOG_FORMAT       =    "[%level-%vlevel] [%datetime] %log\n";
const std::string    QA_LOG_FORMAT            =    DEFAULT_LOG_FORMAT;

// Part 2 is miscellaneous configurations

// SHOW_STD_OUTPUT
//   High level configuration to determine whether or not to show log to standard
//   output i.e, terminal or command prompt. If this is set to false, logs will not
//   be shown to standard output regardless of log level setting _***_LOGS_TO_STANDARD_OUTPUT
//   Recommendation: true
const bool           SHOW_STD_OUTPUT          =    true;


// SAVE_TO_FILE
//   Same as SHOW_STD_OUTPUT but for saving to file. If this is false, logs will not
//   be written to file regardless of log level setting _***_LOGS_TO_FILE.
//   Be careful when you set this option to false
//   Recommendation: true
const bool           SAVE_TO_FILE             =    false;


// LOG_FILENAME
//   Filename of log file. This should only be filename and not the whole path.
//   Path is set in different configuration below (CUSTOM_LOG_FILE_LOCATION).
//   If custom location is not used, log will be saved in executable path.
const std::string    LOG_FILENAME             =    "myeasylog.log";


// CUSTOM_LOG_FILE_LOCATION
//   Path where log file should be saved. Configuration below (USE_CUSTOM_LOCATION)
//   must be set to true in order for this to take affect.
//   NOTES
//    * This location path should end with slash ( '/' for linux and '\' for windows)
//    * This has to be absolute path. Relative paths will not work
//   Recommendation: Set value according to your need - Do not leave empty
//   If you do not want to use this set USE_CUSTOM_LOCATION to false instead.
const std::string    CUSTOM_LOG_FILE_LOCATION =    "logs/";


// USE_CUSTOM_LOCATION
//   If this is true, logs will be saved to location set in configuration above
//   (CUSTOM_LOG_FILE_LOCATION). Default log location is application run path.
//   Recommendation: As required
const bool           USE_CUSTOM_LOCATION      =    true;

// SHOW_START_FUNCTION_LOG
//   When using performance logging, this determines whether or not to show
//   when a certain function has started executing.
//   Recommendation: false
const bool           SHOW_START_FUNCTION_LOG  =    false;

} // namespace configuration


//          ***********************************************
//     **   PLEASE DO NOT MODIFY ANY LINE BEYOND THIS POINT   **
//          ***********************************************

//
// Source code location macros
//
#if !defined(__FILE__)
#   define __FILE__ ""
#endif // !defined(__FILE__)
#if !defined(__LINE__)
#   define __LINE__ ""
#endif // !defined(__LINE__)
// Determine appropriate function macro according to current compiler
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#   define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
#   define __func__ __PRETTY_FUNCTION__
#else
#   define __func__ ""
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)

// Finally determine which log levels are enabled and which are disabled.
// This is determined by _ENABLE_***_LOGS and _DISABLE_***_LOGS macros.
// These macros defined in following section is then used throughout the process
// of logging.
#define _DEBUG_LOG       ((_ENABLE_DEBUG_LOGS) && !defined(_DISABLE_DEBUG_LOGS))
#define _INFO_LOG        ((_ENABLE_INFO_LOGS) && !defined(_DISABLE_INFO_LOGS))
#define _WARNING_LOG     ((_ENABLE_WARNING_LOGS) && !defined(_DISABLE_WARNING_LOGS))
#define _ERROR_LOG       ((_ENABLE_ERROR_LOGS) && !defined(_DISABLE_ERROR_LOGS))
#define _PERFORMANCE_LOG ((_ENABLE_PERFORMANCE_LOGS) && !defined(_DISABLE_PERFORMANCE_LOGS))
#define _FATAL_LOG       ((_ENABLE_FATAL_LOGS) && !defined(_DISABLE_FATAL_LOGS))
#define _VERBOSE_LOG     ((_ENABLE_VERBOSE_LOGS) && !defined(_DISABLE_VERBOSE_LOGS))
#define _QA_LOG          ((_ENABLE_QA_LOGS) && defined(_QUALITY_ASSURANCE))

#if _VERBOSE_LOG
#   define _VERBOSE_SPECIFIC_INITIALIZATIONS int verboseLevel = -1;
#else
#   define _VERBOSE_SPECIFIC_INITIALIZATIONS
#endif // _VERBOSE_LOG

#if defined(_ALWAYS_CLEAN_LOGS)
#   define _ALWAYS_CLEAN_LOGS_SPECIFIC_INITIALIZATIONS bool alreadyCleanedLogFile = false;
#else
#   define _ALWAYS_CLEAN_LOGS_SPECIFIC_INITIALIZATIONS
#endif // defined(_ALWAYS_CLEAN_LOGS)

// EasyLogging++ uses a lot of extern symbols in order to keep using same values
// to prevent potential memory leaks and to improve performance by not initializing
// variables repeatedly. This include variables like username, hostname, streams
// and list of log types. In order to achieve this, following macro should be used
// once and only once in main.cpp file after all the includes in order to initialize
// extern symbols.
// Candidates for extern symbols are carefully chosen, the rest are static symbols.
#define _INITIALIZE_EASYLOGGINGPP                                             \
namespace easyloggingpp {                                                     \
    namespace internal {                                                      \
        bool loggerInitialized = false;                                       \
        std::stringstream *logStream = NULL;                                  \
        std::ofstream *logFile = NULL;                                        \
        std::stringstream tempStream;                                         \
        std::stringstream tempStream2;                                        \
        std::vector< easyloggingpp::internal::LogType > registeredLogTypes;   \
        easyloggingpp::internal::Counter tempCounter;                         \
        std::vector< easyloggingpp::internal::Counter > registeredCounters;   \
        bool fileNotOpenedErrorDisplayed = false;                             \
        std::string user = "";                                                \
        std::string host = "";                                                \
        _VERBOSE_SPECIFIC_INITIALIZATIONS                                     \
        _ALWAYS_CLEAN_LOGS_SPECIFIC_INITIALIZATIONS                           \
       _MUTEX_SPECIFIC_INIT                                                   \
    }                                                                         \
}

// When using log levels that require program arguments, for example VERBOSE logs require
// to see what VERBOSE levels to log by looking at --v=X argument or --verbose (for level 9)
// argument, following macro should be used.
#define _START_EASYLOGGINGPP(argc, argv) easyloggingpp::internal::setAppArgs(argc, argv);

// When program is exiting, following macro should be used in order to release all the memory
// used by internal symbols.
#define _END_EASYLOGGINGPP easyloggingpp::internal::releaseMemory();

namespace version {
static const char* versionNumber = "6.10";
}

namespace internal {
//
// Static symbols
//
static const std::string kFinalFilename = (easyloggingpp::configuration::USE_CUSTOM_LOCATION ?
                                               easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION :
                                               "") +
                                           easyloggingpp::configuration::LOG_FILENAME;
static bool showDateTime = easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%datetime") != std::string::npos;
static bool showDate = (!easyloggingpp::internal::showDateTime) && (easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%date") != std::string::npos);
static bool showTime = (!easyloggingpp::internal::showDateTime) && (easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%time") != std::string::npos);
static bool showLocation = easyloggingpp::configuration::DEFAULT_LOG_FORMAT.find("%loc") != std::string::npos;

static bool toStandardOutput;
static bool toFile;
static const short kDateBufferSize = 30;
static char dateBuffer[kDateBufferSize];
static char dateFormat[kDateBufferSize];
static std::string logFormat = "";
//
// Extern symbols
//
extern std::string user;
extern std::string host;
extern std::stringstream *logStream;
extern std::ofstream *logFile;
extern std::stringstream tempStream;
extern std::stringstream tempStream2;
extern bool loggerInitialized;
extern bool fileNotOpenedErrorDisplayed;
#if defined(_ALWAYS_CLEAN_LOGS)
extern bool alreadyCleanedLogFile;
#endif // defined(_ALWAYS_CLEAN_LOGS)
#if _VERBOSE_LOG
extern int verboseLevel;
#endif // _VERBOSE_LOG
#if _USING_MUTEX
extern MUTEX_TYPE mutex;
#endif // _USING_MUTEX

// Represents log type and configuration such as format and target
class LogType {
public:
    explicit LogType(const std::string& name_,
                     const std::string& format_,
                     bool toStandardOutput_,
                     bool toFile_) :
        name(name_),
        format(format_),
        toStandardOutput(toStandardOutput_),
        toFile(toFile_) {}
    bool operator==(const std::string& name) const {
        return this->name == name;
    }
    std::string name;
    std::string format;
    bool toStandardOutput;
    bool toFile;
};

// Constant iterator for log type
typedef std::vector< easyloggingpp::internal::LogType >::const_iterator LogTypeConstIter;

// Represents all the log types in current context
extern std::vector< easyloggingpp::internal::LogType > registeredLogTypes;

// Represent a counter
class Counter {
public:
    explicit Counter(void) :
        filename(""),
        lineNumber(0),
        position(1) {}
    explicit Counter(const char* filename_,
                     unsigned long int lineNumber_) :
        filename(filename_),
        lineNumber(lineNumber_),
        position(1) {}
    bool operator==(const Counter& other) {
        return ((this->filename == other.filename) &&
                (this->lineNumber == other.lineNumber));
    }
    void resetLocation(const char* filename_,
                       unsigned long int lineNumber_) {
        this->filename = filename_;
        this->lineNumber = lineNumber_;
    }
    const char* filename;
    unsigned long int lineNumber;
    unsigned int position;
};

// Iterator for counter
typedef std::vector< easyloggingpp::internal::Counter >::iterator CounterIter;

// Represents list of all registered counters
extern std::vector < easyloggingpp::internal::Counter > registeredCounters;

// Represents a temporary counter used to do fast lookups. This is defined so that
// temporary variables are not defined in every iteration. We just reset the
// location of this temporary counter and look it up.
extern easyloggingpp::internal::Counter tempCounter;

// Internal message from EasyLogging++. This is used as less number of times
// as possible to minimize annoying outputs.
static inline void internalMessage(const std::string& message) {
    std::cout << std::endl << "[EasyLogging++] " << message << std::endl << std::endl;
}

// Determines the arguments used by EasyLogging++ and store them into static and extern
// symbols where applicable.
// Specifically, looks for '--v=X' or '--verbose' arguments, where X is a digit between
// 0 and 9 and store the digit value into verboseLevel. The max verbose level is 9
// and this set when '--verbose' argument is provided. Priority is given to '--v=X' arguments
static void setAppArgs(int argc, char** argv) {
    while (argc-- > 0) {
#if _VERBOSE_LOG
        const int kMaxVerboseLevel = 9;
        // Look for --v=X argument
        if ((strlen(argv[argc]) >= 5) &&
                (argv[argc][0] == '-') &&
                (argv[argc][1] == '-') &&
                (argv[argc][2] == 'v') &&
                (argv[argc][3] == '=') &&
                (isdigit(argv[argc][4]))) {
            // Current argument is --v=X
            // where X is a digit between 0-9
            easyloggingpp::internal::verboseLevel = atoi(argv[argc] + 4);
        }
        // Look for --verbose argument
        else if ((strlen(argv[argc]) == 9) &&
                 (argv[argc][0] == '-') &&
                 (argv[argc][1] == '-') &&
                 (argv[argc][2] == 'v') &&
                 (argv[argc][3] == 'e') &&
                 (argv[argc][4] == 'r') &&
                 (argv[argc][5] == 'b') &&
                 (argv[argc][6] == 'o') &&
                 (argv[argc][7] == 's') &&
                 (argv[argc][8] == 'e')) {
            easyloggingpp::internal::verboseLevel = kMaxVerboseLevel;
        }
        // Look for -v argument
        else if ((strlen(argv[argc]) == 2) &&
                 (argv[argc][0] == '-') &&
                 (argv[argc][1] == 'v')) {
            easyloggingpp::internal::verboseLevel = kMaxVerboseLevel;
        }
#endif // _VERBOSE_LOG
    }
}

static void setAppArgs(int argc, const char** argv) {
    char** args = const_cast<char**>(argv);
    easyloggingpp::internal::setAppArgs(argc, args);
}

// Determines if log path exists or not.
static bool logPathExist(void) {
#if _WINDOWS
    DWORD fileType = GetFileAttributesA(easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str());
    if (fileType == INVALID_FILE_ATTRIBUTES) {
        return false;
    }
    return (fileType & FILE_ATTRIBUTE_DIRECTORY);
#elif _LINUX || _MAC
    struct stat st;
    return (stat(easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str(), &st) == 0);
#endif // _WINDOWS
}

// Creates log path with read, write and execute permissions for
// all users except for 'no-read' for 'others'.
static void createLogPath(void) {
#if _WINDOWS || _LINUX || _MAC
    if ((easyloggingpp::configuration::USE_CUSTOM_LOCATION) &&
            (easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.size() > 0) &&
            (!easyloggingpp::internal::logPathExist())) {
        int status = -1;
#   if _WINDOWS
        const char* pathDelimiter = "\\";
#   elif _LINUX || _MAC
        const char* pathDelimiter = "/";
#   endif // _WINDOWS
        std::string fullPathToBuild =
                easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION[0] == '/' ? pathDelimiter : "";
        char* currentPath = const_cast<char*>(easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION.c_str());
        currentPath = strtok(currentPath, pathDelimiter);
        while (currentPath != NULL) {
            fullPathToBuild = fullPathToBuild + currentPath + pathDelimiter;
#   if _WINDOWS
            status = _mkdir(fullPathToBuild.c_str());
#   elif _LINUX || _MAC
            status = mkdir(fullPathToBuild.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH); // rwx,rwx,wx
#   endif // _WINDOWS
            if (status == -1) {
                easyloggingpp::internal::internalMessage("Unable to create log path [" + fullPathToBuild + "]");
                return;
            }
            currentPath = strtok(NULL, pathDelimiter);
        }
        if (status == -1) {
            easyloggingpp::internal::internalMessage("Unable to create log path [" + easyloggingpp::configuration::CUSTOM_LOG_FILE_LOCATION + "]");
        }
    }
#endif // _WINDOWS || _LINUX || _MAC
}

// Gets current date and time with milliseconds.
static std::string getDateTime(void) {
    if (!(easyloggingpp::internal::showDateTime || easyloggingpp::internal::showDate || easyloggingpp::internal::showTime)) {
        return "";
    }
    long milliSeconds = 0;
#if _LINUX || _MAC
    timeval currTime;
    gettimeofday(&currTime, NULL);
    if ((easyloggingpp::internal::showDateTime) || (easyloggingpp::internal::showTime)) {
        milliSeconds = currTime.tv_usec / 1000;
    }
    struct tm * timeInfo = localtime(&currTime.tv_sec);
    strftime(easyloggingpp::internal::dateBuffer, easyloggingpp::internal::kDateBufferSize, easyloggingpp::internal::dateFormat, timeInfo);
    if ((easyloggingpp::internal::showDateTime) || (easyloggingpp::internal::showTime)) {
        sprintf(easyloggingpp::internal::dateBuffer, "%s.%03ld", easyloggingpp::internal::dateBuffer, milliSeconds);
    }
#elif _WINDOWS
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", easyloggingpp::internal::dateBuffer, easyloggingpp::internal::kDateBufferSize) != 0) {
        static DWORD oldTick = GetTickCount();
        if ((easyloggingpp::internal::showDateTime) || (easyloggingpp::internal::showTime)) {
            milliSeconds = (long)(GetTickCount() - oldTick) % 1000;
        }
        if ((easyloggingpp::internal::showDateTime) || (easyloggingpp::internal::showTime)) {
            sprintf(easyloggingpp::internal::dateBuffer, "%s.%03ld", easyloggingpp::internal::dateBuffer, milliSeconds);
        }
    }
#endif
    return std::string(easyloggingpp::internal::dateBuffer);
}

// Runs command on terminal and returns the output.
// This is applicable only on linux and mac, for all other OS, an empty string is returned.
static std::string getBashOutput(const char* command) {
#if _LINUX || _MAC
    FILE* proc = popen(command, "r");
    if (proc != NULL) {
        const short hBuffMaxSize = 20;
        char hBuff[hBuffMaxSize];
        fgets(hBuff, hBuffMaxSize, proc);
        pclose(proc);
        short actualHBuffSize = strlen(hBuff);
        if (actualHBuffSize > 0) {
            if (hBuff[actualHBuffSize - 1] == '\n') {
                hBuff[actualHBuffSize - 1] = '\0';
            }
            return std::string(hBuff);
        }
        return "";
    } else {
        return "";
    }
#else
    return "";
#endif // _LINUX || _MAC
}

// Gets current username.
static std::string getUsername(void) {
#if _WINDOWS
    char* username = getenv("USERNAME");
#elif _LINUX || _MAC
    char* username = getenv("USER");
#endif // _WINDOWS
    if ((username == NULL) || ((strcmp(username, "") == 0))) {
        // No username found by environment variable
        // Try harder by using bash command 'whoami' if on linux or mac
        return easyloggingpp::internal::getBashOutput("whoami");
    } else {
        return std::string(username);
    }
}

// Gets current host name or computer name.
static std::string getHostname(void) {
#if _WINDOWS
    char* hostname = getenv("COMPUTERNAME");
#elif _LINUX || _MAC
    char* hostname = getenv("HOSTNAME");
#endif // _WINDOWS
    if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
        // No host name found by environment variable
        // Try harder by using bash command 'hostname' if on linux or mac
        std::string strHostname = easyloggingpp::internal::getBashOutput("hostname");
        if (strHostname == "") {
            // Still nothing found, return 'unknown-host'
            return std::string("unknown-host");
        } else {
            return strHostname;
        }
    } else {
        return std::string(hostname);
    }
}

// Clean all the streams.
static inline void cleanStream(void) {
    easyloggingpp::internal::tempStream.str("");
    easyloggingpp::internal::tempStream2.str("");
    if (easyloggingpp::internal::logStream) {
        easyloggingpp::internal::logStream->str("");
    }
}

// Release all the memory used by EasyLogging++.
static inline void releaseMemory(void) {
    _LOCK_MUTEX
    if (easyloggingpp::internal::loggerInitialized) {
        easyloggingpp::internal::cleanStream();
        if (easyloggingpp::internal::logFile) {
            delete easyloggingpp::internal::logFile;
            easyloggingpp::internal::logFile = NULL;
        }
        if (easyloggingpp::internal::logStream) {
            delete easyloggingpp::internal::logStream;
            easyloggingpp::internal::logStream = NULL;
        }
        easyloggingpp::internal::registeredLogTypes.clear();
        easyloggingpp::internal::registeredCounters.clear();
        easyloggingpp::internal::loggerInitialized = false;
    }
    _UNLOCK_MUTEX
}

// Determine what is being shown for date/time and update dateFormat symbol accordingly.
static void updateDateFormat(void) {
    const char* dateFormatLocal = "%d/%m/%Y";
    const char* timeFormatLocal = "%H:%M:%S";
    if (easyloggingpp::internal::showDate) {
        strcpy(easyloggingpp::internal::dateFormat, dateFormatLocal);
    } else if (easyloggingpp::internal::showTime) {
        strcpy(easyloggingpp::internal::dateFormat, timeFormatLocal);
    } else if (easyloggingpp::internal::showDateTime) {
        strcpy(easyloggingpp::internal::dateFormat, dateFormatLocal);
        strcat(easyloggingpp::internal::dateFormat, " ");
        strcat(easyloggingpp::internal::dateFormat, timeFormatLocal);
    }
}

// Initialize logger, this is where all the memories are allocated and uses loggerInitialized
// symbol to determine whether or not to allocate memory. This function also looks at high
// level configurations like SHOW_STD_OUTPUT and SAVE_TO_FILE and allocate memory to whats
// needed.
static void init(void) {
    if (!easyloggingpp::internal::loggerInitialized) {
        // Logger
        easyloggingpp::internal::logStream = new std::stringstream();
        // Path
        easyloggingpp::internal::createLogPath();
        // Log file
        if (easyloggingpp::configuration::SAVE_TO_FILE) {
            std::ios_base::openmode mode = std::ofstream::out | std::ofstream::app;
#if defined(_ALWAYS_CLEAN_LOGS)
            if (!easyloggingpp::internal::alreadyCleanedLogFile) {
                mode = std::ofstream::out;
                easyloggingpp::internal::alreadyCleanedLogFile = true;
            }
#endif //defined(_ALWAYS_CLEAN_LOGS)
            easyloggingpp::internal::logFile = new std::ofstream(easyloggingpp::internal::kFinalFilename.c_str(), mode);
            if ((!easyloggingpp::internal::fileNotOpenedErrorDisplayed) && (!easyloggingpp::internal::logFile->is_open())) {
                easyloggingpp::internal::internalMessage("Unable to open log file [" + easyloggingpp::internal::kFinalFilename + "]");
                easyloggingpp::internal::fileNotOpenedErrorDisplayed = true;
            } else {
                easyloggingpp::internal::logFile->close();
            }
        }
        // Date format
        easyloggingpp::internal::updateDateFormat();
        // Username and host
        easyloggingpp::internal::user = easyloggingpp::internal::getUsername();
        easyloggingpp::internal::host = easyloggingpp::internal::getHostname();
        // Different log levels
#if _DEBUG_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("DEBUG", easyloggingpp::configuration::DEBUG_LOG_FORMAT, _DEBUG_LOGS_TO_STANDARD_OUTPUT, _DEBUG_LOGS_TO_FILE));
#endif // _DEBUG_LOG
#if _INFO_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("INFO", easyloggingpp::configuration::INFO_LOG_FORMAT, _INFO_LOGS_TO_STANDARD_OUTPUT, _INFO_LOGS_TO_FILE));
#endif // _INFO_LOG
#if _WARNING_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("WARNING", easyloggingpp::configuration::WARNING_LOG_FORMAT, _WARNING_LOGS_TO_STANDARD_OUTPUT, _WARNING_LOGS_TO_FILE));
#endif // _WARNING_LOG
#if _ERROR_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("ERROR", easyloggingpp::configuration::ERROR_LOG_FORMAT, _ERROR_LOGS_TO_STANDARD_OUTPUT, _ERROR_LOGS_TO_FILE));
#endif // _ERROR_LOG
#if _FATAL_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("FATAL", easyloggingpp::configuration::FATAL_LOG_FORMAT, _FATAL_LOGS_TO_STANDARD_OUTPUT, _FATAL_LOGS_TO_FILE));
#endif //_FATAL_LOG
#if _PERFORMANCE_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("PERFORMANCE", easyloggingpp::configuration::PERFORMANCE_LOG_FORMAT, _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT, _PERFORMANCE_LOGS_TO_FILE));
#endif // _PERFORMANCE_LOG
#if _VERBOSE_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("VERBOSE", easyloggingpp::configuration::VERBOSE_LOG_FORMAT, _VERBOSE_LOGS_TO_STANDARD_OUTPUT, _VERBOSE_LOGS_TO_FILE));
#endif // _VERBOSE_LOG
#if _QA_LOG
        easyloggingpp::internal::registeredLogTypes.push_back(
            easyloggingpp::internal::LogType("QA", easyloggingpp::configuration::QA_LOG_FORMAT, _QA_LOGS_TO_STANDARD_OUTPUT, _QA_LOGS_TO_FILE));
#endif // _QA_LOG
        easyloggingpp::internal::loggerInitialized = true;
    }
}

// Writes log safely after checking symbols availablility.
static void writeLog(void) {
    if ((easyloggingpp::configuration::SHOW_STD_OUTPUT) && (easyloggingpp::internal::logStream) && (easyloggingpp::internal::toStandardOutput)) {
        std::cout << easyloggingpp::internal::logStream->str();
    }
    if ((easyloggingpp::configuration::SAVE_TO_FILE) && (!easyloggingpp::internal::fileNotOpenedErrorDisplayed) && (easyloggingpp::internal::logStream) &&
            (easyloggingpp::internal::logFile) && (easyloggingpp::internal::toFile)) {
        easyloggingpp::internal::logFile->open(easyloggingpp::internal::kFinalFilename.c_str(), std::ofstream::out | std::ofstream::app);
        (*easyloggingpp::internal::logFile) << easyloggingpp::internal::logStream->str();
        easyloggingpp::internal::logFile->close();
    }
    easyloggingpp::internal::cleanStream();
}

// Updates the format specifier to value in log format
// This is used to build log for writing to standard output or to file.
static void updateFormatValue(const std::string& formatSpecifier, const std::string& value, std::string& currentFormat) {
    size_t foundAt = -1;
    while ((foundAt = currentFormat.find(formatSpecifier, foundAt + 1)) != std::string::npos){
        if (currentFormat[foundAt > 0 ? foundAt - 1 : 0] == 'E') {
            currentFormat.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
            foundAt++;
        } else {
            currentFormat = currentFormat.replace(foundAt, formatSpecifier.size(), value);
            continue;
        }
    }
}

// Determines format for format specifiers common across all the log formats.
static void determineCommonLogFormat(const std::string& format) {
    easyloggingpp::internal::logFormat = format;
    easyloggingpp::internal::showDateTime = format.find("%datetime") != std::string::npos;
    if (!easyloggingpp::internal::showDateTime) {
        easyloggingpp::internal::showDate = (format.find("%date") != std::string::npos);
        easyloggingpp::internal::showTime = (format.find("%time") != std::string::npos);
    }
    easyloggingpp::internal::showLocation = format.find("%loc") != std::string::npos;
    easyloggingpp::internal::updateDateFormat();
}

// Iterates through log types andd find the one matching with current type
static void determineLogFormat(const std::string& type) {
    easyloggingpp::internal::LogTypeConstIter logType(std::find(easyloggingpp::internal::registeredLogTypes.begin(), easyloggingpp::internal::registeredLogTypes.end(), type));
    if (logType != easyloggingpp::internal::registeredLogTypes.end()) {
        easyloggingpp::internal::determineCommonLogFormat(logType->format);
        easyloggingpp::internal::toStandardOutput = logType->toStandardOutput;
        easyloggingpp::internal::toFile = logType->toFile;
        return;
    }
}

// Builds log format. This function is entry point of writing log.
static void buildFormat(const char* func, const char* file, const unsigned long int line, const std::string& type, int verboseLevel = -1) {
    easyloggingpp::internal::init();
    easyloggingpp::internal::determineLogFormat(type);
    easyloggingpp::internal::updateFormatValue("%level", type, easyloggingpp::internal::logFormat);
#if _VERBOSE_LOG
    if (verboseLevel != -1) {
        easyloggingpp::internal::tempStream << verboseLevel;
        easyloggingpp::internal::updateFormatValue("%vlevel", easyloggingpp::internal::tempStream.str(),  easyloggingpp::internal::logFormat);
        easyloggingpp::internal::tempStream.str("");
    }
#endif // _VERBOSE_LOG
    if (easyloggingpp::internal::showDateTime) {
        easyloggingpp::internal::updateFormatValue("%datetime", easyloggingpp::internal::getDateTime(), easyloggingpp::internal::logFormat);
    } else if (easyloggingpp::internal::showDate) {
        easyloggingpp::internal::updateFormatValue("%date", easyloggingpp::internal::getDateTime(), easyloggingpp::internal::logFormat);
    } else if (easyloggingpp::internal::showTime) {
        easyloggingpp::internal::updateFormatValue("%time", easyloggingpp::internal::getDateTime(), easyloggingpp::internal::logFormat);
    }
    easyloggingpp::internal::updateFormatValue("%func", std::string(func), easyloggingpp::internal::logFormat);
    if (easyloggingpp::internal::showLocation) {
        easyloggingpp::internal::tempStream << file << ":" << line;
        easyloggingpp::internal::updateFormatValue("%loc", easyloggingpp::internal::tempStream.str(), easyloggingpp::internal::logFormat);
    }
    easyloggingpp::internal::updateFormatValue("%user", easyloggingpp::internal::user, easyloggingpp::internal::logFormat);
    easyloggingpp::internal::updateFormatValue("%host", easyloggingpp::internal::host, easyloggingpp::internal::logFormat);
    easyloggingpp::internal::updateFormatValue("%log", easyloggingpp::internal::tempStream2.str(), easyloggingpp::internal::logFormat);
    if (easyloggingpp::internal::logStream) {
        (*easyloggingpp::internal::logStream) << logFormat;
    }
}

// Registers the counter. This should not be called by itself since
// one counter can be registered only once and this is checked
// below in validateCounter(..)
static void registerCounter(const easyloggingpp::internal::Counter& counter) {
    easyloggingpp::internal::registeredCounters.push_back(counter);
}

// Resets the counter when it reaches its limit to prevent any failure
// since internal counter (position) uses int for data type.
static void resetCounter(easyloggingpp::internal::CounterIter& counter, int n) {
    if (counter->position >= 5000) {
        counter->position = (n >= 1 ? 5000 % n : 0);
    }
}

// Validates the counter to see if it is valid to write the log for current iteration (n)
// This also registers and resets the counter position if neccessary.
static bool validateCounter(const char* func, const char* filename, unsigned long int lineNumber, int n) {
    _LOCK_MUTEX;
    // Supress unused warning
    (void)func;
    easyloggingpp::internal::tempCounter.resetLocation(filename, lineNumber);
    bool result = false;
    easyloggingpp::internal::CounterIter counter(
        std::find(easyloggingpp::internal::registeredCounters.begin(),
            easyloggingpp::internal::registeredCounters.end(), easyloggingpp::internal::tempCounter));
    if (counter == easyloggingpp::internal::registeredCounters.end()) {
        easyloggingpp::internal::registerCounter(easyloggingpp::internal::tempCounter);
        counter = easyloggingpp::internal::registeredCounters.end() - 1;
    }
    if ((n >= 1) && (counter->position != 0) && (counter->position % n == 0)) {
        result = true;
    }
    easyloggingpp::internal::resetCounter(counter, n);
    ++counter->position;
    _UNLOCK_MUTEX
    return result;
}

//
// Logging macros
//
#define WRITE_LOG(type, log, func, file, line)                                                        \
    _LOCK_MUTEX                                                                                       \
    easyloggingpp::internal::tempStream2 << log;                                                      \
    easyloggingpp::internal::buildFormat(func, file, line, std::string(type));                        \
    easyloggingpp::internal::writeLog();                                                              \
    _UNLOCK_MUTEX

#define WRITE_VLOG(level, log, func, file, line)                                                      \
    _LOCK_MUTEX                                                                                       \
    if (easyloggingpp::internal::verboseLevel >= level) {                                             \
        easyloggingpp::internal::tempStream2 << log;                                                  \
        easyloggingpp::internal::buildFormat(func, file, line, std::string("VERBOSE"), level);        \
        easyloggingpp::internal::writeLog();                                                          \
    }                                                                                                 \
    _UNLOCK_MUTEX

#define WRITE_LOG_EVERY_N(type, n, log, func, file, line)                                             \
    if (easyloggingpp::internal::validateCounter(func, file, line, n)) {                              \
        WRITE_LOG(type, log, func, file, line)                                                        \
    }

#define WRITE_VLOG_EVERY_N(n, level, log, func, file, line)                                           \
    if (easyloggingpp::internal::validateCounter(func, file, line, n)) {                              \
        WRITE_VLOG(level, log, func, file, line)                                                      \
    }

#if _DEBUG_LOG
#    define INTERNAL_DEBUG_LOG(logMessage, func, file, line) WRITE_LOG("DEBUG",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_DEBUG_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_DEBUG_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_DEBUG_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("DEBUG", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define DEBUG(logMessage) WRITE_LOG("DEBUG",logMessage, __func__, __FILE__, __LINE__)
#           define DEBUG_IF(condition, logMessage) if (condition) { DEBUG(logMessage); }
#           define DEBUG_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("DEBUG", n, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#    define INTERNAL_DEBUG_LOG(x, y, z, a)
#    define INTERNAL_CONDITIONAL_DEBUG_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_DEBUG_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define DEBUG(x)
#           define DEBUG_IF(x, y)
#           define DEBUG_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _DEBUG_LOG

#if _INFO_LOG
#    define INTERNAL_INFO_LOG(logMessage, func, file, line) WRITE_LOG("INFO",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_INFO_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_INFO_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_INFO_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("INFO", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define INFO(logMessage) WRITE_LOG("INFO",logMessage, __func__, __FILE__, __LINE__)
#           define INFO_IF(condition, logMessage) if (condition) { INFO(logMessage); }
#           define INFO_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("INFO", n, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#       define INTERNAL_INFO_LOG(x, y, z, a)
#       define INTERNAL_CONDITIONAL_INFO_LOG(x, y, z, a, b)
#       define INTERNAL_INTERVAL_INFO_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define INFO(x)
#           define INFO_IF(x, y)
#           define INFO_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _INFO_LOG

#if _WARNING_LOG
#    define INTERNAL_WARNING_LOG(logMessage, func, file, line) WRITE_LOG("WARNING",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_WARNING_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_WARNING_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_WARNING_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("WARNING", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define WARNING(logMessage) WRITE_LOG("WARNING",logMessage, __func__, __FILE__, __LINE__)
#           define WARNING_IF(condition, logMessage) if (condition) { WARNING(logMessage); }
#           define WARNING_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("WARNING", n, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#    define INTERNAL_WARNING_LOG(x, y, z, a)
#    define INTERNAL_CONDITIONAL_WARNING_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_WARNING_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define WARNING(x)
#           define WARNING_IF(x, y)
#           define WARNING_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _WARNING_LOG

#if _ERROR_LOG
#    define INTERNAL_ERROR_LOG(logMessage, func, file, line) WRITE_LOG("ERROR",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_ERROR_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_ERROR_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_ERROR_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("ERROR", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define ERROR(logMessage) WRITE_LOG("ERROR",logMessage, __func__, __FILE__, __LINE__)
#           define ERROR_IF(condition, logMessage) if (condition) { ERROR(logMessage); }
#           define ERROR_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("ERROR", n, logMessage)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#    define INTERNAL_ERROR_LOG(x, y, z, a)
#    define INTERNAL_CONDITIONAL_ERROR_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_ERROR_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define ERROR(x)
#           define ERROR_IF(x, y)
#           define ERROR_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _ERROR_LOG
#if _FATAL_LOG
#    define INTERNAL_FATAL_LOG(logMessage, func, file, line) WRITE_LOG("FATAL",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_FATAL_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_FATAL_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_FATAL_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("FATAL", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define FATAL(logMessage) WRITE_LOG("FATAL",logMessage, __func__, __FILE__, __LINE__)
#           define FATAL_IF(condition, logMessage) if (condition) { FATAL(logMessage); }
#           define FATAL_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("FATAL", n, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#    define INTERNAL_FATAL_LOG(x, y, z, a)
#    define INTERNAL_CONDITIONAL_FATAL_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_FATAL_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define FATAL(x)
#           define FATAL_IF(x, y)
#           define FATAL_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _FATAL_LOG

#if _PERFORMANCE_LOG
static std::string formatSeconds(double secs) {
    double result = secs;
    std::string unit = "seconds";
    std::stringstream ss;
    if (result > 60.0f) {result /= 60; unit = "minutes";
        if (result > 60.0f) {result /= 60; unit = "hours";
            if (result > 24.0f) {result /= 24; unit = "days";}
        }
    }
    ss << result << " " << unit;
    return ss.str();
}
#    define INTERNAL_PERFORMANCE_LOG(logMessage, func, file, line) WRITE_LOG("PERFORMANCE",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_PERFORMANCE_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_PERFORMANCE_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_PERFORMANCE_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("PERFORMANCE", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define PERFORMANCE(logMessage) WRITE_LOG("PERFORMANCE",logMessage, __func__, __FILE__, __LINE__)
#           define PERFORMANCE_IF(condition, logMessage) if (condition) { PERFORMANCE(logMessage); }
#           define PERFORMANCE_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("PERFORMANCE", n, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#    define START_FUNCTION_LOG "Executing [" << __func__ << "]"
#    define TIME_OUTPUT "Executed [" << __func__ << "] in [~ " <<                                       \
        easyloggingpp::internal::formatSeconds(difftime(functionEndTime, functionStartTime)) << "]"
#    define FUNC_SUB_COMMON_START {                                                                     \
        if (easyloggingpp::configuration::SHOW_START_FUNCTION_LOG) {                                    \
            INTERNAL_PERFORMANCE_LOG(START_FUNCTION_LOG, __func__, __FILE__, __LINE__)                  \
        }                                                                                               \
        time_t functionStartTime, functionEndTime;                                                      \
        time(&functionStartTime);
#    define FUNC_SUB_COMMON_END time(&functionEndTime); INTERNAL_PERFORMANCE_LOG(TIME_OUTPUT, __func__, __FILE__, __LINE__);
#    define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#    define END_SUB FUNC_SUB_COMMON_END }
#    define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#    define RETURN(return_value) FUNC_SUB_COMMON_END return return_value;
#    define END_FUNC(return_value) RETURN(return_value) }
#    define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#    define END_MAIN(return_value) FUNC_SUB_COMMON_END; _END_EASYLOGGINGPP; return return_value; }
#    define RETURN_MAIN(exit_status) _END_EASYLOGGINGPP return exit_status;
#else
#    define INTERNAL_PERFORMANCE_LOG(x, y, z, a)
#    define INTERNAL_CONDITIONAL_PERFORMANCE_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_PERFORMANCE_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define PERFORMANCE(x)
#           define PERFORMANCE_IF(x, y)
#           define PERFORMANCE_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#    define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
#    define END_SUB }
#    define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
#    define END_FUNC(x) return x; }
#    define RETURN(expr) return expr;
#    define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#    define END_MAIN(x) _END_EASYLOGGINGPP return x; }
#    define RETURN_MAIN(exit_status) _END_EASYLOGGINGPP return exit_status;
#endif // _PERFORMANCE_LOG

#if _VERBOSE_LOG
#    define INTERNAL_VERBOSE_LOG(level, logMessage, func, file, line) WRITE_VLOG(level, logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_VERBOSE_LOG(condition, level, logMessage, func, file, line) if (condition) { INTERNAL_VERBOSE_LOG(level, logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_VERBOSE_LOG(n, level, logMessage, func, file, line) WRITE_VLOG_EVERY_N(n, level, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define VERBOSE(level, logMessage) WRITE_VLOG(level, logMessage, __func__, __FILE__, __LINE__)
#           define VERBOSE_IF(condition, level, logMessage) if (condition) { VERBOSE(level, logMessage); }
#           define VERBOSE_EVERY_N(n, level, logMessage) WRITE_VLOG_EVERY_N(n, level, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#    define INTERNAL_VERBOSE_LOG(x, y, z, a, b)
#    define INTERNAL_CONDITIONAL_VERBOSE_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_VERBOSE_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define VERBOSE(x, y)
#           define VERBOSE_IF(x, y, z)
#           define VERBOSE_EVERY_N(x, y, z)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _VERBOSE_LOG

#if _QA_LOG
#    define INTERNAL_QA_LOG(logMessage, func, file, line) WRITE_LOG("QA",logMessage, func, file, line)
#    define INTERNAL_CONDITIONAL_QA_LOG(condition, logMessage, func, file, line) if (condition) { INTERNAL_QA_LOG(logMessage, func, file, line); }
#    define INTERNAL_INTERVAL_QA_LOG(n, logMessage, func, file, line) WRITE_LOG_EVERY_N("QA", n, logMessage, func, file, line)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define QA(logMessage) WRITE_LOG("QA",logMessage, __func__, __FILE__, __LINE__)
#           define QA_IF(condition, logMessage) if (condition) { QA(logMessage); }
#           define QA_EVERY_N(n, logMessage) WRITE_LOG_EVERY_N("QA", n, logMessage, __func__, __FILE__, __LINE__)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#else
#    define INTERNAL_QA_LOG(x, y, z, a)
#    define INTERNAL_CONDITIONAL_QA_LOG(x, y, z, a, b)
#    define INTERNAL_INTERVAL_QA_LOG(x, y, z, a, b)
#       ifdef _SUPPORT_LEGACY_LOG_NAMES
#           define QA(x)
#           define QA_IF(x, y)
#           define QA_EVERY_N(x, y)
#       endif // _SUPPORT_LEGACY_LOG_NAMES
#endif // _QA_LOG
} // namespace internal
namespace helper {
// Reads log from current log file an returns standard string
static std::string readLog(void) {
    _LOCK_MUTEX
    std::stringstream ss;
    if (easyloggingpp::configuration::SAVE_TO_FILE) {
        std::ifstream logFileReader(easyloggingpp::internal::kFinalFilename.c_str(), std::ifstream::in);
        if (logFileReader.is_open()) {
            std::string line;
            while (logFileReader.good()) {
                std::getline(logFileReader, line);
                ss << line << std::endl;
            }
            logFileReader.close();
        } else {
            ss << "Error opening log file [" << easyloggingpp::internal::kFinalFilename << "]";
        }
    } else {
        ss << "Logs are not being saved to file!";
    }
    _UNLOCK_MUTEX
    return ss.str();
}
} // namespace helper

// Following namespace is useless and is ONLY there to supress
// warnings of unused symbols. These symbols include conditional
// and helper functions. Please do not use these functions.
namespace unusedwarningsuppresser {
class UnusedWarningSupresser {
private:
    void suppressAll(void) {
        std::string readLogWarningSupress = easyloggingpp::helper::readLog();
        const char* argv[1];
        argv[1] = "easylogging++ warning suppressor";
        easyloggingpp::internal::setAppArgs(0, argv);
        easyloggingpp::internal::buildFormat("suppress", "suppress", 1, "suppress");
        easyloggingpp::internal::writeLog();
        std::cout << easyloggingpp::version::versionNumber;
        easyloggingpp::internal::validateCounter("", "", 0, 0);
#if _PERFORMANCE_LOG
        easyloggingpp::internal::formatSeconds(1);
#endif
    }
};
} // warningsuppresser
} // namespace easyloggingpp
#else // ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))
// Essentials
#define INTERNAL_DEBUG_LOG(x, y, z, a)
#define INTERNAL_INFO_LOG(x, y, z, a)
#define INTERNAL_WARNING_LOG(x, y, z, a)
#define INTERNAL_ERROR_LOG(x, y, z, a)
#define INTERNAL_FATAL_LOG(x, y, z, a)
#define INTERNAL_PERFORMANCE_LOG(x, y, z, a)
#define INTERNAL_VERBOSE_LOG(x, y, z, a, b)
#define INTERNAL_QA_LOG(x, y, z, a)
#ifdef _SUPPORT_LEGACY_LOG_NAMES
#   define DEBUG(x)
#   define INFO(x)
#   define WARNING(x)
#   define ERROR(x)
#   define FATAL(x)
#   define PERFORMANCE(x)
#   define VERBOSE(x, y)
#   define QA(x)
#endif // _SUPPORT_LEGACY_LOG_NAMES
// Performance logs
#define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
#define END_SUB }
#define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
#define END_FUNC(x) }
#define RETURN(expr) return expr;
#define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#define END_MAIN(x) END_FUNC(x)
#define RETURN_MAIN(exit_status) return exit_status;
// Conditional logs
#define INTERNAL_CONDITIONAL_DEBUG_LOG(x, y, z, a, b)
#define INTERNAL_CONDITIONAL_INFO_LOG(x, y, z, a, b)
#define INTERNAL_CONDITIONAL_WARNING_LOG(x, y, z, a, b)
#define INTERNAL_CONDITIONAL_ERROR_LOG(x, y, z, a, b)
#define INTERNAL_CONDITIONAL_FATAL_LOG(x, y, z, a, b)
#define INTERNAL_CONDITIONAL_PERFORMANCE_LOG(x, y, z, a, b)
#define INTERNAL_CONDITIONAL_VERBOSE_LOG(x, y, z, a, b, c)
#define INTERNAL_CONDITIONAL_QA_LOG(x, y, z, a, b)
#ifdef _SUPPORT_LEGACY_LOG_NAMES
#   define INFO_IF(x, y)
#   define WARNING_IF(x, y)
#   define ERROR_IF(x, y)
#   define FATAL_IF(x, y)
#   define PERFORMANCE_IF(x, y)
#   define VERBOSE_IF(x, y, z)
#   define QA_IF(x, y)
#endif // _SUPPORT_LEGACY_LOG_NAMES
// Interval logs
#define INTERNAL_INTERVAL_DEBUG_LOG(x, y, z, a, b)
#define INTERNAL_INTERVAL_INFO_LOG(x, y, z, a, b)
#define INTERNAL_INTERVAL_WARNING_LOG(x, y, z, a, b)
#define INTERNAL_INTERVAL_ERROR_LOG(x, y, z, a, b)
#define INTERNAL_INTERVAL_FATAL_LOG(x, y, z, a, b)
#define INTERNAL_INTERVAL_PERFORMANCE_LOG(x, y, z, a, b)
#define INTERNAL_INTERVAL_VERBOSE_LOG(x, y, z, a, b, c)
#define INTERNAL_INTERVAL_QA_LOG(x, y, z, a, b)
#ifdef _SUPPORT_LEGACY_LOG_NAMES
#   define DEBUG_EVERY_N(x, y)
#   define INFO_EVERY_N(x, y)
#   define WARNING_EVERY_N(x, y)
#   define ERROR_EVERY_N(x, y)
#   define FATAL_EVERY_N(x, y)
#   define PERFORMANCE_EVERY_N(x, y)
#   define VERBOSE_EVERY_N(x, y, z)
#   define QA_EVERY_N(x, y)
#endif // _SUPPORT_LEGACY_LOG_NAMES
// Miscellaneous
#define _INITIALIZE_EASYLOGGINGPP
#define _START_EASYLOGGINGPP(x, y)
#define _END_EASYLOGGINGPP
// Helper functions
#include <string>  // For readLog()
#include <sstream> // For LogWrapper
namespace easyloggingpp {
namespace version {
static const char* versionNumber = "6.10";
}
namespace helper {
static std::string readLog() {
    return "";
}
} // namespace helper
} // namespace easyloggingpp
#endif // ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))

namespace easyloggingpp {
namespace internal {
// A log wrapper to provide class based logging, yet using power of preprocessor directives
// to minimize instructions certain (or all) logging is disabled
class LogWrapper {
public:
    enum kLogLevel { kInfo,
                     kWarning,
                     kError,
                     kDebug,
                     kFatal,
                     kPerformance,
                     kQa,
                     kVerbose };

    enum kLogAspect { kNormal,
                      kConditional,
                      kInterval };

    explicit LogWrapper(kLogAspect logAspect_,
               kLogLevel logLevel_,
               const char* func_,
               const char* file_,
               const unsigned long int line_,
               bool condition_ = true,
               int verboseLevel_ = 0,
               int counter_ = 0) :
        logAspect(logAspect_),
        logLevel(logLevel_),
        func(func_),
        file(file_),
        line(line_),
        condition(condition_),
        verboseLevel(verboseLevel_),
        counter(counter_){}

    ~LogWrapper(void) {
        switch (logLevel) {
        case kInfo:
            if (logAspect == kNormal) {
                INTERNAL_INFO_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_INFO_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_INFO_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kWarning:
            if (logAspect == kNormal) {
                INTERNAL_WARNING_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_WARNING_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_WARNING_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kError:
            if (logAspect == kNormal) {
                INTERNAL_ERROR_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_ERROR_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_ERROR_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kDebug:
            if (logAspect == kNormal) {
                INTERNAL_DEBUG_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_DEBUG_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_DEBUG_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kFatal:
            if (logAspect == kNormal) {
                INTERNAL_FATAL_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_FATAL_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_FATAL_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kPerformance:
            if (logAspect == kNormal) {
                INTERNAL_PERFORMANCE_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_PERFORMANCE_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_PERFORMANCE_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kQa:
            if (logAspect == kNormal) {
                INTERNAL_QA_LOG(logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_QA_LOG(condition, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_QA_LOG(counter, logStream.str(), func, file, line);
            }
            break;
        case kVerbose:
            if (logAspect == kNormal) {
                INTERNAL_VERBOSE_LOG(verboseLevel, logStream.str(), func, file, line);
            }
            else if (logAspect == kConditional) {
                INTERNAL_CONDITIONAL_VERBOSE_LOG(condition, verboseLevel, logStream.str(), func, file, line);
            }
            else if (logAspect == kInterval) {
                INTERNAL_INTERVAL_VERBOSE_LOG(counter, verboseLevel, logStream.str(), func, file, line);
            }
            break;
        }
    }

    inline std::ostream& operator<<(const std::string& log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(char log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(bool log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(signed short log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(unsigned short log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(signed int log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(unsigned int log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(signed long log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(unsigned long log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(float log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(double log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(const char* log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(const void* log_) { logStream << log_; return logStream; }
    inline std::ostream& operator<<(long double log_) { logStream << log_; return logStream; }

private:
    unsigned int logAspect;
    unsigned int logLevel;
    const char* func;
    const char* file;
    const unsigned long int line;
    bool condition;
    int verboseLevel;
    int counter;
    std::stringstream logStream;
};
} // internal
} // easyloggingpp
// Normal logs
#define LINFO easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,           \
    easyloggingpp::internal::LogWrapper::kInfo, __func__, __FILE__, __LINE__)
#define LWARNING easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,        \
    easyloggingpp::internal::LogWrapper::kWarning, __func__, __FILE__, __LINE__)
#define LDEBUG easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,          \
    easyloggingpp::internal::LogWrapper::kDebug, __func__, __FILE__, __LINE__)
#define LERROR easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,          \
    easyloggingpp::internal::LogWrapper::kError, __func__, __FILE__, __LINE__)
#define LFATAL easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,          \
    easyloggingpp::internal::LogWrapper::kFatal, __func__, __FILE__, __LINE__)
#define LPERFORMANCE easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,    \
    easyloggingpp::internal::LogWrapper::kPerformance, __func__, __FILE__, __LINE__)
#define LQA easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal,             \
    easyloggingpp::internal::LogWrapper::kQa, __func__, __FILE__, __LINE__)
#define LVERBOSE(level) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kNormal, \
    easyloggingpp::internal::LogWrapper::kVerbose, __func__, __FILE__, __LINE__, true, level)
// Conditional logs
#define LINFO_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,           \
    easyloggingpp::internal::LogWrapper::kInfo, __func__, __FILE__, __LINE__, condition)
#define LWARNING_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,        \
    easyloggingpp::internal::LogWrapper::kWarning, __func__, __FILE__, __LINE__, condition)
#define LDEBUG_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,          \
    easyloggingpp::internal::LogWrapper::kDebug, __func__, __FILE__, __LINE__, condition)
#define LERROR_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,          \
    easyloggingpp::internal::LogWrapper::kError, __func__, __FILE__, __LINE__, condition)
#define LFATAL_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,          \
    easyloggingpp::internal::LogWrapper::kFatal, __func__, __FILE__, __LINE__, condition)
#define LPERFORMANCE_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,    \
    easyloggingpp::internal::LogWrapper::kPerformance, __func__, __FILE__, __LINE__, condition)
#define LQA_IF(condition) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional,             \
    easyloggingpp::internal::LogWrapper::kQa, __func__, __FILE__, __LINE__, condition)
#define LVERBOSE_IF(condition, level) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kConditional, \
    easyloggingpp::internal::LogWrapper::kVerbose, __func__, __FILE__, __LINE__, condition, level)
// Interval logs
#define LINFO_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,           \
    easyloggingpp::internal::LogWrapper::kInfo, __func__, __FILE__, __LINE__, true, 0, n)
#define LWARNING_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,        \
    easyloggingpp::internal::LogWrapper::kWarning, __func__, __FILE__, __LINE__, true, 0, n)
#define LDEBUG_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,          \
    easyloggingpp::internal::LogWrapper::kDebug, __func__, __FILE__, __LINE__, true, 0, n)
#define LERROR_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,          \
    easyloggingpp::internal::LogWrapper::kError, __func__, __FILE__, __LINE__, true, 0, n)
#define LFATAL_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,          \
    easyloggingpp::internal::LogWrapper::kFatal, __func__, __FILE__, __LINE__, true, 0, n)
#define LPERFORMANCE_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,    \
    easyloggingpp::internal::LogWrapper::kPerformance, __func__, __FILE__, __LINE__, true, 0, n)
#define LQA_EVERY_N(n) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval,             \
    easyloggingpp::internal::LogWrapper::kQa, __func__, __FILE__, __LINE__, condition, 0, n)
#define LVERBOSE_EVERY_N(n, level) easyloggingpp::internal::LogWrapper(easyloggingpp::internal::LogWrapper::kInterval, \
    easyloggingpp::internal::LogWrapper::kVerbose, __func__, __FILE__, __LINE__, true, level, n)
#endif //EASYLOGGINGPP_H
