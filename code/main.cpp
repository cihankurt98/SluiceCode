#include "Door.h"
#include "Watersensor.h"
#include "TrafficLight.h"
#include "HardwareConnection.h"
#include "Valve.h"
#include "Sluice.h"
#include "EventGenerator.h"

#include <stdlib.h>
#include <iostream>
#include <thread>


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
	Valve valve(tcp);
	Door door(tcp, valve);
	WaterSensor waterSensor(tcp);
	TrafficLight trafficLight(tcp);
	EventGenerator eventGen(door, waterSensor);
 	Sluice sluice(door, waterSensor, trafficLight, eventGen);
	bool quit = false;
	char oldChoice = '\0';

	iUserInterface& UI = eventGen;

	//char tmpmessage[] = {"SetDoorLeft:open;"};
 	//door.SetDoorStatus(tmpmessage);
	std::thread poll (&Sluice::Run, sluice);
	poll.detach();
	while (!quit)
	{
		ShowMenu();
		char choice = GetUserInput(oldChoice);
		oldChoice = choice;

		switch (choice)
		{
		case '1':
			UI.BtnStartPressed();
			break;
		case '2':
			UI.BtnUitvarenPressed();
			break;
		case '3':
           UI.BtnInvarenPressed();
			break;
		case '4':
            //ev = EV_EMERGENCY;
             UI.BtnAlarmPressed();
			break;
		case '5':
            //ev = EV_RESUME;
			UI.BtnResetPressed();
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

