g++ hello.cpp -I ../../../MQTTClient/src -I ../../../MQTTPacket/src -I ../../src/linux ../../../MQTTPacket/src/MQTTPacket.c ../../../MQTTPacket/src/MQTTDeserializePublish.c ../../../MQTTPacket/src/MQTTConnectClient.c ../../../MQTTPacket/src/MQTTSubscribeClient.c ../../../MQTTPacket/src/MQTTSerializePublish.c ../../../MQTTPacket/src/MQTTUnsubscribeClient.c -L"/usr/lib/gcc/x86_64-linux-gnu/4.8" -lgcc -lstdc++ -L"/usr/lib/x86_64-linux-gnu" -lm -ldl -lcrypt -lc -lrt  -o hello


