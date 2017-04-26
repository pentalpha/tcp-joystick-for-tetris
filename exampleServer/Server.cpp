#include "Server.h"

Server::Server(){
  sizeAddressClient = sizeof(struct sockaddr);
  msg = new char[MAXMSG+1];
  /*
   * Configurações do endereço
  */
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(PORTNUM);
  //address.sin_addr.s_addr = INADDR_ANY;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
}

bool Server::start(){
  if(getSocket() == false){
    return false;
  }
  if(doBind() == false){
    return false;
  }
  if(startListening() == false){
    return false;
  }
  return true;
}

bool Server::getSocket(){
  /*
   * Criando o Socket
   *
   * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
   * PARAM2: SOCK_STREAM ou SOCK_DGRAM
   * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente
  */
  socketId = socket(AF_INET, SOCK_STREAM, 0);
  //Verificar erros
  if (socketId == -1)
  {
      std::cout << "Failed to create socket()\n";
      return false;
  }
  return true;
}

bool Server::doBind(){
  //Conectando o socket a uma porta. Executado apenas no lado servidor
  if (bind (socketId, (struct sockaddr *)&address, sizeof(struct sockaddr)) == -1)
  {
    std::cout << "Failed to bind() a port\n";
    return false;
  }else{
    return true;
  }
}

bool Server::startListening(){
  //Habilitando o servidor a receber conexoes do cliente
  if (listen( socketId, 10 ) == -1)
  {
      std::cout << "Failed to listen()\n";
      return false;
  }else{
      return true;
  }
}

void Server::waitForClientAndReceive(){
  //servidor ficar em um loop infinito
  std::cout << "Server: waiting for client connections\n";

  //Servidor fica bloqueado esperando uma conexão do cliente
  connectionClientId = accept( socketId,(struct sockaddr *) &addressClient,&sizeAddressClient );

  std::cout << "Server: received connection from " << inet_ntoa(addressClient.sin_addr) << "\n";

  //Verificando erros
  if ( connectionClientId == -1)
  {
      std::cout << "Failed to accept()\n";
      return;
  }
  while(1){
    //receber uma msg do cliente
    std::cout << "Server waiting for a message...\n";
    bytesread = recv(connectionClientId,msg,MAXMSG,0);
    if (bytesread == -1)
    {
        std::cout << "Failed to recv()";
        break;
    }
    else if (bytesread == 0)
    {
        std::cout << "Client finished connection\n";
        break;
    }
    //Inserir o caracter de fim de mensagem
    msg[bytesread] = '\0';
    std::cout << "Servidor recebeu a seguinte msg do cliente: " << msg << "\n";
    //close(connectionClientId);
  }
  close(connectionClientId);
}
