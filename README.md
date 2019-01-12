# SysLoggerC++
SysLoggerC++ is a simple and easy to use C++ thread-safe [syslog](https://linux.die.net/man/3/syslog) wrapper.

Keywords: syslog, C++17, thread-safe, concurrent, library, wrapper C++

Note: For C++14 just replace std::optional with std::experimental::optional in code.

## About SysLoggerC++:
SysLoggerC++ writes messages to the /var/log/syslog. These messages can be also filtered and 
redirected to the custom file. For this purpose special rsyslog and logrotate
configuration files must be created and copied into the appropriate directories. 
###Custom syslog file
To redirect messages from 
example:
```Shell
sudo cp examples/etc/rsyslog.d/99-custom-syslog.conf /etc/rsyslog.d/
sudo cp examples/etc/logrotate.d/custom-syslog /etc/logrotate.d/

sudo rervice rsyslog restart
sudo rervice logrotate restart
```
Prepare directory for custom syslog file and its archives:
```Shell
sudo mkdir -p /var/log/custom-syslog/
sudo chown -R syslog:adm /var/log/custom-syslog/
```
Now if you run ./SyslogExample, its syslog messages are redirected to the
```Shell
/var/log/custom-syslog/custom-syslog-example.log
```

##Build instructions
Use git to clone the repository.
```Shell
git clone https://github.com/JakubFornadel/SysLogger.git
cd SysLogger
```

A CMake configuration file is provided for multiplatform support.

```Shell
mkdir build
cd build

cmake -DSYSLOGGERCPP_BUILD_EXAMPLES=ON ../
cmake --build .

# run example
./SyslogExample
```

##Usage
```C++
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
```

