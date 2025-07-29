#pragma once

#include "Logger.h"

#ifdef AB_DEBUG
    # define ASSERT(condition, message) \
    { \
        if (!(condition)) \
        { \
            char buffer[LOG_TEMPLATE_LENGTH]; \
            sprintf_s(buffer, "[Assert] [File: %s] [Line: %d] ", __FILE__, __LINE__); \
            Wrum::Logger::GetInstance().Log(std::move(buffer), Wrum::LogVerbosity::Error, message); \
            std::terminate(); \
        } \
    }
#else
    #   define ASSERT(condition, message) {}
#endif