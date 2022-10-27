#include <string>
#include "m2co.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <sys/time.h>

#include <opencv2/opencv.hpp>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

class Video
{
	public:
	 	double fps;
	 	std::string window_name = "Bad Apple";
		cv::VideoCapture cap;
		struct winsize w;
		int scaled_w;
		int scaled_h;
		double r;


		Video(std::string videoPath, double r): r{r}
		{
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			scaled_h = w.ws_row -2;
			
		
			ColorPrint("Opening video\n", 255, 0, 0);

			cap = cv::VideoCapture(videoPath);
			fps = 1.0 / static_cast<double>(cap.get(cv::CAP_PROP_FPS)); 

			//cv::namedWindow(window_name, cv::WINDOW_NORMAL); //create a window
		}
		
		void Play()
		{
			struct timeval start;
			struct timeval stop;

			gettimeofday(&start, NULL);
			while (true)
			{
				
				//printf("yukseklik: %i genislik: %i\n", scaled_h, scaled_w);
				
				//printf("r: %i c: %i\n", scaled_w, scaled_h);
				bool bSuccess = true;
				double secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
				if(secs > fps)
				{
					cv::Mat frame;
					cv::Mat scaled;
					bSuccess = cap.read(frame); // read a new frame from video
					scaled_w = (static_cast<float>(scaled_h) / static_cast<float>(frame.rows)) * static_cast<float>(frame.cols);
					cv::resize(frame, scaled, {scaled_w * r, scaled_h});
					int i = 0;
					for(int y = 0; y < scaled_h; y++)
					{
						for(int x = 0; x < scaled_w * r; x++)
						{
							putchar((scaled.data[i++] + scaled.data[i++] + scaled.data[i++] == 0 ? ' ' : '#'));
						}
						putchar('\n');					
					}
					gotoxy(0,0);
					gettimeofday(&start, NULL);
				}
				//printf("time: %lu\n", (stop.tv_sec - start.tv_sec) * 100 + stop.tv_usec - start.tv_usec);
				//std::cout << (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec << '\n';

				if (bSuccess == false) 
				{
					printf("Found the end of the video");
					break;
				}


				//if (cv::waitKey(10) == 27)
				{
				//	printf("Esc key is pressed by user. Stoppig the video\n");
				//break;
				
				}
				gettimeofday(&stop, NULL);

				
			}
		}
};

int main(int argc, char** argv)
{
	
	//cv2::VideoCapture("./badapple.mp4");
	//Video vid(argv[1]);
	Video vid(argv[1], argc == 3 ? std::atof(argv[2]) : 2);

	vid.Play();

	//printf("Frames: %i\n", count)


	return 0;
}

