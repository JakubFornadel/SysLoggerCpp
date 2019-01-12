#include <SysLogger.hpp>
#include <string>

class Person {
public:
  Person(const std::string& name, int age) :
    name_(name),
    age_(age)
  {};
  ~Person() = default;

  friend std::ostream& operator <<(std::ostream& out, const Person& person) {
    out << "Name: " << person.name_ << ", age: " << person.age_;
    return out;
  }
private:
  std::string name_;
  int         age_;
};


int main(void) {
  // test data
  const std::string name = "Alice";
  const Person bob("Bob", 21);

  // Creates logger, specifies application name as "custom-syslog-example". Application name can be used for
  // filtering application specific messages from /var/log/syslog and redirecting it to the custom file
  SysLogger logger("custom-syslog-example" /* application name */,
                   LOG_DEBUG               /* min. log level */,
                   "custom-prefix:"        /* message prefix */);

  // logger accepts any TYPE of parameter to be printed, but it has to overload
  // std::ostream& operator <<(std::ostream& stream, const TYPE& obj)
  logger.info("Start logging...");
  logger.info("Bes friend of", name, "is", bob);

  logger.debug("debug message");
  logger.notice("notice message");
  logger.warning("warning message");
  logger.error("error message");
  logger.critical("critical message");
  logger.alert("alert message");
  logger.emergency("emergency message");

  logger.info("Finish logging...");
}