cmake_minimum_required(VERSION 3.13)
project(OOP5)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP5 main.cpp utils/dynamicarray.h tests/Tests.cpp tests/Tests.h domain/movie.cpp domain/movie.h repository/repository.cpp repository/repository.h controller/adminController.cpp controller/adminController.h userinterface/userinterface.cpp userinterface/userinterface.h controller/userController.cpp controller/userController.h exceptions/validationException.cpp exceptions/validationException.h exceptions/repositoryException.cpp exceptions/repositoryException.h utils/movieValidator.cpp utils/movieValidator.h repository/CSVRepository.cpp repository/CSVRepository.h repository/HTMLRepository.cpp repository/HTMLRepository.h utils/comparator.h utils/comparatorAscendingByTitle.cpp utils/comparatorAscendingByTitle.h utils/comparatorDescendingByLikes.cpp utils/comparatorDescendingByLikes.h repository/MYSQLRepository.cpp repository/MYSQLRepository.h)
set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage -lmysqlcppconn")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
include_directories(/usr/include/cppconn)
include_directories(/usr/include)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(OOP5 /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so)