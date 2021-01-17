#include "polygon.hpp"
#include <assert.h>

#define DECLARE_NAPI_METHOD(name, func) {name, 0, func, 0, 0, 0, napi_default, 0}

template<typename keyType, typename valueType>
std::pair<keyType, valueType> get_max(const std::multimap<keyType, valueType>& x) {
   using pairtype=std::pair<keyType, valueType>;
   return *std::max_element(x.begin(), x.end(), [](const pairtype& p1, const pairtype& p2) {
      return p1.first < p2.first;
   });
}

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
      DECLARE_NAPI_METHOD("checkSimple", CheckSimple),
      DECLARE_NAPI_METHOD("checkConvex", CheckConvex),
      DECLARE_NAPI_METHOD("dividePolygon", DividePolygon),
      DECLARE_NAPI_METHOD("longestSideBisector", GetLongestSideBisector),
   };
   napi_value cons;
   status = napi_define_class(
      aEnv, "Polygon", NAPI_AUTO_LENGTH, New, nullptr, 5, properties, &cons);
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

   double latitude;
   status = napi_get_value_double(env, value[0], &latitude);
   double longitude;
   status = napi_get_value_double(env, value[1], &longitude);
   assert(status == napi_ok);

   obj->mPoly.push_back(Point_2(latitude, longitude));

   return nullptr;
}

napi_value Polygon::CheckSimple(napi_env env, napi_callback_info info) {
   napi_status status;

   napi_value jsthis;
   status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
   assert(status == napi_ok);

   Polygon* obj;
   status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
   assert(status == napi_ok);

   bool ok = obj->mPoly.is_simple();

   napi_value valueToBeReturned;
   status = napi_get_boolean(env, ok, &valueToBeReturned);
   assert(status == napi_ok);

   return valueToBeReturned;
}

napi_value Polygon::CheckConvex(napi_env env, napi_callback_info info) {
   napi_status status;

   napi_value jsthis;
   status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
   assert(status == napi_ok);

   Polygon* obj;
   status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
   assert(status == napi_ok);

   bool ok = obj->mPoly.is_convex();

   napi_value valueToBeReturned;
   status = napi_get_boolean(env, ok, &valueToBeReturned);
   assert(status == napi_ok);

   return valueToBeReturned;
}

napi_value Polygon::DividePolygon(napi_env env, napi_callback_info info) {
   napi_status status;

   size_t argc = 1;
   napi_value value[1];
   napi_value jsthis;
   status = napi_get_cb_info(env, info, &argc, value, &jsthis, nullptr);
   assert(status == napi_ok);

   Polygon* obj;
   status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
   assert(status == napi_ok);

   int64_t numberOfParts;
   status = napi_get_value_int64(env, value[0], &numberOfParts);
   assert(status == napi_ok);

   std::cout << "I am goiing to launch a divison operation dividing polygon into " << numberOfParts << std::endl ;

   bool ok = obj->launchDivison(numberOfParts);
   napi_value valueToBeReturned;
   status = napi_get_boolean(env, ok, &valueToBeReturned);
   assert(status == napi_ok);
   return valueToBeReturned;
}

napi_value Polygon::GetLongestSideBisector(napi_env env, napi_callback_info info) {
   napi_status status;

   napi_value jsthis;
   status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
   assert(status == napi_ok);

   Polygon* obj;
   status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
   assert(status == napi_ok);

   napi_value startPoint;
   status = napi_create_object(env, &startPoint);
   assert(status == napi_ok);

   napi_value valueToAdd;
   status = napi_create_double(env, obj->mLongestBisector.source().x(), &valueToAdd);
   assert(status == napi_ok);

   status = napi_set_named_property(env, startPoint, "latitude", valueToAdd);
   assert(status == napi_ok);

   status = napi_create_double(env, obj->mLongestBisector.source().y(), &valueToAdd);
   assert(status == napi_ok);

   status = napi_set_named_property(env, startPoint, "longitude", valueToAdd);
   assert(status == napi_ok);

   napi_value endPoint;
   status = napi_create_object(env, &endPoint);
   assert(status == napi_ok);

   status = napi_create_double(env, obj->mLongestBisector.target().x(), &valueToAdd);
   assert(status == napi_ok);

   status = napi_set_named_property(env, endPoint, "latitude", valueToAdd);
   assert(status == napi_ok);

   status = napi_create_double(env, obj->mLongestBisector.target().y(), &valueToAdd);
   assert(status == napi_ok);

   status = napi_set_named_property(env, endPoint, "longitude", valueToAdd);
   assert(status == napi_ok);

   napi_value objectToBeReturned;
   status = napi_create_object(env, &objectToBeReturned);
   assert(status == napi_ok);

   status = napi_set_named_property(env, objectToBeReturned, "StartPoint", startPoint);
   assert(status == napi_ok);

   status = napi_set_named_property(env, objectToBeReturned, "EndPoint", endPoint);
   assert(status == napi_ok);

   status = napi_create_double(env, obj->mLengthLongBisect, &valueToAdd);
   assert(status == napi_ok);

   status = napi_set_named_property(env, objectToBeReturned, "LengthOfBisector", valueToAdd);
   assert(status == napi_ok);

   return objectToBeReturned;
}

bool Polygon::launchDivison(int64_t aNumberOfParts) {
   bool ok = true;
   ok &= findLongestSideBisector();
   return ok;
}

bool Polygon::findLongestSideBisector() {
   try {
      std::multimap<double, Segment_2> lenBisectorMap;
      Segment_2 sideBisector;
      for(EdgeIterator edge1 = mPoly.edges_begin(); edge1 != mPoly.edges_end(); ++edge1) {
         for(EdgeIterator edge2 = mPoly.edges_begin(); edge2 != mPoly.edges_end(); ++edge2) {
            if(*edge1 != *edge2) {
               sideBisector = getBisector(*edge1, *edge2);
               lenBisectorMap.insert(std::pair<double, Segment_2>(std::sqrt(sideBisector.squared_length()), sideBisector));
            }
         }
      }
      auto bisectorLenPair = get_max(lenBisectorMap);
      mLengthLongBisect = bisectorLenPair.first;
      mLongestBisector = bisectorLenPair.second;
      return true;
   } catch(std::exception ex) {
      std::cout << ex.what();
      return false;
   }
}

Segment_2 Polygon::getBisector(Segment_2 edge1, Segment_2 edge2) {
   Point_2 mid_Point1 = CGAL::midpoint(edge1.start(), edge1.end());
   Point_2 mid_Point2 = CGAL::midpoint(edge2.start(), edge2.end());
   return Segment_2(mid_Point1,mid_Point2);
}