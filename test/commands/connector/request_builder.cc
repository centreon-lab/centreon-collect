/*
** Copyright 2011-2012 Merethis
**
** This file is part of Centreon Engine.
**
** Centreon Engine is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Engine is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Engine. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include <exception>
#include <QCoreApplication>
#include <QDebug>
#include "com/centreon/engine/commands/connector/request_builder.hh"
#include "com/centreon/engine/error.hh"
#include "test/unittest.hh"

using namespace com::centreon::engine;
using namespace com::centreon::engine::commands::connector;

/**
 *  Check valid build.
 *
 *  @return True if builder correctly build, false otherwise.
 */
static bool is_valid() {
  request_builder& builder = request_builder::instance();
  if (builder.build("0\0\0\0\0").isNull() == true
      || builder.build("4\0\0\0\0").isNull() == true
      || builder.build("5\0\0\0\0").isNull() == true) {
    return (false);
  }
  return (true);
}

/**
 *  Check invalid build.
 *
 *  @return True if builder cannot build, false otherwise.
 */
static bool is_invalid() {
  request_builder& builder = request_builder::instance();
  try {
    builder.build(".\0\0\0\0");
  }
  catch (...) {
    return (true);
  }
  return (false);
}

/**
 *  Check request builder.
 */
int main_test() {
  if (is_valid() == false)
    throw (engine_error() << "error: is valid failed.");

  if (is_invalid() == false)
    throw (engine_error() << "error: is invalid failed.");

  return (0);
}

/**
 *  Init the unit test.
 */
int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  unittest utest(&main_test);
  QObject::connect(&utest, SIGNAL(finished()), &app, SLOT(quit()));
  utest.start();
  app.exec();
  return (utest.ret());
}
