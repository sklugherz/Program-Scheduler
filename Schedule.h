#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Show.h"
#include <vector>

class Schedule {
  public:
    Schedule();
    ~Schedule();
    Schedule& operator+=(const Show& rhs);
    Schedule& operator+=(const Schedule& rhs);
    Schedule& operator+(const Schedule& rhs);
    Schedule& operator-=(const int& id);
    Show& operator[](const size_t& index);
    size_t size() const;
    std::vector<Show> schedule;
    //helper methods
    bool isadult = true;
    std::ostream& print(std::ostream& os, const Schedule& rhs) const;
    bool inRange(double low, double high, double y);
    bool grups(bool adult = true);
    class iterator;
    iterator begin() const;
    iterator end() const;

};

class Schedule::iterator {
  public:
    iterator& operator++();
    iterator operator++(int inc);
    const Show& operator*() const;
    bool operator==(const iterator& rhs) const;
    bool operator!=(const iterator& rhs) const;
    iterator(const std::vector<Show>* sched, const bool& addme, size_t ind);
    ~iterator();
    const std::vector<Show>* addysched;
    bool addy;
    size_t index;
};
    std::ostream& operator<<(std::ostream& os, const Schedule& rhs);
    //print methods
    std::string timePrint(int time);
    double timeConvert(int time);
    std::string printFiller(size_t diffLength);
    std::string checkAdult(bool adult);

#endif
