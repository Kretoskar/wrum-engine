#pragma once

#include "Logger.h"

#ifdef AB_DEBUG
    # define ASSERT_MSG(condition, message) \
    { \
        if (!(condition)) \
        { \
            char buffer[LOG_TEMPLATE_LENGTH]; \
            sprintf_s(buffer, "[Assert] [File: %s] [Line: %d] ", __FILE__, __LINE__); \
            Wrum::Logger::GetInstance().Log(std::move(buffer), Wrum::LogVerbosity::Error, message); \
            std::terminate(); \
        } \
    }

    # define ASSERT(condition) assert(condition)

    #define ASSERT_NO_ENTRY() ASSERT_MSG(false, "No entry assert entered")

#else
    #   define ASSERT_MSG(condition, message) {}
    #   define ASSERT(condition) {}
    #   define ASSERT_NO_ENTRY(message) {}
#endif