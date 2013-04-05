local host, port = "127.0.0.1", 3030
local socket = require 'socket'
local tcp = assert(socket.tcp())

tcp:connect(host, port);

tcp:send("he         l              lo w             orld\n");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("END\n");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("fksljsdlkjfl::ksdj::lfkjsdlfjsdklfskdfsd");
tcp:send("END\n");
while true do
    local s, status, partial = tcp:receive()
    print(s or partial)
    if status == "closed" then break end
end

tcp:close()