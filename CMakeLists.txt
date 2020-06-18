cmake_minimum_required(VERSION 3.15)
project(StockApplication)

set(CMAKE_CXX_STANDARD 14)

add_executable(StockApplication main.cpp VectorData.h TechnicalAnalysis.h Inventory.h)