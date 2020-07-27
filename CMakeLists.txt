cmake_minimum_required(VERSION 3.16)

project(
    CylinderBankDev
    DESCRIPTION "The project which includes both the CylinderBank library as well as the Sandbox app"
)

add_subdirectory(CylinderBank)
add_subdirectory(Sandbox)
