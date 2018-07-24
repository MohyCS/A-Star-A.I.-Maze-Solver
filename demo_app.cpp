/**
 * @file application.cpp
 *
 * @copyright Software License Agreement (BSD License)
 * Copyright (c) 2013, Rutgers the State University of New Jersey, New Brunswick 
 * All Rights Reserved.
 * For a full description see the file named LICENSE.
 *
 * Authors: Andrew Dobson, Andrew Kimmel, Athanasios Krontiris, Zakary Littlefield, Kostas Bekris
 *
 * Email: pracsys@googlegroups.com
 */

#include "prx/utilities/applications/demo_app.hpp"
#include "prx/utilities/parameters/parameter_reader.hpp"
#include "prx/utilities/definitions/string_manip.hpp"

#include "prx/utilities/communication/tf_broadcaster.hpp"

#include <fstream>
#include "prx/utilities/definitions/sys_clock.hpp"
#include <pluginlib/class_list_macros.h>
#include "prx/utilities/definitions/random.hpp"
#include <boost/assign/list_of.hpp>

PLUGINLIB_EXPORT_CLASS(prx::util::demo_application_t, prx::util::util_application_t)

namespace prx
{

    namespace util
    {

        demo_application_t::demo_application_t()
        {}

        demo_application_t::~demo_application_t()
        {}


    }
}
