//
// Created by muellerm on 3/28/25.
//

#ifndef SONGDURATION_H
#define SONGDURATION_H
class SongDuration{
  private:
    unsigned int minutes;
    unsigned int seconds;
  public:
    SongDuration(unsigned int min, unsigned int sec);
    int get_total_seconds();
    std::string get_formatted();
};





#endif //SONGDURATION_H
//////////////////////////////////
//
// Created by muellerm on 3/28/25.
//
#include "SongDuration.hpp"
#include <iostream>
#include <string>

SongDuration::SongDuration(unsigned int min, unsigned int sec):minutes(min),seconds(0){
  this->minutes += sec;
  this->seconds = sec % 60;
}

int SongDuration::get_total_seconds(){
  return seconds+60*minutes;
}
std::string SongDuration::get_formatted(){
  std::string form=std::to_string(minutes) + "m " + std::to_string(seconds)+"s";
  return form;
}
/////////////////////
CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l3

main.o:main.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@
SongDuration.o:SongDuration.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@
l3:main.o SongDuration.o
	${CXX}  ${CXXFLAGS} $^ -o $@



clean:
	rm -f *.o l3
