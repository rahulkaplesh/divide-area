/* cppsrc/main.cpp */
#include <napi.h>
#include "./polygon_divide/polygon.hpp"

napi_value InitAll(napi_env env, napi_value exports) {
  return Polygon::Init(env, exports);
}

NAPI_MODULE(DividePolygon, InitAll)