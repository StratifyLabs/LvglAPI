
#include <signal.h>

#include "UnitTest.hpp"

#define VERSION "0.1"
#include "sys/Cli.hpp"

void segfault(int a) { API_ASSERT(false); }

int main(int argc, char *argv[]) {
  sys::Cli cli(argc, argv);

#if defined __link
  signal(11, segfault);
#endif

  printer::Printer printer;

  printer.set_verbose_level(cli.get_option("verbose"));

  test::Test::initialize(test::Test::Initialize()
                           .set_name(cli.get_name())
                           .set_version(VERSION)
                           .set_git_hash(SOS_GIT_HASH)
                           .set_printer(&printer));

  { UnitTest(cli.get_name()).execute(cli); }

  test::Test::finalize();

  exit(test::Test::final_result() == false);

  return 0;
}
