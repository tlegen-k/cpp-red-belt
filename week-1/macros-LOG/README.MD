## Macros LOG

You are given class Logger and macros LOG
```cpp
class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }
  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }
  void Log(const string& message);
private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) ...
```
LOG macro parameters - an object of the Logger class and a string message that should be passed to the Log method. Depending on the settings of the Logger class object, the logged message must be preceded by the file name or line number. See unit tests in the solution template for a more detailed description of the behavior.

Implement the LOG macro so that it adds the file name and line number to the logged message, depending on the settings of the logger object. Send for verification a cpp file containing

- LOG macro implementation
- declaration of the Logger class, while you can add additional fields and methods to it if necessary
- definitions of all methods of the Logger class
