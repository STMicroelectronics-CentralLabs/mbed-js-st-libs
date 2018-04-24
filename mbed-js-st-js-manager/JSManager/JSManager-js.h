#ifndef _JS_MANAGER_JS_H
#define _JS_MANAGER_JS_H

#include "jerryscript-mbed-library-registry/wrap_tools.h"

DECLARE_CLASS_CONSTRUCTOR(JSManager);

DECLARE_JS_WRAPPER_REGISTRATION (JSManager_library)
{
    REGISTER_CLASS_CONSTRUCTOR(JSManager);
}
#endif // _JS_MANAGER_JS_H
