#include <log.h>

std::ostream *log::out_stream = 0;

std::mutex    log::file_lock;

uint8_t       log::min_level = log::info;

std::set<std::string> log::domains = {
"earpc.api.call",
"earpc.api.respond",
"earpc.process.expiry",
"earpc.process.feedback",
"earpc.process.master",
"earpc.process.recv",
"earpc.process.recv.ack",
"earpc.process.recv.call",
"earpc.process.recv.nak",
"earpc.process.send",
"wic.device.client",
"wic.device.host",
"wicp.commit",
"wicp.property.local",
"wicp.property.remote",
"wicp.sync.local",
"wicp.sync.remote"
};
