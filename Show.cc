#include "Show.h"
#include "stdexcept"

Show::Show(const std::string& name, const std::string& channel, const int& start, const int& length, bool adult) : mName(name), mChannel(channel), mStart(start), mLength(length), mAdult(adult) {
  if(mName == "" || mChannel == "" || mStart == -1 || mStart > 96 || mStart + mLength > 96) {
    throw std::runtime_error("Invalid arguments");
  }
  static int id = 0;
  mID = id++;
}

Show::~Show() {}

std::string Show::name() const {
  return mName;
}

std::string Show::channel() const {
  return mChannel;
}

int Show::start() const {
  return mStart * 15;
}

int Show::length() const {
  return mLength * 15;
}

int Show::id() const {
  return mID;
}

bool Show::adult() const {
  return mAdult;
}
