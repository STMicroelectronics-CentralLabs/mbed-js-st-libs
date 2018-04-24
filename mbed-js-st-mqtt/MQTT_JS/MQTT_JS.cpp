/*
 * @file    MQTT_JS.cpp
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


/* Includes ------------------------------------------------------------------*/

#include "MQTT_JS.h"

/** onSubscribeCallback
 * @brief	onSubscribeCallback.
 */
jerry_value_t MQTT_JS::onSubscribeCallback;

/** Constructor
 * @brief	Constructor.
 */
MQTT_JS::MQTT_JS(){
    connack_rc = 0; // MQTT connack return code
    ip_addr = NULL;
    netConnecting = false;
    connectTimeout = 1000;
    mqttConnecting = false;
    netConnected = false;
    connected = false;
    retryAttempt = 0;

    client = NULL;
    mqttNetwork = NULL;
    
    onSubscribeCallback = NULL;
    
}

/** Destructor
 * @brief	Destructor.
 */
MQTT_JS::~MQTT_JS(){
    if(client){
        delete client;
        client = NULL;
    }
    if(mqttNetwork){
        delete mqttNetwork;
        mqttNetwork = NULL;
    }
}

/** subscribe_cb
 * @brief	Connects the subscription callback.
 * @param	Message Data
 */
void MQTT_JS::subscribe_cb(MQTT::MessageData & msgMQTT) {
    char msg[MQTT_MAX_PAYLOAD_SIZE];
    msg[0]='\0';
    strncat (msg, (char*)msgMQTT.message.payload, msgMQTT.message.payloadlen);
    //printf ("--->>> subscribe_cb msg: %s\n\r", msg);

    if (onSubscribeCallback && jerry_value_is_function(onSubscribeCallback)) {
        
        jerry_value_t this_val = jerry_create_undefined ();
        const jerry_value_t args[1] = {
            jerry_create_string ((const jerry_char_t *)msg)
            //jerry_create_number(3)
        };

        jerry_value_t ret_val = jerry_call_function (onSubscribeCallback, this_val, args, 1);

        if (!jerry_value_has_error_flag (ret_val))
        {
            // handle return value
        }
        jerry_release_value(args[0]);

        jerry_release_value (ret_val);
        jerry_release_value (this_val);
        
    }
}

/** onSubscribe
 * @brief	Calls the subscription callback.
 * @param	Jerry Callback
 * @return  Return code
 */
int MQTT_JS::onSubscribe(jerry_value_t cb){
    
    if (jerry_value_is_function(cb)) {
        onSubscribeCallback = cb;
        return 0;
    }
    return 1;
}

/** subscribe
 * @brief	Subscribes to the topic.
 * @param	Topic
 * @return  Return code
 */
int MQTT_JS::subscribe (char *_topic)
{
    strcpy(topic, _topic);
    if(!topic){
        return 1; // invalid topic
    }
    return client->subscribe(topic, MQTT::QOS1, subscribe_cb);
}

/** unsubscribe
 * @brief	Unsubscribes the callback
 * @param	Topic
 * @return  Return code
 */
int MQTT_JS::unsubscribe(char *pubTopic)
{
    return client->unsubscribe(pubTopic);
}


/** init
 * @brief	Initializes the MQTT.
 * @param	NetworkInterface
 * @param	ID
 * @param	Token
 * @param	URL
 * @param	Port
 * @return  Return code
 */
int MQTT_JS::init(NetworkInterface* network, char* _id, char* _token, char* _url, char* _port)
{
    sprintf (id, "%s", _id);
    sprintf (auth_token, "%s", _token);
    sprintf (hostname, "%s", _url);
    sprintf (subscription_url, "%s", _url);
    sprintf (port, "%s", _port);
    
    if (!network) {
        printf ("Error easy_connect\n\r");
        return -1;
    }

    mqttNetwork = new MQTTNetwork(network);
    
    client = new MQTT::Client<MQTTNetwork, Countdown, MQTT_MAX_PACKET_SIZE>(*mqttNetwork);

    return 0;
}

/** connect
 * @brief	Connects to the MQTT Server.
 * @param	NetworkInterface
 * @return  Return code
 */
int MQTT_JS::connect(NetworkInterface* network)
{    
    netConnecting = true;
    int rc = mqttNetwork->connect(hostname, atoi(port));
    if (rc != 0)
    {
        //WARN("IP Stack connect returned: %d\n", rc);    
        return rc;
    }
    printf ("--->TCP Connected\n\r");
    netConnected = true;
    netConnecting = false;

    // MQTT Connect
    mqttConnecting = true;
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 4;
    data.struct_version=0;
    data.clientID.cstring = id;
    data.username.cstring = id;
    data.password.cstring = auth_token;
    data.keepAliveInterval = 15;  // in Sec    
    if ((rc = client->connect(data)) == 0) 
    {       
        connected = true;
        printf ("--->MQTT Connected\n\r");     
    }
    else {
        WARN("MQTT connect returned %d\n", rc);        
    }
    if (rc >= 0)
        connack_rc = rc;
    mqttConnecting = false;
    return rc;
}

/** getConnTimeout
 * @brief	Returns the timeout in seconds.
 * @param	Attempt number
 * @return  Return code
 */
int MQTT_JS::getConnTimeout(int attemptNumber)
{
    // First 10 attempts try within 3 seconds, next 10 attempts retry after every 1 minute
    // after 20 attempts, retry every 10 minutes
    return (attemptNumber < 10) ? 3 : (attemptNumber < 20) ? 60 : 600;
}

/** attemptConnect
 * @brief	Attempt connection to MQTT server.
 * @param	NetworkInterface
 */
void MQTT_JS::attemptConnect(NetworkInterface* network) 
{
    connected = false;
        
    while (connect(network) != MQTT_CONNECTION_ACCEPTED) 
    {    
        if (connack_rc == MQTT_NOT_AUTHORIZED || connack_rc == MQTT_BAD_USERNAME_OR_PASSWORD) {
            printf ("File: %s, Line: %d Error: %d\n\r",__FILE__,__LINE__, connack_rc);        
            return; // don't reattempt to connect if credentials are wrong
        } 
        int timeout = getConnTimeout(++retryAttempt);
        WARN("Retry attempt number %d waiting %d\n", retryAttempt, timeout);
        
        // if ipstack and client were on the heap we could deconstruct and goto a label where they are constructed
        //  or maybe just add the proper members to do this disconnect and call attemptConnect(...)
        
        // this works - reset the system when the retry count gets to a threshold
        if (retryAttempt == 5)
            NVIC_SystemReset();
        else
            wait(timeout);
    }
}

/** publish
 * @brief	Publishes to the MQTT broker.
 * @param	Data
 * @param	Optional: retry number
 * @return  Return code
 */
int MQTT_JS::publish(char* buf, int n)
{
    MQTT::Message message;
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buf;
    message.payloadlen = strlen(buf);
    
    //LOG("Publishing %s\n\r", buf);
    int result =  client->publish(topic, message);
    if(result != 0){
        if(n < 2){
            printf("\33[31mCould not publish message. Trying again...\33[0m\n");
            return publish(buf, n+1);
        }
        else{
            printf("\33[31mError publishing message!\33[0m\n");
            return result;
        }
    }
    
    /*
    if(result == 0){
        client->yield(5000);  // allow the MQTT client to receive messages
    }
    */
    return result;
} 


/** yield
 * @brief	Waits for the MQTT broker for subscription callback.
 * @param	Time to wait
 * @return  Return code
 */
int MQTT_JS::yield(int time)
{
    client->yield(time);  // allow the MQTT client to receive messages
    return 0;
} 
    
/** start_mqtt
 * @brief	Starts a demo for MQTT.
 * @param	NetworkInterface
 * @return  Return code
 */
int MQTT_JS::start_mqtt(NetworkInterface* network)
{   
    sprintf (id, "hsojbpev");
    sprintf (auth_token, "4H5vbg1KAhYi");
    sprintf (hostname, "m20.cloudmqtt.com");
    sprintf (subscription_url, "m20.cloudmqtt.com");
    sprintf (port, "10023");

    if (!network) {
        printf ("Error easy_connect\n\r");
        return -1;
    }

    mqttNetwork = new MQTTNetwork(network);
    
    client = new MQTT::Client<MQTTNetwork, Countdown, MQTT_MAX_PACKET_SIZE>(*mqttNetwork);

    attemptConnect(network);   
    if (connack_rc == MQTT_NOT_AUTHORIZED || connack_rc == MQTT_BAD_USERNAME_OR_PASSWORD)    
    {
        while (true)
        wait(1.0); // Permanent failures - don't retry
    }
    
    int count = 0;    
    while (true)
    {
        if (++count == 6)
        {               
            // Publish a message every ~3 second
            if (publish((char*)"TestTest") != 0) { 
                attemptConnect(network);   // if we have lost the connection                
            }
            count = 0;
        }        
        client->yield(500);  // allow the MQTT client to receive messages
    }
}
