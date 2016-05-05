#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include "strutils.h"
#include "nfd.h"
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <string>

int main()
{
	cout << "Software by Elif Begum Cig" << endl << "For any questions email bcig@sabanciuniv.edu." << endl
		<< "Any recorded file is automaticly saved." << endl << "Recordings are made at 16 bits but you can convert it to 8 bits." << endl;

	sf::RenderWindow window(sf::VideoMode(1340, 390), "Recorder"); 
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	sf::SoundBufferRecorder recorder;
	sf::SoundBuffer record;
	sf::SoundBuffer waver;
	sf::Sound sound;
	sf::RectangleShape rectangle;//for the waveform.
	sf::Font font;
	sf::Clock playtime;
	sf::Clock playtime1;


	if (!font.loadFromFile("OpenSans-Regular.ttf"))
	{
		cout << "Could not load the font file." << endl;
	}

	int recCount44 = 0; // the variables that hold the number of records corresponding to their sampling frequencies.
	int recCount22 = 0;
	int recCount11 = 0;
	int recCount50 = 0;
	bool last1 = false; //when playing the sounds we have to know which sample rated audio we are using.
	bool last2 = false;
	bool last3 = false;
	bool last4 = false;
	vector <int> ycor;
	bool bpause = false;
	bool bplay = false;
	sf::Time duration = sf::seconds(18000);
	sf::Time interval = sf::seconds(0);

	// some UI elements.
	sf::Text record1;
	record1.setFont(font);
	record1.setString("Hold 1 to record at 44100 Hz.");
	record1.setColor(sf::Color::White);
	record1.setPosition(20, 20);
	record1.setCharacterSize(17);

	sf::Text record2;
	record2.setFont(font);
	record2.setString("Hold 2 to record at 22100 Hz.");
	record2.setColor(sf::Color::White);
	record2.setPosition(20, 40);
	record2.setCharacterSize(17);

	sf::Text record3;
	record3.setFont(font);
	record3.setString("Hold 3 to record at 11050 Hz.");
	record3.setColor(sf::Color::White);
	record3.setPosition(20,60);
	record3.setCharacterSize(17);

	sf::Text record4;
	record4.setFont(font);
	record4.setString("Hold 4 to record at 5012 Hz.");
	record4.setColor(sf::Color::White);
	record4.setPosition(20, 80);
	record4.setCharacterSize(17);

	sf::Text rec;
	rec.setFont(font);
	rec.setPosition(1200, 30);
	rec.setCharacterSize(22);

	sf::Text opent;
	opent.setFont(font);
	opent.setString("O - Open File");
	opent.setColor(sf::Color::White);
	opent.setPosition(1150, 330);
	opent.setCharacterSize(17);

	sf::Text playt;
	playt.setFont(font);
	playt.setString("P - Play last recording");
	playt.setColor(sf::Color::White);
	playt.setPosition(1150, 350);
	playt.setCharacterSize(17);

	sf::Text pause;
	pause.setFont(font);
	pause.setString("Space - Play/Pause");
	pause.setColor(sf::Color::White);
	pause.setPosition(600, 20);
	pause.setCharacterSize(17);


	sf::Text playpauset;
	playpauset.setFont(font);
	playpauset.setColor(sf::Color::Red);
	playpauset.setPosition(630, 39);
	playpauset.setCharacterSize(20);

	sf::Text bit8t;
	bit8t.setFont(font);
	bit8t.setColor(sf::Color::White);
	bit8t.setString("Press 8 to convert to 8 bit.");
	bit8t.setPosition(20, 345);
	bit8t.setCharacterSize(17);




	//the main loop.
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// the part for recording at different sampling frequencies. The key 1 -> 44100hz, 2-> 22050hz, 3-> 11025hz and 4->5012hz.
			if (event.type == sf::Event::KeyPressed &&(event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Num4)) // if the 1,2,3 or 4 key is pressed start recording (at 44100, 22050, 11025, 5012Hz)
			{
				rec.setString("Recording...");
				rec.setColor(sf::Color::White);

				if(event.key.code == sf::Keyboard::Num1)
				{
					if (sf::SoundBufferRecorder::isAvailable()) //if recording is available start recording.
					{
						recorder.start(44100);
						recCount44++;	//this will be used for naming the files whlist savin.
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
					if (sf::SoundBufferRecorder::isAvailable()) 
					{
						recorder.start(11025);
						recCount11++;
					}
				}

				else if(event.key.code == sf::Keyboard::Num4)
				{
					if (sf::SoundBufferRecorder::isAvailable()) 
					{
						recorder.start(5012);
						recCount50++;
					}
				}
			}

			//what to do when the pressed keys are let go.
			if (event.type == sf::Event::KeyReleased)
			{
				rec.setString("");
				if(event.key.code == sf::Keyboard::Num1)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount44); //return the string equivalent of the number of recordings which has been done at 44100hz.
					buffer.saveToFile("recording 44100 - " + count + ".wav");
					last1 = true; //the last recording was made at 44100hz.
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
					string count = itoa(recCount22); //return the string equivalent of the number of recordings which has been done at 22050hz.
					buffer.saveToFile("recording 22050 - " + count + ".wav");
					last1 = false;
					last2 = true; //the last recording was made at 22050hz.
					last3 = false;
					last4 = false;
				}
				else if(event.key.code == sf::Keyboard::Num3)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount11); //return the string equivalent of the number of recordings which has been done at 11025hz.
					buffer.saveToFile("recording 11025 - " + count + ".wav");
					last1 = false;
					last2 = false;
					last3 = true; //the last recording was made at 11025 hz.
					last4 = false;
				}
				else if(event.key.code == sf::Keyboard::Num4)
				{
					recorder.stop();
					// Get the buffer containing the captured audio data
					const sf::SoundBuffer& buffer = recorder.getBuffer();
					// Save it to a file
					string count = itoa(recCount50); //return the string equivalent of the number of recordings which has been done at 5012hz.
					buffer.saveToFile("recording 5012 - " + count + ".wav");
					last1 = false;
					last2 = false;
					last3 = false;
					last4 = true; //the last recording mas done in 5012hz.
				}

			}

			//time condition to make play pause option available
			//in sfml a clock starts as soon as it is contructed, therefore some precautions should be taken for play/pause to work properly.
			//playtime is the first clock and it only holds true iff the user never presses play/pause.
			//since playtime also counts when the audio pauses, playtime1 resets when the audio plays again and its value is incremented in interval.
			//since playtime1 resets when the audio starts, we should make sure that it can start. bpause is true when audio pauses and false when it starts.
			if(playtime.getElapsedTime() >= duration && playtime1.getElapsedTime() + interval >= duration && bpause==false)
			{
				bplay = false;
				playpauset.setString("");
				sf::Time sec0 = sf::seconds(0);
				interval = sec0;
			}

			//the part about playing pausing the audio
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && bplay == true)
			{
				if(bpause)
				{
					sound.play();
					playtime1.restart(); //playtime1 begins to count again, next time the value will be incremented in "interval".
					bpause = false;
					playpauset.setString("");
					
				}
				else
				{
					sound.pause();
					bpause = true;
					interval += playtime1.getElapsedTime();
					playpauset.setString("Paused");
				}

			}

			//the part for playing the last recording that has been made.
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{

				if(last1) // the bool variable for checking whether the last recording wa made at 44100hz.
				{
					string count = itoa(recCount44);
					if (!record.loadFromFile("recording 44100 - " + count + ".wav")) //load file.
						cout <<"File could not be loaded." << endl;
					else
					{
						sound.setBuffer(record);
						sound.play();
						playtime.restart();
						playtime1.restart();
						duration = record.getDuration();
						bplay = true;
						bpause = false;
						playpauset.setString("");
					

						const sf::Int16* samples = record.getSamples(); //gets the address of the first sample
						std::size_t count = record.getSampleCount(); //gets the sample count.

						//getting the values to draw the waveform.
						int max = -1000000000; //it should be fairly small so it shouldn't effect the results.
						ycor.clear();

						for(int i= 0; i<count; i++)
						{
							//cout << *samples;
							int ratio = count / 650; //how many samples per pixel on the screen.

							if(i % ratio == 0) //at each iteration of the radio we want to display the maximum value as the wave form.
							{
								if(i != 0) //since when i=0, max = -1000000.
								{
									ycor.push_back(-(max/200)+200);  // some changes to make it look good on the screen.
									//cout << max << endl;
								}

								max = *samples;
							}
							else if(abs(*samples) >= max) //if the sample value is larger then the max value it should be the new maximum.
								max = *samples;
							samples++; // the next memory location.
						}
					}


				}

				else if(last2) //the bool variable for checking whether the last recording wa made at 22050hz.
				{
					string count = itoa(recCount22);
					if (!record.loadFromFile("recording 22050 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;
					else
					{
						sound.setBuffer(record);
						sound.play();
						playtime.restart();
						playtime1.restart();
						sf::Time sec0 = sf::seconds(0);
						interval = sec0;
						duration = record.getDuration();
						bplay = true;
						bpause = false;
						playpauset.setString("");

						const sf::Int16* samples = record.getSamples(); //gets the address of the first sample
						std::size_t count = record.getSampleCount(); //gets the sample count.

						//getting the values to draw the waveform.
						int max = -1000000000; //it should be fairly small so it shouldn't effect the results.
						ycor.clear();

						for(int i= 0; i<count; i++)
						{
							//cout << *samples;
							int ratio = count / 650; //how many samples per pixel on the screen.

							if(i % ratio == 0) //at each iteration of the radio we want to display the maximum value as the wave form.
							{
								if(i != 0) //since when i=0, max = -1000000.
								{
									ycor.push_back(-(max/200)+200);  // some changes to make it look good on the screen.
									//cout << max << endl;
								}

								max = *samples;
							}
							else if(abs(*samples) >= max) //if the sample value is larger then the max value it should be the new maximum.
								max = *samples;
							samples++; // the next memory location.
						}
					}
				}

				else if(last3) //last recording = 11025.
				{
					string count = itoa(recCount11);
					if (!record.loadFromFile("recording 11025 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;
					else
					{
						sound.setBuffer(record);
						sound.play();
						playtime.restart();
						playtime1.restart();
						duration = record.getDuration();
						bplay = true;
						bpause = false;
						playpauset.setString("");

						const sf::Int16* samples = record.getSamples(); //gets the address of the first sample
						std::size_t count = record.getSampleCount(); //gets the sample count.

						//getting the values to draw the waveform.
						int max = -1000000000; //it should be fairly small so it shouldn't effect the results.
						ycor.clear();

						for(int i= 0; i<count; i++)
						{
							//cout << *samples;
							int ratio = count / 650; //how many samples per pixel on the screen.

							if(i % ratio == 0) //at each iteration of the radio we want to display the maximum value as the wave form.
							{
								if(i != 0) //since when i=0, max = -1000000.
								{
									ycor.push_back(-(max/200)+200);  // some changes to make it look good on the screen.
									//cout << max << endl;
								}

								max = *samples;
							}
							else if(abs(*samples) >= max) //if the sample value is larger then the max value it should be the new maximum.
								max = *samples;
							samples++; // the next memory location.
						}
					}
				}

				else if(last4) //last recording = 5012.
				{
					string count = itoa(recCount50);
					if (!record.loadFromFile("recording 5012 - " + count + ".wav"))
						cout <<"File could not be loaded." << endl;
					else
					{
						sound.setBuffer(record);
						sound.play();
						playtime.restart();
						playtime1.restart();
						duration = record.getDuration(),
						bplay = true;
						bpause = false;
						playpauset.setString("");

						const sf::Int16* samples = record.getSamples(); //gets the address of the first sample
						std::size_t count = record.getSampleCount(); //gets the sample count.

						//getting the values to draw the waveform.
						int max = -1000000000; //it should be fairly small so it shouldn't effect the results.
						ycor.clear();

						for(int i= 0; i<count; i++)
						{
							//cout << *samples;
							int ratio = count / 650; //how many samples per pixel on the screen.

							if(i % ratio == 0) //at each iteration of the radio we want to display the maximum value as the wave form.
							{
								if(i != 0) //since when i=0, max = -1000000.
								{
									ycor.push_back(-(max/200)+200);  // some changes to make it look good on the screen.
									//cout << max << endl;
								}

								max = *samples;
							}
							else if(abs(*samples) >= max) //if the sample value is larger then the max value it should be the new maximum.
								max = *samples;
							samples++; // the next memory location.
						}

					}
				}

				else
				{
					cout << "No file has been recorded yet." << endl; // to avoid problems.
				}		
			}

			//the part for opening an audio file from the file directories.
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
			{
				nfdchar_t *outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("wav, ogg", NULL, &outPath ); // open dialog returs NFD_OKAY if the user did some action succesfully. 
				//waw, ogg is the filter I applied on he file dialog and the outhpath variable is the file's directory which is passed as a reference.

				if ( result == NFD_OKAY ) //if the user tried to open a file.
				{
					string out = outPath;
					if(!record.loadFromFile(out))
						cout << "File could not be loaded." << endl;
					else
					{
						sound.setBuffer(record);
						sound.play();
						playtime.restart();
						playtime1.restart();
						duration = record.getDuration(),
							bplay = true;

						const sf::Int16* samples = record.getSamples(); //gets the address of the first sample
						std::size_t count = record.getSampleCount(); //gets the sample count.
						waver.loadFromSamples(&samples[0], count, 1, record.getSampleRate()); //transform it into mono.
						//cout << count << endl;

						//getting the values to draw the waveform.
						int max = -1000000000; //it should be fairly small so it shouldn't effect the results.
						ycor.clear();

						for(int i= 0; i<count; i++)
						{
							//cout << *samples;
							int ratio = count / 650; //how many samples per pixel on the screen.

							if(i % ratio == 0) //at each iteration of the radio we want to display the maximum value as the wave form.
							{
								if(i != 0) //since when i=0, max = -1000000.
								{
									ycor.push_back(-(max/200)+200);  // some changes to make it look good on the screen.
									//cout << max << endl;
								}

								max = *samples;
							}
							else if(abs(*samples) >= max) //if the sample value is larger then the max value it should be the new maximum.
								max = *samples;
							samples++; // the next memory location.
						}
					}

				}
				else if ( result == NFD_CANCEL ) //if the user gave up on doing something.
				{
					puts("User pressed cancel.");
				}
				else 
				{
					cout << NFD_GetError();
				}
			}


			//for reducing 16 bit file to 8 bit file.
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num8)
			{
				//again the file directories.
				nfdchar_t *outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("wav, ogg", NULL, &outPath );

				if ( result == NFD_OKAY ) 
				{
					string out = outPath;
					
					if(!record.loadFromFile(out))
						cout << "File could not be loaded." << endl;
					else
					{
						const sf::Int16* samples = record.getSamples(); //gets the address of the first sample
						std::size_t count = record.getSampleCount(); //gets the sample count.
						sf::Int16 * ussamples = new sf::Int16 [count]; //the 8 bit version of the samples. I used sf::Int16 since sfml audio format is strictly that one.

						for(int i = 0; i<count; i++)
						{
							ussamples[i] = samples[i] & 0xFF00; //since the 8 bit audio is losing 16 bit audio's least significant bit parts i used a mask.
							//IMPORTANT: the reason i didn't use shift right operation was due to the fact that in most of samples the audio doesn't exceed a value around 4000.
							//therefore using right shifting made my samples so small that they were insignificant.
							//I first used an approach of converting signed16 to unsigned16 to unsigned8. But the results were not good. So I used this method.
						}

						//getting the values to draw the waveform.
						int max = -1000000000; //it should be fairly small so it shouldn't effect the results.
						ycor.clear();

						for(int i= 0; i< count; i++)
						{
							int ratio = count / 650; //how many samples per pixel on the screen.

							if(i % ratio == 0) //at each iteration of the radio we want to display the maximum value as the wave form.
							{
								if(i != 0) //since when i=0, max = -1000000.
								{
									ycor.push_back(-(max/200)+200);
									//cout << max << endl;
								}

								max = ussamples[i];
							}
							else if(abs(ussamples[i]) >= max)
								max = ussamples[i];
						}

						waver.loadFromSamples(&ussamples[0], count, 1, record.getSampleRate()); //to mono.
						sound.setBuffer(waver);
						sound.play();
						playtime.restart();
						playtime1.restart();
						duration = record.getDuration(),
							bplay = true;

						size_t poss = out.rfind('\\');
						size_t pose =out.rfind('.');
						if (poss != string::npos)
						{
							waver.saveToFile(out.substr(poss + 1,pose - (poss + 1)) + " 8 bit version.wav" );
						}
						else
							waver.saveToFile("8 bit audio.wav");

					}
				}
			}
		}

		window.clear();
		//drawing the waveform.
		// i wanted my waveform to look like dots connected to each other, exactly like a wave instead of points or columns.
		int j= 20; // the starting x coordinate.
		for(int i= 0; i<ycor.size(); i++)
		{
			if(ycor[i] != ycor [i+1])
				rectangle.setSize(sf::Vector2f(2,fabs(ycor[i] * 1.0- ycor[i+1]))); //the rectange's length is the difference between the two values so they look as if they are connected.
			else 
				rectangle.setSize(sf::Vector2f(2,1)); //if two values are the same there should be a straight line.

			if(ycor[i] < ycor[i+1]) //since on a computer the y coordinate gets bigger when moving to the bottom of the screen, the rectangle should be positioned on the left value iff it is smaller than the right value.
				rectangle.setPosition(j, ycor[i]);
			else
				rectangle.setPosition(j, ycor[i+1]);
			rectangle.setFillColor(sf::Color::White);
			window.draw(rectangle);
			j = j+2; //since with one square we draw on 2 pixels.
		}
		window.draw(record1);
		window.draw(record2);
		window.draw(record3);
		window.draw(record4);
		window.draw(rec);
		window.draw(opent);
		window.draw(playt);
		window.draw(pause);
		window.draw(playpauset);
		window.draw(bit8t);
		window.display();
	}
	return 0;
}