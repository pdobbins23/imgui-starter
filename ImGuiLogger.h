#pragma once

#include "Logger.h"
#include "imgui/imgui.h"
#include <string>
#include <vector>


class ImGuiLogger {
public:
  struct Line {
    std::string content;
    ImVec4 color;
  };

  ImGuiLogger() = default;
  ~ImGuiLogger() = default;

  Logger::SinkFn sinkFn();

  void clear();

  void draw();

private:
  void sink(LogLevel, const std::string &);

private:
  std::vector<Line> lines;

  bool autoScroll = true;
  bool scrollToBottom = false;
};
