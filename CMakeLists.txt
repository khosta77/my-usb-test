cmake_minimum_required(VERSION 3.0)
project(USBTest)

if(APPLE)  # Настройка для mac OS
    execute_process(
        COMMAND sw_vers -productVersion
        OUTPUT_VARIABLE OSX_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message("-- build for MacOS ${OSX_VERSION}")
    include_directories(/opt/homebrew/Cellar/libusb/1.0.26/include)
    link_directories(/opt/homebrew/Cellar/libusb/1.0.26/lib)
endif()

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7l")
    message("Этот код выполняется на Raspberry Pi")
    set(ENV{PKG_CONFIG_PATH} "/usr/lib/arm-linux-gnueabihf/pkgconfig")
    # Использование pkg-config для поиска пакета libusb
    find_package(PkgConfig REQUIRED)
    pkg_search_module(LIBUSB REQUIRED libusb-1.0)
endif()

# Добавление исполняемого файла с именем main.out
add_executable(main.out ./project/main.cpp)

# Включение заголовочных файлов и библиотек libusb
if(APPLE)
    target_link_libraries(main.out libusb-1.0.dylib)
endif()

if(UNIX)
    include_directories(${LIBUSB_INCLUDE_DIRS})
    target_link_libraries(main.out ${LIBUSB_LIBRARIES})
endif()
