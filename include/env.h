#include <string>

/*
 * static class Env: contain enviroment variables that are shared between components
 */

using namespace std;

class Env {
  public:
    static string DbPath;
};
