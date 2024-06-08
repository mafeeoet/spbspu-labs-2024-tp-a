#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>
#include "stream_guard.hpp"
#include "polygon.hpp"
#include "commands.hpp"
#include "implementation_cmds.hpp"

int main(int argc, char ** argv)
{
  using namespace lopatina;
  if (argc < 2)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "No such file\n";
    return 1;
  }
  std::vector<Polygon> figures;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator<Polygon>{input},
      std::istream_iterator<Polygon>{},
      std::back_inserter(figures)
    );
    if (!input && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::map<std::string, std::function<void(std::istream &, std::ostream &)>> cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(lopatina::areaCmd, figures, _1, _2);
    cmds["MAX"] = std::bind(lopatina::maxCmd, figures, _1, _2);
    cmds["MIN"] = std::bind(lopatina::minCmd, figures, _1, _2);
    cmds["COUNT"] = std::bind(lopatina::countCmd, figures, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
/*
  std::copy(
    std::begin(figures),
    std::end(figures),
    std::ostream_iterator<Polygon>(std::cout, "\n")
  );
*/
  return 0;
}
