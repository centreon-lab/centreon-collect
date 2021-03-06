cmake_minimum_required(VERSION 3.4)
project("Centreon Collect" C CXX)
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

# Version.
set(COLLECT_MAJOR 20)
set(COLLECT_MINOR 10)
set(COLLECT_PATCH 0)
set(COLLECT_VERSION "${COLLECT_MAJOR}.${COLLECT_MINOR}.${COLLECT_PATCH}")
add_definitions(-DCENTREON_CONNECTOR_VERSION=\"${COLLECT_VERSION}\")
add_definitions(-DCENTREON_BROKER_VERSION=\"${COLLECT_VERSION}\")

project (centreon_collect)

set(CPACK_RPM_COMPONENT_INSTALL IGNORE)
set(CPACK_COMPONENTS_ALL broker broker-cbd clib connector-perl connector-ssh engine-daemon engine-extcommands)
set(CPACK_COMPONENTS_GROUPING "IGNORE")
set(CPACK_PACKAGE_VERSION ${COLLECT_VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_RPM_COMPONENT_INSTALL "ON")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "David Boucher")
set(CPACK_PACKAGE_VENDOR "Centreon")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

#centreon-clib
set(CPACK_PACKAGE_CLIB_PACKAGE_NAME "centreon-clib")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/script/redhat/clib.spec.in" "${CMAKE_BINARY_DIR}/clib.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_CLIB_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/clib.spec")
set(CPACK_RPM_CLIB_FILE_NAME ${CPACK_PACKAGE_CLIB_PACKAGE_NAME}.rpm)

#centreon-connector-perl
set(CPACK_PACKAGE_CONNECTOR-PERL_PACKAGE_NAME "centreon-connector-perl")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/script/redhat/connector-perl.spec.in" "${CMAKE_BINARY_DIR}/connector-perl.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_CONNECTOR-PERL_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/connector-perl.spec")
set(CPACK_RPM_CONNECTOR-PERL_FILE_NAME ${CPACK_PACKAGE_CONNECTOR-PERL_PACKAGE_NAME}.rpm)

#centreon-connector-ssh
set(CPACK_PACKAGE_CONNECTOR-SSH_PACKAGE_NAME "centreon-connector-ssh")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/script/redhat/connector-ssh.spec.in" "${CMAKE_BINARY_DIR}/connector-ssh.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_CONNECTOR-SSH_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/connector-ssh.spec")
set(CPACK_RPM_CONNECTOR-SSH_FILE_NAME ${CPACK_PACKAGE_CONNECTOR-SSH_PACKAGE_NAME}.rpm)

#centreon-engine-daemon
set(CPACK_PACKAGE_ENGINE-DAEMON_PACKAGE_NAME "centreon-engine-daemon")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/script/redhat/engine-daemon.spec.in" "${CMAKE_BINARY_DIR}/engine-daemon.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_ENGINE-DAEMON_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/engine-daemon.spec")
set(CPACK_RPM_ENGINE-DAEMON_FILE_NAME ${CPACK_PACKAGE_ENGINE-DAEMON_PACKAGE_NAME}.rpm)

#centreon-engine-extcommands
set(CPACK_PACKAGE_ENGINE-EXTCOMMANDS_PACKAGE_NAME "centreon-engine-extcommands")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/script/redhat/engine-extcommands.spec.in" "${CMAKE_BINARY_DIR}/engine-extcommands.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_ENGINE-EXTCOMMANDS_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/engine-extcommands.spec")
set(CPACK_RPM_ENGINE-EXTCOMMANDS_FILE_NAME ${CPACK_PACKAGE_ENGINE-EXTCOMMANDS_PACKAGE_NAME}.rpm)

#centreon-broker
set(CPACK_PACKAGE_BROKER_PACKAGE_NAME "centreon-broker")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/script/redhat/broker.spec.in" "${CMAKE_BINARY_DIR}/broker.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_BROKER_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/broker.spec")
set(CPACK_RPM_BROKER_FILE_NAME ${CPACK_PACKAGE_BROKER_PACKAGE_NAME}.rpm)

#centreon-broker-cbd
set(CPACK_PACKAGE_BROKER-CBD_PACKAGE_NAME "centreon-broker-cbd")
set(CPACK_RPM_BROKER-CBD_USER_BINARY_SPECFILE "${CMAKE_BINARY_DIR}/broker-cbd.spec")
set(CPACK_RPM_BROKER-CBD_FILE_NAME ${CPACK_PACKAGE_BROKER-CBD_PACKAGE_NAME}.rpm)

include(CPack)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
else()
  message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

add_subdirectory(src/10-neb)
add_subdirectory(src/15-stats)
add_subdirectory(src/20-bam)
add_subdirectory(src/20-storage)
add_subdirectory(src/50-tcp)
add_subdirectory(src/60-tls)
add_subdirectory(src/70-graphite)
add_subdirectory(src/70-influxdb)
add_subdirectory(src/70-lua)
add_subdirectory(src/70-simu)
add_subdirectory(src/70-rrd)
add_subdirectory(src/80-sql)
add_subdirectory(src/cbd)
add_subdirectory(src/cbmod)
add_subdirectory(src/cbwd)
add_subdirectory(src/ccb_conflict_manager)
add_subdirectory(src/ccb_core)
add_subdirectory(src/ccb_neb)
add_subdirectory(src/ccb_rpc)
add_subdirectory(src/ccb_sql)
add_subdirectory(src/cce_core)
add_subdirectory(src/external_command)
add_subdirectory(src/cce_rpc)
add_subdirectory(src/centengine)
add_subdirectory(src/centenginestats)
add_subdirectory(src/centenginestats2)
add_subdirectory(src/clib)
add_subdirectory(src/connectors)

#if (WITH_TESTING)
  add_subdirectory(tests/broker)
  add_subdirectory(tests/cbwd)
  add_subdirectory(tests/clib)
  add_subdirectory(tests/connectors)
  add_subdirectory(tests/engine)
#endif()
