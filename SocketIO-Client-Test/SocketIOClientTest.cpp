// SocketIOClientTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Boolean used to check for connection
bool connected = false;
std::string URI = "http://127.0.0.1:3000";

//On connected function
void OnConnected()
{
	//we are connected!
	std::cout << "Connected to server " << std::endl;
	connected = true;
}

//On Message recieved
void OnMessage(sio::event &ev)
{
	//Lets just print out
	std::cout << "Recieved Message " << ev.get_message()->get_string() << std::endl;
}

int main()
{
	//Create Socket IO Client
	sio::client h;
	//Connect to the given URI
	h.connect(URI);
	
	//bind an open listener
	h.set_open_listener(std::bind(&OnConnected));
	//Bind function for message events
	h.socket()->on("message", &OnMessage);

	//Check to see if connection is live!
	while (!connected)
	{
		//Spin out a message
		std::cout << "Waiting for connection" << std::endl;
	}
	//We are sending a message to get a response from the server
	std::string message = "hello";
	//Emit a chat message to the server
	h.socket()->emit("chat", message);
	
	//Get a key press
	std::cin.get();

	return 0;
}

