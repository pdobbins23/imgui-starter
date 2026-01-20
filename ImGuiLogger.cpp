#include "ImGuiLogger.h"
#include "imgui/imgui.h"

Logger::SinkFn ImGuiLogger::sinkFn() {
  return [this](LogLevel level, const std::string &line) {
    this->sink(level, line);
  };
}

void ImGuiLogger::clear() { lines.clear(); }

void ImGuiLogger::draw() {
  ImGui::Checkbox("Auto Scroll", &autoScroll);

  ImGui::BeginChild("Scrolling Buffer", ImVec2(0, 0), false,
                    ImGuiWindowFlags_HorizontalScrollbar);
  {
    for (const auto &line : lines) {
      ImGui::TextColored(line.color, "%s", line.content.c_str());
    }

    if (autoScroll && scrollToBottom) {
      ImGui::SetScrollHereY(1.0f);
      scrollToBottom = false;
    }
  }
  ImGui::EndChild();
}

void ImGuiLogger::sink(LogLevel level, const std::string &line) {
  ImVec4 color;

  switch (level) {
  case LogLevel::Info:
    color = ImVec4(1.0, 1.0, 1.0, 1.0);
    break;
  case LogLevel::Warn:
    color = ImVec4(1.0, 1.0, 0.0, 1.0);
    break;
  case LogLevel::Error:
    color = ImVec4(1.0, 0.0, 0.0, 1.0);
    break;
  }

  lines.push_back({line, color});

  scrollToBottom = true;
}
