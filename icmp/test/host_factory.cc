/*
** Copyright 2011-2012 Merethis
**
** This file is part of Centreon Connector ICMP.
**
** Centreon Connector ICMP is free software: you can redistribute it
** and/or modify it under the terms of the GNU Affero General Public
** License as published by the Free Software Foundation, either version
** 3 of the License, or (at your option) any later version.
**
** Centreon Connector ICMP is distributed in the hope that it will be
** useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Affero General Public License for more details.
**
** You should have received a copy of the GNU Affero General Public
** License along with Centreon Connector ICMP. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/connector/icmp/host.hh"

using namespace com::centreon::connector::icmp;

/**
 *  Delete hosts memory.
 *
 *  @param[in, out] lst  The hosts list.
 */
static void cleanup_hosts(std::list<host*> const& lst) {
  for (std::list<host*>::const_iterator
         it(lst.begin()), end(lst.end());
       it != end;
       ++it)
    delete *it;
}

/**
 *  Check host factory with empty parameter.
 *
 *  @return True on sucess, otherwise false.
 */
static bool empty_argument() {
  try {
    std::list<host*> hosts;
    host::factory("", hosts);
    cleanup_hosts(hosts);
  }
  catch (std::exception const& e) {
    (void)e;
    return (true);
  }
  return (false);
}

/**
 *  Check host constructor.
 *
 *  @return 0 on success.
 */
int main() {
  int ret(0);
  try {
    if (!empty_argument())
      throw (basic_error() << "invalid factory with empty name");

    std::list<host*> hosts;
    host::factory("localhost", hosts);
    if (hosts.empty())
      throw (basic_error() << "invalid factory with localhost");
    unsigned int addr(hosts.front()->get_address());
    std::string addr_str(host::address_to_string(addr));
    cleanup_hosts(hosts);
    if (std::string(addr_str) != "127.0.0.1")
      throw (basic_error() << "invalid factory with localhost");

    hosts.clear();
    host::factory("127.0.0.1", hosts);
    if (hosts.empty())
      throw (basic_error() << "invalid factory with 127.0.0.1");
    addr = hosts.front()->get_address();
    addr_str = host::address_to_string(addr);
    cleanup_hosts(hosts);
    if (addr_str != "127.0.0.1")
      throw (basic_error() << "invalid factory with 127.0.0.1");
  }
  catch (std::exception const& e) {
    std::cerr << "error: " << e.what() << std::endl;
    ret = 1;
  }
  return (ret);
}
