// Copyright (c) 2017, Xiaomi, Inc.  All rights reserved.
// This source code is licensed under the Apache License Version 2.0, which
// can be found in the LICENSE file in the root directory of this source tree.

#include "info_collector_app.h"
#include "pegasus_counter_updater.h"

#include <dsn/dist/replication.h>
#include <dsn/dist/replication/replication_other_types.h>

#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef __TITLE__
#undef __TITLE__
#endif
#define __TITLE__ "info.collector.app"

namespace pegasus {
namespace server {

info_collector_app::info_collector_app(dsn_gpid pid) : service_app(pid), _updater_started(false) {}

info_collector_app::~info_collector_app() {}

::dsn::error_code info_collector_app::start(int argc, char **argv)
{
    pegasus_counter_updater::instance().start();
    _updater_started = true;

    _collector.start();
    _detector.start();
    return ::dsn::ERR_OK;
}

::dsn::error_code info_collector_app::stop(bool cleanup)
{
    if (_updater_started) {
        pegasus_counter_updater::instance().stop();
    }

    _collector.stop();
    _detector.stop();
    return ::dsn::ERR_OK;
}
}
} // namespace
