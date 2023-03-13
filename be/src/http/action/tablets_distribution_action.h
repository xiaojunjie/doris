// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <stdint.h>

#include <string>

#include "http/http_handler_with_auth.h"
#include "util/easy_json.h"

namespace doris {
class HttpRequest;

class ExecEnv;

// Get BE tablets distribution info from http API.
class TabletsDistributionAction : public HttpHandlerWithAuth {
public:
    TabletsDistributionAction(ExecEnv* exec_env);

    ~TabletsDistributionAction() override = default;

    void handle(HttpRequest* req) override;

    EasyJson get_tablets_distribution_group_by_partition(uint64_t partition_id);

    std::string host() { return _host; }

private:
    std::string _host;

    bool on_privilege(const HttpRequest& req, TCheckAuthRequest& auth_request) override {
        auth_request.priv_ctrl.priv_hier = TPrivilegeHier::GLOBAL;
        auth_request.priv_type = TPrivilegeType::ADMIN;
        return true;
    }
};
} // namespace doris
