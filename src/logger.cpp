#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "cgimap/logger.hpp"

using std::string;
using std::ostream;
using std::ofstream;
using boost::format;

using std::shared_ptr;

namespace logger {

static shared_ptr<ostream> stream;
static pid_t pid;

void initialise(const string &filename) {
  stream = std::shared_ptr<ostream>(
      new ofstream(filename.c_str(), std::ios_base::out | std::ios_base::app));
  pid = getpid();
}

std::string get_current_timestamp()
{
  struct tm tstruct;
  char buf[80];
  time_t now = time(0);
  tstruct = *gmtime(&now);
  strftime(buf, sizeof(buf), "%FT%T", &tstruct);
  return buf;
}


void message(const string &m) {
  if (stream) {

    *stream << "[" << get_current_timestamp() << " #" << pid << "] " << m
            << std::endl;
  }
}

void message(const format &m) { message(m.str()); }
}
