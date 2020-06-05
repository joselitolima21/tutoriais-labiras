// Importando bibliotecas do ros
#define USE_USBCON
#include <ros.h>
#include <std_msgs/String.h>

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
  // Iniciando o nó
  nh.initNode();
   // Assinando o nó que eu criei
  nh.advertise(chatter);
}

void loop()
{
  // Atribuindo a mensagem que vou enviar ao meu tipo de mensagem ros
  str_msg.data = hello;
  // Publicando a mensagem
  chatter.publish( &str_msg );
  // Recebendo todos os retornos
  nh.spinOnce();
  delay(1000);
}
