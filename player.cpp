#include <string>
#include "m2co.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

#include <opencv2/opencv.hpp>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

class Video
{
	public:
	 	float fps;
	 	std::string window_name = "Bad Apple";
		cv::VideoCapture cap;
		struct winsize w;
		int scaled_w;
		int scaled_h;


		Video(std::string videoPath)
		{
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			scaled_h = w.ws_row -2;
			
		
			ColorPrint("Opening video\n", 255, 0, 0);

			cap = cv::VideoCapture(videoPath);
			fps = 1.0 / static_cast<float>(cap.get(cv::CAP_PROP_FPS)); 

			//cv::namedWindow(window_name, cv::WINDOW_NORMAL); //create a window
		}
		
		void Play()
		{
			while (true)
			{
				cv::Mat frame;
				cv::Mat scaled;
				bool bSuccess = cap.read(frame); // read a new frame from video
				scaled_w = (static_cast<float>(scaled_h) / static_cast<float>(frame.rows)) * static_cast<float>(frame.cols);
				cv::resize(frame, scaled, {scaled_w * 2, scaled_h});
				//printf("yukseklik: %i genislik: %i\n", scaled_h, scaled_w);
				
				int i = 0;
				//printf("r: %i c: %i\n", scaled_w, scaled_h);
				for(int y = 0; y < scaled_h; y++)
				{
					for(int x = 0; x < scaled_w * 2; x++)
					{
						putchar((scaled.data[i++] + scaled.data[i++] + scaled.data[i++] == 0 ? ' ' : '#'));
					}
					putchar('\n');
					
				}
				gotoxy(0,0);
				usleep(1000000*fps);

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
			}
		}
};

int main(int argc, char** argv)
{
	
	//cv2::VideoCapture("./badapple.mp4");
	Video vid(argv[1]);
	vid.Play();

	//printf("Frames: %i\n", count)


	return 0;
}

