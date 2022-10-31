#include "Schedule.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
Schedule::Schedule() {}

Schedule::~Schedule() {}

Schedule& Schedule::operator+=(const Show& rhs) {
  for(const Show& x : this->schedule) {//check for time
    if(rhs.mChannel == x.mChannel) {
      if(inRange(timeConvert(x.mStart), timeConvert(x.mStart) + timeConvert(x.mLength), timeConvert(rhs.mStart)) || inRange(timeConvert(x.mStart), timeConvert(x.mStart) + timeConvert(x.mLength), timeConvert(rhs.mStart) + timeConvert(rhs.mLength))) {//if times match then check if channels are the same
        throw std::runtime_error("overlapping show times on the same channel");
        return *this;
      }
      else {
        this->schedule.push_back(rhs);
        sort(this->schedule.begin(), this->schedule.end(), [](const Show& a, const Show& b) {return a.mStart < b.mStart ? a.mStart < b.mStart : a.mChannel < b.mChannel;});
        return *this;
      }
    }
  }
  this->schedule.push_back(rhs);
  sort(this->schedule.begin(), this->schedule.end(), [](const Show& a, const Show& b) {return a.mStart < b.mStart ? a.mStart < b.mStart : a.mChannel < b.mChannel;});
  return *this;
}

Schedule& Schedule::operator+=(const Schedule& rhs) {
  try {
    for(const Show& x : rhs.schedule) {
      *this += x;
    }
    return *this;
  }
  catch(const std::runtime_error& rt) {
    return *this;
  }
}

Schedule& Schedule::operator+(const Schedule& rhs) {
  return *this += rhs;
}

Schedule& Schedule::operator-=(const int& id) {
  std::vector<Show> replacement;
  for(const Show& x : this->schedule) {
    if(x.mID == id) {
      for(const Show& y : this->schedule) {
        if(y.mID != id) {
          replacement.push_back(y);
        }
      }
      this->schedule = replacement;
      return *this;
    }
  }
  throw std::runtime_error("Show id DNE");
  return *this;
}

Show& Schedule::operator[](const size_t& index) {
  if(index > schedule.size()) {
    throw std::range_error("Current size: " + std::to_string(schedule.size()) + " is greater than requested index: " + std::to_string(index) + '\n');
  }
  return schedule[index];
}

size_t Schedule::size() const {
  return this->schedule.size();
}

bool Schedule::grups(bool adult) {
  this->isadult = adult;
  return adult;
}

Schedule::iterator Schedule::begin() const{
  return iterator(&this->schedule, this->isadult, 0);
}

Schedule::iterator Schedule::end() const {
  return iterator(&this->schedule, this->isadult, this->schedule.size());
}
//iteartor start
Schedule::iterator::iterator(const std::vector<Show>* sched, const bool& addme, size_t ind) : addysched(sched), addy(addme), index(ind) {}

Schedule::iterator::~iterator() {}

const Show& Schedule::iterator::operator*() const {
  return (*addysched)[index];
}

Schedule::iterator& Schedule::iterator::operator++() {
  if(!addy) {
    if((*addysched)[index].mAdult == true) {
      ++index;
    }
  }
  ++index;
  return *this;
}

Schedule::iterator Schedule::iterator::operator++(int inc) {
  (void)inc;
  auto tmp = *this;
  ++*this;
  return tmp;
}

bool Schedule::iterator::operator==(const iterator& rhs) const {
  return this->index == rhs.index;
}

bool Schedule::iterator::operator!=(const iterator& rhs) const {
  return this->index != rhs.index;
}

//free functions

std::ostream& operator<<(std::ostream& os, const Schedule& rhs) {
  return rhs.print(os, rhs);
}

std::ostream& operator<<(const std::ostream& os, const std::string& rhs) {
  return os << rhs;
}
                           
std::ostream& Schedule::print(std::ostream& os, const Schedule& rhs) const {
long unsigned int maxLength = 0;
  for(const Show& x : rhs.schedule) {
    if(x.mChannel.length() > maxLength) {
      maxLength = x.mChannel.length();
    }
  }
  for(const Show& x : rhs.schedule) {
    long unsigned int diffLength = maxLength - x.mChannel.length();
    os << timePrint(x.mStart) << '-' << timePrint(x.mStart + x.mLength) << ' ' << x.mChannel << printFiller(diffLength) << ' ' << x.mName << checkAdult(x.mAdult) << '\n';
  }
  return os;
}

std::string timePrint(int time) {
  int minutes = (time * 15) % 60;
  int hours = (time * 15) / 60;
  std::string rtn =  std::to_string(hours) + ':' + std::to_string(minutes);
  if(minutes == 0) {
    rtn = rtn + '0';
  }
  if(hours < 10) {
    rtn = '0' + rtn;
  }
  return rtn;
}

double timeConvert(int time) {
  double rtn = time * 15;
  rtn = rtn / 60;
  return rtn;
}

bool Schedule::inRange(double low, double high, double y) {
  return (low < y && y < high);
}

std::string printFiller(size_t diffLength) {
  std::string rtn = "";
  if(diffLength == 0) {
    return rtn;
  }
  while(diffLength > 0) {
    rtn += ' ';
    diffLength--;
  }
  return rtn;
}

std::string checkAdult(bool adult) {
   std::string rtn = "";
  if(adult) {
    rtn = '*';
  }
  return rtn;
}
