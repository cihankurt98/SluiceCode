#include "Door.h"
#include "Watersensor.h"
#include "TrafficLight.h"
#include "HardwareConnection.h"
#include "Sluice.h"

#include <iostream>


static void ShowMenu( void )
{
	std::cerr << ("\n\nMenu\n");
	std::cerr << ("====\n");
	std::cerr << ("(1) CreateConnection Sluice 1\n");
	std::cerr << ("-----------------------\n");
	std::cerr << ("(q) QUIT\n");
	std::cerr << ("Enter: repeat previous choice\n\n");
	std::cerr << ("Choice : ");
}

char GetUserInput(char oldChoice)
{
	char choice = '\0';
	std::cin.get(choice);
	if (choice == 10)
	{
		choice = oldChoice; // repeat previous command
	}
	else
	{
		std::cin.ignore();
	}
	return choice;
}

int main()
{
	char ip[] = {"127.0.0.1"};
	HardwareConnection cHandlerOne(ip, 5555);
	Door door(&cHandlerOne);
	WaterSensor waterSensor(&cHandlerOne);
	TrafficLight trafficLight(&cHandlerOne);
	Sluice sluiceOne(door, waterSensor, trafficLight);
	char messageToBeSent[13] = {"GetDoorLeft;"};

	bool quit = false;
	char oldChoice = '\0';

	while (!quit)
	{
		ShowMenu();
		char choice = GetUserInput(oldChoice);
		oldChoice = choice;

		switch (choice)
		{
		case '1':
		std::cout << door.GetDoorStatus(messageToBeSent, 13) << std::endl;
		break;
		case 'q':
			quit = true;
			break;
		default:
			std::cerr << "Choice not recognized( " << choice  << ")" << std::endl;
			break;
		}
	}
	return 0;
}