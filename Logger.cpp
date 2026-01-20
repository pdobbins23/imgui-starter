#include "Logger.h"

#include <iostream>

std::vector<const char *> Logger::getSinks() {
  std::vector<const char *> sinkNames;
  sinkNames.reserve(sinks.size());

  for (const auto &pair : sinks) {
    sinkNames.push_back(pair.first);
  }

  return sinkNames;
}

void Logger::addSink(const char *name, SinkFn fn, LogLevel filter) {
  sinks.insert({name, {fn, filter}});
}

void Logger::clearSinks() { sinks.clear(); }

LogLevel Logger::getSinkFilter(const char *name) {
  return sinks.at(name).filter;
}

void Logger::setSinkFilter(const char *name, LogLevel filter) {
  sinks.at(name).filter = filter;
}

void Logger::log(LogLevel level, const char *msg) {
  const char *prefix = "";

  switch (level) {
  case LogLevel::Info:
    prefix = "[INFO] ";
    break;
  case LogLevel::Warn:
    prefix = "[WARN] ";
    break;
  case LogLevel::Error:
    prefix = "[ERROR] ";
    break;
  }

  std::string line = std::string(prefix) + msg;

  for (auto &sink : sinks) {
    if (level >= sink.second.filter) {
      sink.second.fn(level, line);
    }
  }
}

Logger::SinkFn Logger::sinkFile(std::ostream &os) {
  return [&os](LogLevel level, const std::string &line) {
    os << line << std::endl;
  };
}

Logger::SinkFn Logger::sinkStdout() { return Logger::sinkFile(std::cout); }
