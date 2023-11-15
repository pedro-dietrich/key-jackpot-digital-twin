cmake_minimum_required(VERSION 3.17)
project("Key Jackpot Digital Twin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(Stb REQUIRED)
find_package(nlohmann_json REQUIRED)

set(
    INCLUDES
    ${Stb_INCLUDE_DIR}
)

set(
    LIBRARIES
    glfw
    glad::glad
    glm::glm
    nlohmann_json::nlohmann_json
)

set(EXECUTABLE "key_jackpot_digital_twin")
file(GLOB_RECURSE SRC_FILES "src/**.cpp")
add_executable(${EXECUTABLE} ${SRC_FILES})

target_include_directories(${EXECUTABLE} PRIVATE ${INCLUDES})

target_link_libraries(${EXECUTABLE} PRIVATE ${LIBRARIES})

install(TARGETS ${EXECUTABLE} DESTINATION .)
install(FILES $<TARGET_FILE:glfw> DESTINATION .)
