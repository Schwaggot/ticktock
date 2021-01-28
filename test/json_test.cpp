/*
    TickTock is an open-source Time Series Database for your metrics.
    Copyright (C) 2020-2021  Yongtao You (yongtao.you@gmail.com),
    Yi Lin (ylin30@gmail.com), and Yalei Wang (wang_yalei@yahoo.com).

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "json.h"
#include "json_test.h"


using namespace tt;

namespace tt_test
{


void
JsonTests::run()
{
    log("Running %s...", m_name);

    char *json1 = strdup("{\"start\": 1546272099999, \"globalAnnotations\": \"true\", \"end\": 1546273846249, \"msResolution\": \"true\", \"queries\": [{\"downsample\": \"10s-avg-zero\", \"aggregator\": \"none\", \"metric\": \"ml_metric_0\"}]}");
    JsonMap map1;
    JsonParser::parse_map(json1, map1);
    JsonParser::free_map(map1);

    char *json2 = strdup("{\"start\":1571364787563,\"queries\":[{\"metric\":\"2.2.nginx.number_requests_writing\",\"aggregator\":\"avg\",\"rate\":true,\"rateOptions\":{\"counter\":false,\"dropResets\":true},\"downsample\":\"1m-avg\",\"tags\":{\"host\":\"*\"}}],\"msResolution\":false,\"globalAnnotations\":true}");
    JsonMap map2;
    JsonParser::parse_map(json2, map2);
    CONFIRM(map2.find("globalAnnotations") != map2.end());
    CONFIRM(map2.find("globalAnnotations")->second->to_bool());
    CONFIRM(map2.find("msResolution") != map2.end());
    CONFIRM(! map2.find("msResolution")->second->to_bool());
    CONFIRM(map2.find("queries") != map2.end());
    JsonArray& arr = map2.find("queries")->second->to_array();
    CONFIRM(arr.size() == 1);
    JsonMap& m = arr[0]->to_map();
    CONFIRM(m.find("rate") != m.end());
    CONFIRM(m.find("rate")->second->to_bool());
    JsonParser::free_map(map2);

    m_stats.add_passed(1);

    log("Finished %s", m_name);
}


}
