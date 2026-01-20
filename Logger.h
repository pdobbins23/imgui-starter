#pragma once

#include <functional>
#include <map>
#include <ostream>
#include <vector>

enum class LogLevel {
  Info = 0,
  Warn = 1,
  Error = 2,
};

class Logger {
public:
  static Logger &instance() {
    static Logger logger;
    return logger;
  }

  std::vector<const char *> getSinks();

  using SinkFn = std::function<void(LogLevel, const std::string &)>;
  void addSink(const char *name, SinkFn fn, LogLevel filter = LogLevel::Info);

  void clearSinks();

  LogLevel getSinkFilter(const char *name);
  void setSinkFilter(const char *name, LogLevel filter);

  void log(LogLevel level, const char *msg);

  static SinkFn sinkFile(std::ostream &os);
  static SinkFn sinkStdout();

private:
  Logger() = default;
  ~Logger() = default;

  struct Sink {
    SinkFn fn;
    LogLevel filter;
  };

  std::map<const char *, Sink> sinks;
};
