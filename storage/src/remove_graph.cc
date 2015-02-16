/*
** Copyright 2012-2013 Merethis
**
** This file is part of Centreon Broker.
**
** Centreon Broker is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Broker is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Broker. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include "com/centreon/broker/io/events.hh"
#include "com/centreon/broker/storage/internal.hh"
#include "com/centreon/broker/storage/remove_graph.hh"

using namespace com::centreon::broker;
using namespace com::centreon::broker::storage;

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  Default constructor.
 */
remove_graph::remove_graph() : id(0), is_index(0) {}

/**
 *  Copy constructor.
 *
 *  @param[in] right Object to copy.
 */
remove_graph::remove_graph(remove_graph const& right)
  : io::data(right) {
  _internal_copy(right);
}

/**
 *  Destructor.
 */
remove_graph::~remove_graph() {}

/**
 *  Assignment operator.
 *
 *  @param[in] right Object to copy.
 *
 *  @return This object.
 */
remove_graph& remove_graph::operator=(remove_graph const& right) {
  if (this != &right) {
    io::data::operator=(right);
    _internal_copy(right);
  }
  return (*this);
}

/**
 *  Get the event type.
 *
 *  @return The event type.
 */
unsigned int remove_graph::type() const {
  return (io::events::data_type<io::events::storage, storage::de_remove_graph>::value);
}

/**************************************
*                                     *
*           Private Methods           *
*                                     *
**************************************/

/**
 *  Copy internal data members.
 *
 *  @param[in] right Object to copy.
 */
void remove_graph::_internal_copy(remove_graph const& right) {
  id = right.id;
  is_index = right.is_index;
  return ;
}

/**************************************
*                                     *
*           Static Objects            *
*                                     *
**************************************/

// Mapping.
mapping::entry const remove_graph::entries[] = {
  mapping::entry(
    &remove_graph::id,
    "id",
    1),
  mapping::entry(
    &remove_graph::is_index,
    "is_end",
    2),
  mapping::entry()
};

// Operations.
static io::data* new_remove_graph() {
  return (new remove_graph);
}
io::event_info::event_operations const remove_graph::operations = {
  &new_remove_graph
};
