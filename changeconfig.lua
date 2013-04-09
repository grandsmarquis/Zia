if arg[1] == nil then
   print('usage : lua changeconfig.lua pathtoconfig.cfg')
   return
end 
local host, port = "127.0.0.1", 2021
local socket = require 'socket'
local tcp = assert(socket.tcp())

tcp:connect(host, port);
--tcp:send("../defausdfsfdsdflt.cfg");
tcp:send(arg[1]);

io.stdout:flush()
tcp:close()