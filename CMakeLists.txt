cmake_minimum_required(VERSION 3.0)
project(USBTest)

# Использование pkg-config для поиска пакета libusb
find_package(PkgConfig REQUIRED)
pkg_search_module(LIBUSB REQUIRED libusb-1.0)

# Добавление исполняемого файла
add_executable(main.out ./project/main.cpp)

# Включение заголовочных файлов и библиотек libusb
include_directories(${LIBUSB_INCLUDE_DIRS})
target_link_libraries(main.out ${LIBUSB_LIBRARIES})
