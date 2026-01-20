# imgui-starter

Using the provided code provided here you have a base Dear IMGUI project for Windows and macOS. There is a basic CMakefile in this project that includes the necessary files to create an application that brings up just a basic screen.

You must add a logging system to this code that you will be using THROUGHOUT the quarter. This logging system should do two things.

It should be able to log to a Dear IMGUI debug console
It should also log its output to a file.

For the submission, make a branch of this repo and submit a new GitHub URL

## Additions - Peter Dobbins

**NOTE:** I developed this on Linux (NixOS).

To build the project, run:

```
cmake -B build

cmake --build build
```

- I added a `flake.nix` which contains the development environment for this project for NixOS. Mainly, this environment contains `mesa` (OpenGL libraries), `glfw` (GLFW libraries), clang compiler, and CMake.
- I created a `Logger` class, which stores a list of `Sink` which represent logical sinks for logging data. Every time a logging event is dispatched by the logger, it will forward the logging data to each `Sink` through its `SinkFn` (callback). The `Logger` will only forward logging events to sinks with the same or smaller log level filter (i.e. a sink with filter Warn (ID 1) will receive logging events with the log level value >= 1, so that includes Error (ID 2) but not Info (ID 0)). Each sink has a unique name which can be used for referring to it from other places in code, as well as updating the sink's log level filter.
- I also created a `ImGuiLogger` class, which is a logger that logs its output into a custom ImGui widget. The `ImGuiLogger` class also offers its own sink via `sinkFn()`, which can be registered to the `Logger` instance. The `ImGuiLogger` class also applies different colors to each log line based on the `LogLevel`, which is supplied to it's sink callback.
- In `Application.cpp`, I register three sinks: one for stdout (implementation based on sinkFile), one for the log file (using sinkFile), and one using ImGuiLogger.
- I also created custom UI for selecting the current log level filter for each registered sink.
