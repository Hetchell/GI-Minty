#include "../includes.h"
#include <fstream>
#include <filesystem>
#include <optional>
#include "TelemetryBlocker.h"

// Function that allows unindenting a string. This will be used by the telemetry blocking code.
// See https://stackoverflow.com/a/24900770
std::string unindent(const char* p)
{
    std::string result;
    if (*p == '\n') ++p;
    const char* p_leading = p;
    while (std::isspace(*p) && *p != '\n')
        ++p;
    size_t leading_len = p - p_leading;
    while (*p)
    {
        result += *p;
        if (*p++ == '\n')
        {
            for (size_t i = 0; i < leading_len; ++i)
                if (p[i] != p_leading[i])
                    goto dont_skip_leading;
            p += leading_len;
        }
    dont_skip_leading:;
    }
    return result;
}

// Reads a file.
// https://stackoverflow.com/a/116220
auto read_file(std::string_view path) -> std::string {
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    if (not stream) {
        throw std::ios_base::failure("File does not exist");
    }

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(&buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

void TelemetryBlocker::BlockTelemetry() {
    // Blocks miHoYo telemetry domains in /etc/hosts to avoid detection.
    std::string hostsText = unindent(R"(
    # These domains have been added to your /etc/hosts file by the M cheat to prevent miHoYo from recording telemetry data about you.
    # Aside from being an egregious privacy violation, telemetry data can be used for bans.
    # Please *do not* modify or remove this text.

    # miHoYo tracking & logging servers
    0.0.0.0 uspider.yuanshen.com
    0.0.0.0 overseauspider.yuanshen.com
    0.0.0.0 log-upload-os.hoyoverse.com
    0.0.0.0 log-upload.mihoyo.com
    0.0.0.0 log-upload-os.mihoyo.com
    0.0.0.0 log-upload-eur.mihoyo.com
    0.0.0.0 devlog-upload.mihoyo.com
    0.0.0.0 devlog-upload-os.mihoyo.com
    0.0.0.0 hk4e-uspider.mihoyo.com
    0.0.0.0 paizicnqa.yuanshen.com
    0.0.0.0 minor-api-os.hoyoverse.com
    0.0.0.0 usa01-appsflyer-report.honkaiimpact3.com
    0.0.0.0 www.uspider.yuanshen.com
    0.0.0.0 www.overseauspider.yuanshen.com
    0.0.0.0 www.log-upload-os.hoyoverse.com
    0.0.0.0 www.log-upload.mihoyo.com
    0.0.0.0 www.log-upload-os.mihoyo.com
    0.0.0.0 www.log-upload-eur.mihoyo.com
    0.0.0.0 www.devlog-upload.mihoyo.com
    0.0.0.0 www.devlog-upload-os.mihoyo.com
    0.0.0.0 www.hk4e-uspider.mihoyo.com
    0.0.0.0 www.paizicnqa.yuanshen.com
    0.0.0.0 www.minor-api-os.hoyoverse.com
    0.0.0.0 www.usa01-appsflyer-report.honkaiimpact3.com

    # Unity engine tracking servers
    0.0.0.0 prd-lender.cdp.internal.unity3d.com
    0.0.0.0 thind-prd-knob.data.ie.unity3d.com
    0.0.0.0 thind-gke-usc.prd.data.corp.unity3d.com
    0.0.0.0 cdp.cloud.unity3d.com
    0.0.0.0 remote-config-proxy-prd.uca.cloud.unity3d.com
    0.0.0.0 www.prd-lender.cdp.internal.unity3d.com
    0.0.0.0 www.thind-prd-knob.data.ie.unity3d.com
    0.0.0.0 www.thind-gke-usc.prd.data.corp.unity3d.com
    0.0.0.0 www.cdp.cloud.unity3d.com
    0.0.0.0 www.remote-config-proxy-prd.uca.cloud.unity3d.com
    )");

    // If this string already exists in /etc/hosts, we aren't going to edit /etc/hosts again.
    // If we really need to add/remove domains to this list in a new version (unlikely), we can implement the necessary code to do that then.
    // I don't want to plan for hypothetical issues when we have a finite amount of time.
    std::string deduplicationString = "cheat to prevent miHoYo from recording telemetry data about you.";

    // https://stackoverflow.com/a/23967977
    // https://stackoverflow.com/a/9740368
    std::string hostsFilename = "C:\\Windows\\System32\\drivers\\etc\\hosts";
    std::fstream appendFileToWorkWith;

    appendFileToWorkWith.open(hostsFilename, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!appendFileToWorkWith)
    {
        // If this block is reached, the hosts file does not exist
        util::log(M_Debug, "You don't have a C:\\Windows\\System32\\drivers\\etc\\hosts file. M will create one to block miHoYo telemetry and prevent bans.");
        appendFileToWorkWith.open(hostsFilename, std::fstream::in | std::fstream::out | std::fstream::trunc);
        appendFileToWorkWith << hostsText;
        appendFileToWorkWith.close();
    }
    else
    {
        // If this block is reached, the hosts file exists

        // We need to make sure we haven't already edited /etc/hosts. We don't want to clog the user's /etc/hosts file.
        // If we haven't edited it, we addd data to it.
        if (read_file(hostsFilename).find(deduplicationString) != std::string::npos) {
            util::log(M_Debug,"You have a C:\\Windows\\System32\\drivers\\etc\\hosts file, but it doesn't have the lines needed for blocking miHoYo telemetry. M will now append text to it.");
            appendFileToWorkWith << hostsText;
        }

        // Close file regardless of what operations took place (leaving files open unnecessarily can cause security and performance issues iirc)
        appendFileToWorkWith.close();
    }
}

