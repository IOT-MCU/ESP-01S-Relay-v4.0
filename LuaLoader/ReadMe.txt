Lua Loader is a helper application for the Lua implementation on the esp8266 by NodeMCU

1. run LuaLoader.exe
2. Use the Tools menu to get and install NodeMCU Lua on your ESP
3. Set the LuaLoader comm port to COMx 9600 8-N-1
4. Test with your chip - you should get the > prompt

LLbin.lua should be in the same folder as LuaLoader.exe for binary uploads
xxd.lua   should be in the same folder as LuaLoader.exe for binary downloads

Feedback via http://www.benlo.com/comments.html



Examples

Some examples of working code is included. Most are from the esp8266.com forum.

Beware that as the Lua firmware changed, some of the examples may only work with a particular firmware build.

Count interrupts. Typical use of the GPIO port to count pulses of any kind.

A web client

A One Wire temperature sensor implementation

Google time look up from HEAD information

Monitoring a GPIO input

Scan for I2C devices

Servo control by UDP

Auto Connect to the strongest open AP visible



LuaLoader is freeware.

The MIT License (MIT)

Copyright (c) 2015 Peter Jennings benlo.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

