# Arduino2ArduinoSecureComm
At this project we developed Arduino to Arduino communication with AES-128 encryption. These 2 devices connected with wire and one of them is MasterSender and the other is SlaveReceiver.
Basicly MasterSender takes input from serial monitor. Then seperate this input into parts, each has 16 bytes. After that encrypt these data with AES-128 with predefined key and send to the wire. The SlaveReader takes these data from wire and decrypty with same key. Then Slave device integrate each 16 bytes and generate the original message. 
Note:!!!This code not working properly. It can be send data wrong to wire or read from wire wrongly when you send too much data to the wire.!!

Qsprec & El2fun
