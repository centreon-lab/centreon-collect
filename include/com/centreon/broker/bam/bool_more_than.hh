/*
** Copyright 2014 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#ifndef CCB_BAM_BOOL_MORE_THAN_HH
#define CCB_BAM_BOOL_MORE_THAN_HH

#include "com/centreon/broker/bam/bool_binary_operator.hh"
#include "com/centreon/broker/namespace.hh"

CCB_BEGIN()

namespace bam {
/**
 *  @class bool_or bool_or.hh "com/centreon/broker/bam/bool_or.hh"
 *  @brief OR operator.
 *
 *  In the context of a KPI computation, bool_or represents a logical
 *  OR between two bool_value.
 */
class bool_more_than : public bool_binary_operator {
 public:
  bool_more_than(bool strict = false);
  bool_more_than(bool_more_than const& right);
  ~bool_more_than();
  bool_more_than& operator=(bool_more_than const& right);
  double value_hard();
  double value_soft();

 private:
  bool _strict;
};
}  // namespace bam

CCB_END()

#endif  // !CCB_BAM_BOOL_MORE_THAN_HH
