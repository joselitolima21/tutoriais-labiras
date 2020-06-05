// Importando bibliotecas do ros e esp8266
#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>

// Configurando conexão com a rede WiFi
const char* ssid     = "Thebook";
const char* password = "Catapimbas06A@";
// Configurando o IP e porta do socket do rosserial
IPAddress server(192,168,0,107);
const uint16_t serverPort = 11411;

// Instanciando o manipulador de nós
ros::NodeHandle nh;

// Criando minha variável com o tipo de mensagem
std_msgs::String str_msg;

// Criando o publisher com um nome de "chatter"
ros::Publisher chatter("chatter", &str_msg);

// Criando minha mensagem que será enviada
char hello[13] = "hello world!";

void setup()
{
  // Iniciando o serial monitor e printndo o status da conexão com a rede
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Conectando o nodeMCU ao wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  // Conectando com o socket do rosserial
  nh.getHardware()->setConnection(server, serverPort);
  
  // Iniciando o nó
  nh.initNode();
   // Assinando o nó que eu criei
  nh.advertise(chatter);
}

void loop()
{
  if (nh.connected()) {
    Serial.println("Connected");
    // Atribuindo a mensagem que vou enviar ao meu tipo de mensagem ros
    str_msg.data = hello;
    // Publicando a mensagem
    chatter.publish( &str_msg );
  } else {
    Serial.println("Not Connected");
  }
  // Recebendo todos os retornos
  nh.spinOnce();
  delay(1000);
}
