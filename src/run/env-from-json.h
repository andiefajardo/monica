/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
Authors:
Michael Berg <michael.berg@zalf.de>

Maintainers:
Currently maintained by the authors.

This file is part of the MONICA model.
Copyright (C) Leibniz Centre for Agricultural Landscape Research (ZALF)
*/

#ifndef MONICA_ENV_FROM_JSON_H
#define MONICA_ENV_FROM_JSON_H

#include <string>

#include "tools/date.h"
#include "run-monica.h"
#include "json11/json11.hpp"
#include "tools/json11-helper.h"

namespace Monica
{
	Tools::EResult<json11::Json> readAndParseJsonFile(std::string path);

	Tools::EResult<json11::Json> parseJsonString(std::string jsonString);

	Env createEnvFromJsonConfigFiles(std::map<std::string, std::string> params);

	json11::Json createEnvJsonFromJsonConfigFiles(std::map<std::string, std::string> params);
}

#endif //MONICA_ENV_FROM_JSON_H
