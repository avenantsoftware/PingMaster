/*
 
  PingMaster project by M.J. Meijer 2014

  Ping phones/tablets of friends in your network, when a phone/tablet is found => send a pushovermessage to your own phone/tablet
  This way you know who is visiting you when they make contact to you wifi network
  Also usefull to see if friends visited you while you where not at home

  You need to give friends a static ip address on your router from the mac address of their phones/tablets

  Parts needed:
  -Arduino Uno http://www.dx.com/p/uno-r3-atmega328p-uno-r3-development-board-deep-blue-285620
  -Ethernet Shield: http://www.dx.com/p/ethernet-shield-with-wiznet-w5100-ethernet-chip-tf-slot-118061

*/

#include <SPI.h>         
#include <Ethernet.h>
#include <ICMPPing.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // mac addres for ethernet shield
byte ip[] = {192,168,2,177}; // ip address for ethernet shield

// Pushover settings
char pushoversite[] = "api.pushover.net";
char apitoken[] = "your30characterapitokenhere123";
char userkey [] = "your30characteruserkeygoeshere";

int length;

// Static IP of phones from friends 
IPAddress Friend1(192,168,2,200);
IPAddress Friend2(192,168,2,201);
IPAddress Friend3(192,168,2,202);
IPAddress Friend4(192,168,2,203);
IPAddress Friend5(192,168,2,204);

// Set variables
boolean friend1po = false;
boolean friend2po = false;
boolean friend3po = false;
boolean friend4po = false;
boolean friend5po = false;
int pingfailed1 = 0;
int pingfailed2 = 0;
int pingfailed3 = 0;
int pingfailed4 = 0;
int pingfailed5 = 0;


SOCKET pingSocket = 0;

char buffer [256];
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));

EthernetClient client;

/********** Setup **********/
void setup() 
{
  // start Ethernet
  Ethernet.begin(mac, ip);
  //Serial.begin(9600);
  delay(2500);
  pushover("The PingMaster server started");
}

/********** Loop **********/
void loop()
{
  pingfriends();
}

/********** Ping telefoons van bekenden **********/
void pingfriends()
{
  ICMPEchoReply echoReply1 = ping(Friend1, 4);
  if (echoReply1.status == SUCCESS)
  {
    if (friend1po == false)
    {
      pushover("Phone from Friend1 detected");
      friend1po = true;
    }
  }
  else if (echoReply1.status != SUCCESS)
  {
    pingfailed1++;
    if (pingfailed1 > 500)
    {
      friend1po = false;
      pingfailed1 = 0;
    }
  } 
  delay(500);
  ICMPEchoReply echoReply2 = ping(Friend2, 4);
  if (echoReply2.status == SUCCESS)
  {
    if (friend2po == false)
    {
      pushover("Phone from Friend2 detected");
      friend2po = true;
    }
  }
  else if (echoReply2.status != SUCCESS)
  {
    pingfailed2++;
    if (pingfailed1 > 500)
    {
      friend2po = false;
      pingfailed2 = 0;
    }
  }  
  delay(500);
  ICMPEchoReply echoReply3 = ping(Friend3, 4);
  if (echoReply3.status == SUCCESS)
  {
    if (friend3po == false)
    {
      pushover("Phone from Friend3 detected");
      friend3po = true;
    }
  }
  else if (echoReply3.status != SUCCESS)
  {
    pingfailed3++;
    if (pingfailed3 > 500)
    {
      friend3po = false;
      pingfailed3 = 0;
    }
  }  
  delay(500);
  ICMPEchoReply echoReply4 = ping(Friend4, 4);
  if (echoReply4.status == SUCCESS)
  {
    if (friend4po == false)
    {
      pushover("Phone from Friend4 detected");
      friend4po = true;
    }
  }
  else if (echoReply4.status != SUCCESS)
  {
    pingfailed4++;
    if (pingfailed4 > 500)
    {
      friend4po = false;
      pingfailed4 = 0;
    }
  }  
  delay(500);
  ICMPEchoReply echoReply5 = ping(Friend5, 4);
  if (echoReply5.status == SUCCESS)
  {
    if (friend5po == false)
    {
      pushover("Phone from Friend5 detected");
      friend5po = true;
    }
  }
  else if (echoReply5.status != SUCCESS)
  {
    pingfailed5++;
    if (pingfailed5 > 500)
    {
      friend5po = false;
      pingfailed5 = 0;
    }
  }  
  delay(500);
}

/********** Send pushover message **********/
byte pushover(char *pushovermessage)
{
  String message = pushovermessage;

  length = 81 + data.length();

  if(client.connect(pushoversite,80))
  {
    client.println("POST /1/messages.json HTTP/1.1");
    client.println("Host: api.pushover.net");
    client.println("Connection: close\r\nContent-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.print(length);
    client.println("\r\n");;
    client.print("token=");
    client.print(apitoken);
    client.print("&user=");
    client.print(userkey);
    client.print("&message=");
    client.print(message);
    client.stop();
  }  
}
