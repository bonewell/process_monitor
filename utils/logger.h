#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include "log4cplus/log4cplus.h"

#define LOGGER_INIT(file) \
  ::log4cplus::Initializer initializer; \
  ::log4cplus::PropertyConfigurator::doConfigure(file)

#define LOGGER_INSTANCE(name) \
  ::log4cplus::Logger logger = ::log4cplus::Logger::getInstance(name)

#define LOGGER_TRACE() \
  LOG4CPLUS_TRACE_METHOD(logger, __func__)

#define LOGGER_DEBUG(message) \
  LOG4CPLUS_DEBUG(logger, message)

#define LOGGER_INFO(message) \
  LOG4CPLUS_INFO(logger, message)

#define LOGGER_WARN(message) \
  LOG4CPLUS_WARN(logger, message)

#define LOGGER_ERROR(message) \
  LOG4CPLUS_ERROR(logger, message)

#define LOGGER_FATAL(message) \
  LOG4CPLUS_FATAL(logger, message)

#endif  // UTILS_LOGGER_H
