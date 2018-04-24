/*
 * @file    MQTT_JS.h
 * @author  ST
 * @version V1.0.0
 * @date    9 October 2017
 * @brief   Implementation of MQTT for Javascript.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef _MQTT_JS_H_
#define _MQTT_JS_H_

/* Includes ------------------------------------------------------------------*/

#include "mbed.h"
#include "TCPSocket.h"
#include "MQTTClient.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"

#include "NetworkInterface_JS.h"

#include "jerryscript-mbed-library-registry/wrap_tools.h"

#include <ctype.h>

/* Constants -----------------------------------------------------------------*/

#define MQTT_MAX_PACKET_SIZE 250
#define MQTT_MAX_PAYLOAD_SIZE 300

#define MAX_SSID_LEN   80
#define MAX_PASSW_LEN  80

#define HTTP_BROKER_URL "http://customer.cloudmqtt.com/login"

typedef void (* subscribeCallbackType)(MQTT::MessageData & msgMQTT);

/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of MQTT for Javascript.
 */
class MQTT_JS{    
private:    
    char ssid[MAX_SSID_LEN];
    char seckey[MAX_PASSW_LEN]; 

    char id[32];
    char topic[32];
    char auth_token[32];
    char hostname[128];
    char port[16];

    int connack_rc; // MQTT connack return code
    char* ip_addr;
    char type[30];
    bool netConnecting;
    int connectTimeout;
    bool mqttConnecting;
    bool netConnected;
    bool connected;
    int retryAttempt;
    char subscription_url[300];
    MQTT::Client<MQTTNetwork, Countdown, MQTT_MAX_PACKET_SIZE>* client;
    MQTTNetwork* mqttNetwork;

    static jerry_value_t onSubscribeCallback;

public:

    /* Constructors */
    MQTT_JS();
    
    /* Destructors */
    ~MQTT_JS();

    /* Functions */
    
    NetworkInterface* getNetworkInterface();

    int onSubscribe(jerry_value_t cb);
    int onDisconnect(jerry_value_t cb, subscribeCallbackType fn);

    static void subscribe_cb(MQTT::MessageData & msgMQTT);

    int init(NetworkInterface* network, char* _id, char* _token, char* _url, char* _port);

    int connect();

    int subscribe(char *pubTopic);

    int unsubscribe(char *pubTopic);

    int connect(NetworkInterface* network);

    int getConnTimeout(int attemptNumber);

    void attemptConnect(NetworkInterface* network) ;

    int publish(char* buf, int n = 0);

    int yield(int time);

    int start_mqtt(NetworkInterface* network);
};

#endif