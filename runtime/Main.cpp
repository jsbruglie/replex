#include <RePlex.h>
#include <Test.h>

#include <iostream>

int main()
{
  TestModule::LoadLibrary();
  std::cout << "foo(1) == " << TestModule::Foo(1) << std::endl;
  std::cout << "bar == " << TestModule::GetBar() << std::endl;

  std::cout << "Make some changes, recompile, and press enter." << std::flush;
  while(std::cin.get() != '\n') {}

  TestModule::ReloadLibrary();
  std::cout << "foo(1) == " << TestModule::Foo(1) << std::endl;
  std::cout << "bar == " << TestModule::GetBar() << std::endl;
  return 0;
}
