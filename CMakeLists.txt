cmake_minimum_required(VERSION 3.0.0)
project(weatherapp VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    c:/dev/vcpkg/installed/x64-windows/include/curl
    c:/Users/swift/Desktop/xyz/Group4App/src
)

LINK_DIRECTORIES(
    c:/dev/vcpkg/installed/x64-windows/lib
    c:/Users/swift/Desktop/xyz/Group4App/lib

)

# LINK_LIBRARIES(weatherapp
#     libcurl
# )

add_executable(weatherapp main.c)

TARGET_LINK_LIBRARIES(weatherapp
    libcurl
)
