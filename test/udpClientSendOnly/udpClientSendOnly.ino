#include <EtherCard.h>

static byte mymac[] = { 0x1A,0x2B,0x3C,0x4D,0x5E,0x6F };
static byte myip[] = { 10,10,10,3 };
static byte mask[] = { 255,255,255,0 };
static byte gwip[] = { 10,10,10,2 };

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "192.168.0.4";
const int dstPort PROGMEM = 4096;

const int srcPort PROGMEM = 4096;

void setup () {
  Serial.begin(9600);
  Serial.println( "Init...");
  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println( "Failed to access Ethernet controller");
  if (!ether.dhcpSetup())
   Serial.println("DHCP failed");
 // ether.staticSetup(myip, gwip, NULL, mask);
   
   
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  
  ether.parseIp(ether.hisip, "192.168.0.255");
  ether.printIp("SRV: ", ether.hisip);
}

char textToSend[] = "Sii mary.. ganeee!!";

void loop () {
    if (millis() > timer) {
      timer = millis() + 5000;
     //static void sendUdp (char *data,uint8_t len,uint16_t sport, uint8_t *dip, uint16_t dport);
     ether.sendUdp(textToSend, sizeof(textToSend), srcPort, ether.hisip, dstPort );
     Serial.println("Mensaje enviado con exito :)");
  }
}
