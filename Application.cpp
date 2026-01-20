#include "Application.h"
#include "ImGuiLogger.h"
#include "Logger.h"
#include "imgui/imgui.h"
#include <fstream>

namespace ClassGame {
//
// our global variables
//
ImGuiLogger imguiLogger;

std::ofstream logFile("log.txt");

//
// game starting point
// this is called by the main render loop in main.cpp
//
void GameStartUp() {
  // Initialize logging system
  Logger &logger = Logger::instance();

  logger.addSink("stdout", Logger::sinkStdout());
  logger.addSink("imgui", imguiLogger.sinkFn());
  logger.addSink("file", Logger::sinkFile(logFile));

  logger.log(LogLevel::Info, "Game started successfully");
}

//
// game render loop
// this is called by the main render loop in main.cpp
//
void RenderGame() {
  ImGui::DockSpaceOverViewport();

  ImGui::Begin("Game Log");
  {
    Logger &logger = Logger::instance();

    if (ImGui::BeginPopupModal("Game Log Options")) {
      ImGui::Columns(2, nullptr, true);

      auto sinks = logger.getSinks();
      static int selected_index = -1;

      ImGui::BeginChild("Sink List");
      {
        ImGui::Text("Sinks:");
        
        for (int i = 0; i < sinks.size(); i++) {
          if (ImGui::Selectable(sinks[i], selected_index == i)) {
            selected_index = i;
          }
        }
      }
      ImGui::EndChild();

      ImGui::NextColumn();

      ImGui::BeginChild("Properties");
      {
        if (selected_index >= 0 && selected_index < sinks.size()) {
          ImGui::Text("Sink: %s", sinks[selected_index]);

          const char *log_levels[] = {"Info", "Warn", "Error"};
          int selected_level =
              static_cast<int>(logger.getSinkFilter(sinks[selected_index]));

          if (ImGui::Combo("Log Filter", &selected_level, log_levels,
                           IM_ARRAYSIZE(log_levels))) {
            logger.setSinkFilter(sinks[selected_index],
                                 static_cast<LogLevel>(selected_level));
          }
        } else {
          ImGui::Text("Select a sink");
        }
      }
      ImGui::EndChild();

      ImGui::Columns(1);

      if (ImGui::Button("Ok")) {
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }

    if (ImGui::Button("Options")) {
      ImGui::OpenPopup("Game Log Options");
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear")) {
      imguiLogger.clear();
    }

    ImGui::SameLine();

    if (ImGui::Button("Test Info")) {
      logger.log(LogLevel::Info, "This is a test info message");
    }

    ImGui::SameLine();

    if (ImGui::Button("Test Warn")) {
      logger.log(LogLevel::Warn, "This is a test warning message");
    }

    ImGui::SameLine();

    if (ImGui::Button("Test Error")) {
      logger.log(LogLevel::Error, "This is a test error message");
    }

    imguiLogger.draw();
  }
  ImGui::End();
}

//
// end turn is called by the game code at the end of each turn
// this is where we check for a winner
//
void EndOfTurn() {}
} // namespace ClassGame
