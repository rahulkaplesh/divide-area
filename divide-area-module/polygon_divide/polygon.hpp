#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <node_api.h>
#include "typedef.hpp"

class Polygon {
   public:
      static napi_value Init(napi_env aEnv, napi_value aExports);
      static void Destructor(napi_env aEnv, void* aNativeObject, void* finalize_hint);
   private:
      explicit Polygon();
      ~Polygon();
      static napi_value New(napi_env env, napi_callback_info info);
      static napi_value AddPoint(napi_env env, napi_callback_info info);
      static inline napi_value Constructor(napi_env env);
      static napi_value CheckSimple(napi_env env, napi_callback_info info);

      Polygon_2                   mPoly;
      napi_env                    mEnv{nullptr};
      napi_ref                    mWrapper{nullptr};
};

#endif