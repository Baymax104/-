cmake_minimum_required(VERSION 3.19)
project(CppPractice)

set(CMAKE_CXX_STANDARD 20)

add_executable(CppPractice main.cpp Identity.cpp Identity.h Student.cpp Student.h Teacher.cpp Teacher.h Manager.cpp Manager.h View.cpp View.h ComputerRoom.h ComputerRoom.cpp Reservation.h include.h Reservation.cpp)