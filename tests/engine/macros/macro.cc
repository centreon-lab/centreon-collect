/*
 * Copyright 2019 Centreon (https://www.centreon.com/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For more information : contact@centreon.com
 *
 */

#include <gtest/gtest.h>

#include <com/centreon/engine/configuration/applier/command.hh>
#include <com/centreon/engine/configuration/applier/host.hh>
#include <com/centreon/engine/configuration/applier/service.hh>
#include <com/centreon/engine/configuration/applier/state.hh>
#include <com/centreon/engine/configuration/parser.hh>
#include <com/centreon/engine/hostescalation.hh>
#include <com/centreon/engine/macros.hh>
#include <com/centreon/engine/macros/grab_host.hh>
#include <com/centreon/engine/macros/process.hh>
#include <fstream>
#include <helper.hh>

using namespace com::centreon;
using namespace com::centreon::engine;

class Macro : public ::testing::Test {
 public:
  void SetUp() override { init_config_state(); }

  void TearDown() override { deinit_config_state(); }
};

// Given host configuration without host_id
// Then the applier add_object throws an exception.
TEST_F(Macro, pollerName) {
  configuration::parser parser;
  configuration::state st;

  std::remove("/tmp/test-config.cfg");

  std::ofstream ofs("/tmp/test-config.cfg");
  ofs << "poller_name=poller-test" << std::endl;
  ofs << "log_file=\"\"" << std::endl;
  ofs.close();

  parser.parse("/tmp/test-config.cfg", st);
  configuration::applier::state::instance().apply(st);

  std::string out;
  nagios_macros mac;
  process_macros_r(&mac, "$POLLERNAME$", out, 0);
  ASSERT_EQ(out, "poller-test");
}

TEST_F(Macro, pollerId) {
  configuration::parser parser;
  configuration::state st;

  std::remove("/tmp/test-config.cfg");

  std::ofstream ofs("/tmp/test-config.cfg");
  ofs << "poller_id=42" << std::endl;
  ofs << "log_file=\"\"" << std::endl;
  ofs.close();

  parser.parse("/tmp/test-config.cfg", st);
  configuration::applier::state::instance().apply(st);

  std::string out;
  nagios_macros mac;
  process_macros_r(&mac, "$POLLERID$", out, 0);
  ASSERT_EQ(out, "42");
}

// Given host configuration without host_id
// Then the applier add_object throws an exception.
TEST_F(Macro, TotalServicesOkZero) {
  std::string out;
  nagios_macros mac;
  process_macros_r(&mac, "$TOTALSERVICESOK$", out, 0);
  ASSERT_EQ(out, "0");
}

// Given host configuration without host_id
// Then the applier add_object throws an exception.
TEST_F(Macro, TotalHostOk) {
  configuration::applier::host hst_aply;
  configuration::service svc;
  configuration::host hst;
  ASSERT_TRUE(hst.parse("host_name", "test_host"));
  ASSERT_TRUE(hst.parse("address", "127.0.0.1"));
  ASSERT_TRUE(hst.parse("_HOST_ID", "12"));
  ASSERT_NO_THROW(hst_aply.add_object(hst));
  ASSERT_EQ(1u, host::hosts.size());
  init_macros();

  nagios_macros mac;
  std::string out;
  host::hosts["test_host"]->set_current_state(host::state_up);
  host::hosts["test_host"]->set_has_been_checked(true);
  process_macros_r(&mac, "$TOTALHOSTSUP$", out, 1);
  ASSERT_EQ(out, "1");
}

// Given host configuration without host_id
// Then the applier add_object throws an exception.
TEST_F(Macro, TotalHostServicesCritical) {
  configuration::applier::host hst_aply;
  configuration::service svc;
  configuration::host hst;
  ASSERT_TRUE(hst.parse("host_name", "test_host"));
  ASSERT_TRUE(hst.parse("address", "127.0.0.1"));
  ASSERT_TRUE(hst.parse("_HOST_ID", "12"));
  ASSERT_NO_THROW(hst_aply.add_object(hst));
  ASSERT_EQ(1u, host::hosts.size());
  init_macros();

  nagios_macros mac;
  std::string out;
  host::hosts["test_host"]->set_current_state(host::state_up);
  host::hosts["test_host"]->set_has_been_checked(true);
  process_macros_r(&mac, "$TOTALHOSTSERVICESCRITICAL:test_host$", out, 1);
  ASSERT_EQ(out, "0");
}

// Given host configuration without host_id
// Then the applier add_object throws an exception.
TEST_F(Macro, TotalHostServicesCriticalError) {
  configuration::applier::host hst_aply;
  configuration::service svc;
  configuration::host hst;
  ASSERT_TRUE(hst.parse("host_name", "test_host"));
  ASSERT_TRUE(hst.parse("address", "127.0.0.1"));
  ASSERT_TRUE(hst.parse("_HOST_ID", "12"));
  ASSERT_NO_THROW(hst_aply.add_object(hst));
  ASSERT_EQ(1u, host::hosts.size());
  init_macros();

  nagios_macros mac;
  std::string out;
  host::hosts["test_host"]->set_current_state(host::state_up);
  host::hosts["test_host"]->set_has_been_checked(true);
  /* The call of this variable needs a host name */
  process_macros_r(&mac, "$TOTALHOSTSERVICESCRITICAL$", out, 1);
  ASSERT_EQ(out, "");
}

TEST_F(Macro, ServiceMacro) {
  configuration::applier::host hst_aply;
  configuration::applier::service svc_aply;
  configuration::service svc;
  configuration::host hst;
  ASSERT_TRUE(hst.parse("host_name", "test_host"));
  ASSERT_TRUE(hst.parse("address", "127.0.0.1"));
  ASSERT_TRUE(hst.parse("_HOST_ID", "12"));
  ASSERT_NO_THROW(hst_aply.add_object(hst));
  ASSERT_EQ(1u, host::hosts.size());
  ASSERT_TRUE(svc.parse("description", "test_svc"));
  ASSERT_TRUE(svc.parse("host_name", "test_host"));
  ASSERT_TRUE(svc.parse("_HOST_ID", "12"));
  ASSERT_TRUE(svc.parse("_SERVICE_ID", "13"));
  // We fake the expand_object
  svc.set_host_id(12);

  configuration::command cmd("cmd");
  cmd.parse("command_line", "echo 'output| metric=12;50;75'");
  svc.parse("check_command", "cmd");
  configuration::applier::command cmd_aply;
  cmd_aply.add_object(cmd);
  ASSERT_NO_THROW(svc_aply.add_object(svc));
  ASSERT_EQ(1u, service::services.size());
  init_macros();

  nagios_macros mac;
  std::string out;
  host::hosts["test_host"]->set_current_state(host::state_up);
  host::hosts["test_host"]->set_has_been_checked(true);
  service::services[std::make_pair("test_host", "test_svc")]->set_plugin_output(
      "foo bar!");
  process_macros_r(&mac, "$SERVICEOUTPUT:test_host:test_svc$", out, 1);
  ASSERT_EQ(out, "foo bar!");
}
