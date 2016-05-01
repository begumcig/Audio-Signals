#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "strutils.h"
#include "nfd.h"
#include <stdio.h>
#include <stdlib.h>








int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 400), "Recorder");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	sf::SoundBufferRecorder recorder;
	sf::SoundBuffer record;
	sf::Sound sound;
	int recCount44 = 0; // the variables that hold the number of records corresponding to their sampling frequencies.
	int recCount22 = 0;
	int recCount11 = 0;
	int recCount50 = 0;
	bool last1 = false; //when playing the sounds we have to know which sample rated audio we are using.
	bool last2 = false;
	bool last3 = false;
	bool last4 = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//button ekle

			if (event.type == sf::Event::KeyPressed &&(event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Num4)) // if the 1,2,3 or 4 key is pressed start recording (at 44100, 22050, 11025, 5012Hz)
			{
				if(event.key.code == sf::Keyboard::Num1)
				{
					if (sf::SoundBufferRecorder::isAvailable()) //if recording is available start recording.
					{
						recorder.start(44100);
						recCount44++;	
					}
				}

				else if(event.key.code == sf::Keyboard::Num2)
				{
					if (sf::SoundBufferRecorder::isAvailable())
					{
						recorder.start(22050);
						recCount22++;
					}
				}

				else if(event.key.code == sf::Keyboard::Num3)
				{
					if (sf::SoundBufferRecorder::isAvailable()) //if recording is available start recording.
					{
						recorder.start(11025);
						recCount11++;
					}
				}

				else if(event.key.code == sf::Keyboard::Num4)
				{
					if (sf::SoundBufferRecorder::isAvailable()) //if recording is available start recording.
					{
						recorder.start(5012);
						recCount50++;
					}
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if(event.key.code == sf::Keyboard::Num1)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount44); //return the string equivalent of reccount 
					buffer.saveToFile("recording 44100 - " + count + ".wav");
					last1 = true;
					last2 = false;
					last3 = false;
					last4 = false;
				}

				else if(event.key.code == sf::Keyboard::Num2)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount22); //return the string equivalent of reccount 
					buffer.saveToFile("recording 22050 - " + count + ".wav");
					last1 = false;
					last2 = true;
					last3 = false;
					last4 = false;
				}
				else if(event.key.code == sf::Keyboard::Num3)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount11); //return the string equivalent of reccount 
					buffer.saveToFile("recording 11025 - " + count + ".wav");
					last1 = false;
					last2 = false;
					last3 = true;
					last4 = false;
				}
				else if(event.key.code == sf::Keyboard::Num4)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount50); //return the string equivalent of reccount 
					buffer.saveToFile("recording 5012 - " + count + ".wav");
					last1 = false;
					last2 = false;
					last3 = false;
					last4 = true;
				}

			}

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{

				if(last1)
				{
					string count = itoa(recCount44);
					if (!record.loadFromFile("recording 44100 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;

					else
					{

						sound.setBuffer(record);
						sound.play();
					}
				}

				else if(last2)
				{
					string count = itoa(recCount22);
					if (!record.loadFromFile("recording 22050 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;

					else
					{

						sound.setBuffer(record);
						sound.play();
					}
				}

				else if(last3)
				{
					string count = itoa(recCount11);
					if (!record.loadFromFile("recording 11025 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;

					else
					{

						sound.setBuffer(record);
						sound.play();
					}
				}

				else if(last4)
				{
					string count = itoa(recCount50);
					if (!record.loadFromFile("recording 5012 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;

					else
					{

						sound.setBuffer(record);
						sound.play();
					}
				}

				else
				{
					cout << "No file has been recorded yet." << endl;
				}		
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
			{
				nfdchar_t *outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("wav", NULL, &outPath );

				if ( result == NFD_OKAY ) 
				{
					puts("Success!");
					puts(outPath);
					free(outPath);
				}
				else if ( result == NFD_CANCEL ) 
				{
					puts("User pressed cancel.");
				}
				else 
				{
					printf("Error: %s\n", NFD_GetError() );
				}


			}




		}

		window.clear();
		window.display();
	}

	return 0;
}