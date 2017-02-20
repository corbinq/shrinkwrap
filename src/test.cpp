
#include "xzbuf.hpp"
#include <fstream>

#include <iostream>

int main(int argc, char* argv[])
{
  std::string data = "Some text to compress.";
  oxzbuf obuf("test.xz");
  std::ostream os(&obuf);
  os.write(data.data(), data.size());
  os.flush();


  ixzbuf sbuf("xzbuf.hpp.xz");
  std::istream is(&sbuf);

  std::array<char, 64> tmp;
  is.seekg(-7, std::ios::end);
  auto p = is.tellg();
  is.read(tmp.data(), 7);
  is.seekg(p, std::ios::beg);
  while (is)
  {
    is.read(tmp.data(), tmp.size());
    std::cout << std::string(tmp.data(), is.gcount());
  }

  std::cout.flush();

  return 0;
}
