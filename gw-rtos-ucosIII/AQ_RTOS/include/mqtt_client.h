#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H



extern void mqtt_init(Mqtt *mqtt);

extern void on_connect(Mqtt *mqtt, void *data, int state);
extern void on_connack(Mqtt *mqtt, void *data, int rc);
extern void on_publish(Mqtt *mqtt, void *data, int msgid);
extern void on_puback(Mqtt *mqtt, void *data, int msgid);
extern void on_pubrec(Mqtt *mqtt, void *data, int msgid);
extern void on_pubrel(Mqtt *mqtt, void *data, int msgid);
extern void on_pubcomp(Mqtt *mqtt, void *data, int msgid);
extern void on_subscribe(Mqtt *mqtt, void *data, int msgid);
extern void on_unsubscribe(Mqtt *mqtt, void *data, int msgid);
extern void on_unsuback(Mqtt *mqtt, void *data, int msgid);
extern void on_pingreq(Mqtt *mqtt, void *data, int id);
extern void on_pingresp(Mqtt *mqtt, void *data, int id);
extern void on_disconnect(Mqtt *mqtt, void *data, int id);
extern void on_message(Mqtt *mqtt, MqttMsg *msg);
extern void on_suback(Mqtt *mqtt, void *data, int msgid);


extern void set_callbacks(Mqtt *mqtt);

extern void client_init();
extern void client_read(aeEventLoop *el, int fd, void *clientdata, int mask);
extern void client_open();
extern void client_setup();
extern int  client_cron(aeEventLoop *el, long long id, void *clientData);
extern void client_prepare();




#endif
