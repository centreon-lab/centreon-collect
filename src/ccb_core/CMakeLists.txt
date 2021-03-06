# Version.
include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

configure_file(
  ${CMAKE_SOURCE_DIR}/include/com/centreon/broker/version.hh.in
  ${CMAKE_BINARY_DIR}/broker-version.hh
  @ONLY
)
configure_file(
  ${CMAKE_SOURCE_DIR}/include/com/centreon/broker/vars.hh.in
  ${CMAKE_BINARY_DIR}/vars.hh
  @ONLY
)

include(${CMAKE_SOURCE_DIR}/cmake/FindMariaDB.cmake)

# Broker vars
# Core library.
add_library(ccb_core
  STATIC
  # Sources.
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/acceptor.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/ack.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/connector.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/factory.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/input.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/input_buffer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/internal.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/output.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/stream.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/bbdo/version_response.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/ceof/ceof_deserializer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/ceof/ceof_iterator.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/ceof/ceof_parser.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/ceof/ceof_serializer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/ceof/ceof_token.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/ceof/ceof_writer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/compression/factory.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/compression/internal.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/compression/opener.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/compression/stack_array.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/compression/stream.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/compression/zlib.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/applier/endpoint.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/applier/modules.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/applier/state.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/endpoint.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/logger.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/parser.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/config/state.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/database_config.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/cfile.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/directory_event.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/directory_watcher.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/factory.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/fifo.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/internal.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/opener.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/splitter.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/file/stream.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/instance_broadcast.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/data.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/endpoint.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/event_info.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/events.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/factory.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/protocols.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/raw.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/io/stream.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/log_v2.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/logging/file.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/logging/logger.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/logging/logging.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/logging/manager.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/logging/syslogger.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/logging/temp_logger.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/mapping/entry.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/mapping/source.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/diagnostic.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/filesystem.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/global_lock.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/misc.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/processing_speed_computer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/string.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/stringifier.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/tokenizer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/uuid.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/misc/variant.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/modules/handle.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/modules/loader.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/multiplexing/engine.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/multiplexing/hooker.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/multiplexing/muxer.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/multiplexing/publisher.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/multiplexing/subscriber.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/persistent_cache.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/persistent_file.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/processing/acceptor.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/processing/failover.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/processing/feeder.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/processing/stat_visitable.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/processing/thread.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/stats/helper.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/time/daterange.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/time/timeperiod.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/time/timerange.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/time/timezone_locker.cc
  ${CMAKE_SOURCE_DIR}/src/ccb_core/time/timezone_manager.cc
)

# Static libraries.
set_target_properties(ccb_core PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(ccb_core PROPERTIES COMPILE_FLAGS "${MYSQL_CFLAGS} -fPIC")

target_link_libraries(ccb_core PUBLIC
  CONAN_PKG::json11 CONAN_PKG::spdlog CONAN_PKG::zlib CONAN_PKG::asio ${MYSQL_LIBS}
  )