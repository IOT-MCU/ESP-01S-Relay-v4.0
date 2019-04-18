function xxd(filename)
  file.open(filename, "r")
  buf =  file.read()
  file.close()
  print('Downloading '..#buf..' bytes')
  sum = 0
  for byte=1, #buf do
     uart.write(0,string.format('%02X ',buf:byte(byte)))
     sum = sum + tonumber(buf:byte(byte),10)
     if byte%16 == 0 then print(sum) sum = 0 end
     tmr.wdclr()
  end
  print('\nEOF EOF EOF '..sum)
end
