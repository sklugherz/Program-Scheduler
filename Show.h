#ifndef SHOW_H
#define SHOW_H
#include <string>

class Show {
  public:
    std::string mName;
    std::string mChannel;
    int mStart;
    int mLength;
    int mID;
    bool mAdult;
    std::string name() const;
    std::string channel() const;
    int start() const;
    int length() const;
    int id() const;
    bool adult() const;
    Show() = delete;
    ~Show();
    Show(const std::string& name, const std::string& channel, const int& start, const int& length, bool adult = false);

};


#endif
