#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  void getArea(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  void getMax(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  void getMin(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
}

#endif

