#include "polygon.hpp"
#include <assert.h>

#define DECLARE_NAPI_METHOD(name, func) {name, 0, func, 0, 0, 0, napi_default, 0}

Polygon::Polygon() {}

Polygon::~Polygon() 
{
   napi_delete_reference(mEnv, mWrapper);
}

void Polygon::Destructor(napi_env aEnv, void *aNativeObject, void*)
{
   reinterpret_cast<Polygon*>(aNativeObject)->~Polygon();
}

napi_value Polygon::Init(napi_env aEnv, napi_value aExports)
{
   napi_status status;
   napi_property_descriptor properties[] = {
      DECLARE_NAPI_METHOD("addPoint", AddPoint),
   };
   napi_value cons;
   status = napi_define_class(
      aEnv, "Polygon", NAPI_AUTO_LENGTH, New, nullptr, 1, properties, &cons);
   assert(status == napi_ok);
   napi_ref* constructor = new napi_ref;
   status = napi_create_reference(aEnv, cons, 1, constructor);
   assert(status == napi_ok);
   status = napi_set_instance_data(
      aEnv,
      constructor,
      [](napi_env env, void* data, void* hint) {
        napi_ref* constructor = static_cast<napi_ref*>(data);
        napi_status status = napi_delete_reference(env, *constructor);
        assert(status == napi_ok);
        delete constructor;
      },
      nullptr);
   assert(status == napi_ok);
   status = napi_set_named_property(aEnv, aExports, "Polygon", cons);
   assert(status == napi_ok);
   return aExports;
}

napi_value Polygon::Constructor(napi_env env) {
   void* instance_data = nullptr;
   napi_status status = napi_get_instance_data(env, &instance_data);
   assert(status == napi_ok);
   napi_ref* constructor = static_cast<napi_ref*>(instance_data);

   napi_value cons;
   status = napi_get_reference_value(env, *constructor, &cons);
   assert(status == napi_ok);
   return cons;
}

napi_value Polygon::New(napi_env env, napi_callback_info info) {
   napi_status status;

   napi_value target;
   status = napi_get_new_target(env, info, &target);
   assert(status == napi_ok);
   bool is_constructor = target != nullptr;

   if (is_constructor) {
      // Invoked as constructor: `new MyObject(...)`
      size_t argc = 0;
      //napi_value args[1];
      napi_value jsthis;
      status = napi_get_cb_info(env, info, &argc, 0, &jsthis, nullptr);
      assert(status == napi_ok);

      //double value = 0;

      //napi_valuetype valuetype;
      //status = napi_typeof(env, args[0], &valuetype);
      //assert(status == napi_ok);

      //f (valuetype != napi_undefined) {
      //  status = napi_get_value_double(env, args[0], &value);
      //  assert(status == napi_ok);
      //

      Polygon* obj = new Polygon();

      obj->mEnv = env;
      status = napi_wrap(env,
                         jsthis,
                         reinterpret_cast<void*>(obj),
                         Polygon::Destructor,
                         nullptr,  // finalize_hint
                         &obj->mWrapper);
      assert(status == napi_ok);

      return jsthis;
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    //size_t argc_ = 1;

    //status = napi_get_cb_info(env, info, &argc_, args, nullptr, nullptr);
    //assert(status == napi_ok);

   const size_t argc = 0;

   napi_value instance;
   status = napi_new_instance(env, Constructor(env), argc, 0, &instance);
   assert(status == napi_ok);
   return instance;
  }
}

napi_value Polygon::AddPoint(napi_env env, napi_callback_info info) {
   napi_status status;

   size_t argc = 2;
   napi_value value[2];
   napi_value jsthis;
   status = napi_get_cb_info(env, info, &argc, value, &jsthis, nullptr);
   assert(status == napi_ok);

   Polygon* obj;
   status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
   assert(status == napi_ok);

   double _value1;
   status = napi_get_value_double(env, value[0], &_value1);
   double _value2;
   status = napi_get_value_double(env, value[1], &_value2);
   assert(status == napi_ok);

   return nullptr;
}