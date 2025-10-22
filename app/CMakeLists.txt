set( DEMO_NAME "mqtt_mutual" )

set(SDK_DIR ${CMAKE_SOURCE_DIR}/aws-iot-device-sdk-embedded-c)

include(${SDK_DIR}/libraries/standard/coreMQTT/mqttFilePaths.cmake)
include(${SDK_DIR}/libraries/standard/backoffAlgorithm/backoffAlgorithmFilePaths.cmake)


find_package(CURL REQUIRED)

# CPP files are searched for supporting CI build checks that verify C++ linkage of the coreMQTT library
file(GLOB DEMO_FILE "${CMAKE_CURRENT_LIST_DIR}/${DEMO_NAME}.c")

# Demo target.
add_executable(
    ${DEMO_NAME}
        ${DEMO_FILE}
        ${MQTT_SOURCES}
        ${MQTT_SERIALIZER_SOURCES}
        ${BACKOFF_ALGORITHM_SOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/http_client.c
)

target_link_libraries(
    ${DEMO_NAME}
    PRIVATE
        clock_posix
        openssl_posix
)

target_link_libraries(
    ${DEMO_NAME}
    PRIVATE
        ${CURL_LIBRARIES}
)

target_include_directories(
    ${DEMO_NAME}
    PRIVATE
        ${CURL_INCLUDE_DIRS}
)

target_include_directories(
    ${DEMO_NAME}
    PUBLIC
        ${MQTT_INCLUDE_PUBLIC_DIRS}
        ${BACKOFF_ALGORITHM_INCLUDE_PUBLIC_DIRS}
        ${LOGGING_INCLUDE_DIRS}
        ${AWS_DEMO_INCLUDE_DIRS}
        ${SDK_DIR}/demos/include
        ${CMAKE_CURRENT_LIST_DIR}
)

set_macro_definitions(TARGETS ${DEMO_NAME}
                      REQUIRED
                        "AWS_IOT_ENDPOINT"
                        "ROOT_CA_CERT_PATH"
                        "CLIENT_CERT_PATH"
                        "CLIENT_PRIVATE_KEY_PATH"
                        "CLIENT_IDENTIFIER"
                      OPTIONAL
                        "CLIENT_USERNAME"
                        "CLIENT_PASSWORD"
                        "OS_NAME"
                        "OS_VERSION"
                        "HARDWARE_PLATFORM_NAME")
