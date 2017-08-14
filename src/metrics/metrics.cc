#include <string>
#include "metrics.h"
#include "loc.h"
#include "files.h"
#include "cppinclusions.h"
#include "cppinclusions.h"
extern "C" {
#include "util/log.h"
}


namespace oonalysis::metrics {

void main_metrics(const std::string& metric)
{
    if (metric == "loc") {
        main_loc();
    } else if (metric == "files") {
        main_files();
    } else if (metric == "cppinclusions") {
        main_cppinclusions();
    } else {
        LOG(CRITICAL, "Unknown metric");
    }
}

} // namespace oonalysis::metrics
