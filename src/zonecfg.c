//
// Node.js C binding for illumos/SmartOS's parts of "/usr/include/libzonecfg.h".
//
//
// Dev Notes:
// - "zc_" prefix is used to namespace identifiers in this file.
//

// See examples:
// https://hackernoon.com/n-api-and-getting-started-with-writing-c-addons-for-node-js-cf061b3eae75

// XXX
//#include <errno.h>
//#include <libzonecfg.h>
//#include <zone.h>
//#include <stdlib.h>
//#include <string.h>

#include <libzonecfg.h>

#include <node_api.h>


napi_value zc_zone_get_state(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value argv[1];
    char zone_name[ZONENAME_MAX + 1];
    size_t num_bytes;
    zone_state_t state;
    char *state_str = NULL;
    int err;
    napi_value js_state_str;

    status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "error parsing arguments");
    }
    if (argc !== 1) {
        napi_throw_type_error(env, NULL, "incorrect number of arguments");
    }

    // XXX ZONENAME_MAX length
//XXX
#define ZONENAME_MAX  64
    status = napi_get_value_string_utf8(env, argv[0], zonename, ZONENAME_MAX+1,
        &num_bytes);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "error reading zonename");
    }
//XXX START HERE

    if ((err = zone_get_state(zone_name, &state)) != Z_OK) {
        // XXX how to have string and zonecfg_strerror?
        // XXX return error code?
        //RETURN_EXCEPTION(zonecfg_strerror(ret));
        napi_throw_error(env, NULL, "error reading zonename");
    }

    state_str = zone_state_str(state);
    status = napi_create_string_utf8(env, state_str, NAPI_AUTO_LENGTH,
        &js_state_str);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "error creating string");
    }

    return js_state_str;
}

//v8::Handle<v8::Value> ZoneCfg::GetZoneState(const v8::Arguments &args) {
//  v8::HandleScope scope;
//
//  REQUIRE_STRING_ARG(args, 0, name);
//
//  zone_state_t state;
//  char *statestr = NULL;
//
//  if (int ret = zone_get_state(*name, &state)) {
//    RETURN_EXCEPTION(zonecfg_strerror(ret));
//  }
//  statestr = zone_state_str(state);
//
//  return v8::String::New(statestr);
//}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    // libzonecfg.zone_get_state
    // XXX Arguments 2 and 3 are function name and length respectively
    status = napi_create_function(env, NULL, 0, zc_zone_get_state, NULL, &fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "error creating func");
    }
    status = napi_set_named_property(env, exports, "zone_get_state", fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "error setting prop");
    }

    //NODE_SET_METHOD(target, "getZoneState", GetZoneState);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
