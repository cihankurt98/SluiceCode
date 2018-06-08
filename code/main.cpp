#include "Door.h"
#include "Watersensor.h"
#include "TrafficLight.h"
#include "HardwareConnection.h"
#include "Valve.h"
#include "Sluice.h"


#include <stdlib.h>
#include <iostream>


static void ShowMenu( void )
{
	std::cerr << ("\n\nMenu\n");
	std::cerr << ("====\n");
	std::cerr << ("(1) Start\n");
	std::cerr << ("(2) Vrijgeven voor uitvaren\n");
	std::cerr << ("(3) Vrijgeven voor invaren\n");
	std::cerr << ("(4) Alarm\n");
	std::cerr << ("(5) Reset\n");
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

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Do this: ./sluice [PORT]" << std::endl;
		return 0;
	}
	std::cout << argv[1] << std::endl;
	char ip[] = {"127.0.0.1"};
	int port = atoi(std::string(argv[1]).c_str());


	HardwareConnection tcp(ip, port);
	Door door(tcp);
	WaterSensor waterSensor(tcp);
	TrafficLight trafficLight(tcp);
 	Sluice sluiceOne(door, waterSensor, trafficLight);


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
			/*
			1)De sluiswachter beslist of de sluis geschut wordt, hij heeft hiervoor per sluis een knop “start”.
			2)De geopende deuren van sluis, daar waar de waterstand aan beide zijden gelijk is, worden dan
			gesloten.
			3)Kwamen de boten van de hoogwaterkant, dan worden kleppen in de laagwaterdeuren open gez
			et zodat het water in de sluis zakt tot het laagwaterniveau. Vervolgens worden de deuren aan
			laagwaterzijde geopend.
			4)Kwamen de boten van de laagwaterkant, dan worden de kleppen in de hoogwaterdeuren
			opengezet zodat het water in de sluis stijgt tot het hoog
			water niveau.*/
			break;
		case '2':
			//std::cout << door.GetDoorStatus(messageToBeSent, 19) << std::endl;
			break;
		case '3':
			//std::cout << door.GetDoorStatus(messageToBeSent, 19) << std::endl;
			break;
		case '4':
			//std::cout << door.GetDoorStatus(messageToBeSent, 19) << std::endl;
			break;
		case '5':
			//std::cout << door.GetDoorStatus(messageToBeSent, 19) << std::endl;
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

