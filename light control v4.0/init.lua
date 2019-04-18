
led1 = 3
led2 = 4
gpio.mode(led1, gpio.OUTPUT)
gpio.mode(led2, gpio.OUTPUT)
gpio.write(led1, gpio.HIGH)
gpio.write(led2, gpio.HIGH)

print("Ready to start soft ap")

local str=wifi.ap.getmac();
local ssidTemp=string.format("%s%s%s",string.sub(str,10,11),string.sub(str,13,14),string.sub(str,16,17));

cfg={}
cfg.ssid="ESP8266_"..ssidTemp;
cfg.pwd="12345678"
wifi.ap.config(cfg)

cfg={}
cfg.ip="192.168.1.1";
cfg.netmask="255.255.255.0";
cfg.gateway="192.168.1.1";
wifi.ap.setip(cfg);
wifi.setmode(wifi.SOFTAP)

str=nil;
ssidTemp=nil;
collectgarbage();

print("Soft AP started")
print("Heep:(bytes)"..node.heap());
print("MAC:"..wifi.ap.getmac().."\r\nIP:"..wifi.ap.getip());


srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        local buf = "";
        buf = buf.."HTTP/1.1 200 OK\n\n"
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
        end
        
        if(_GET.pin == "ON1")then
              gpio.write(led1, gpio.LOW);
			  print("led1 on")
        elseif(_GET.pin == "OFF1")then
              gpio.write(led1, gpio.HIGH);
			print("led1 off")
        elseif(_GET.pin == "ON2")then
              gpio.write(led2, gpio.LOW);
			print("led2 on")
        elseif(_GET.pin == "OFF2")then
              gpio.write(led2, gpio.HIGH);
			print("led2 off")
        end
        client:send(buf);
        client:close();
        collectgarbage();
    end)
end)