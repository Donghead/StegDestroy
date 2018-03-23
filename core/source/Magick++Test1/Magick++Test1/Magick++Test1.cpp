// Magick++Test1.cpp : Defines the entry point for the console application.
//
// Simple test project that can be used to verify the Magick++ component of the solution 
// is functioning as intended. 

#include "stdafx.h"
#include <Magick++.h>
#include <string>
#include <iostream>

using namespace Magick;
using namespace std;

#define QUALITY_INCREMENT 10
#define MIN_JPG_QUALITY 0
#define MAX_JPG_QUALITY 100

int main()
{
	string fullPath = "", imagePath = "", imageName = "", imageExtension = "";

	cout << "Path to image using double backslashes '\\' for folder dividers and the file extension (e.g .jpg): " << endl;
	getline(cin, fullPath);

	size_t found = fullPath.find_last_of("\\");
	imageName = fullPath.substr(found + 1);
	imagePath = fullPath.substr(0, found+1);
	found = imageName.find_last_of('.');
	imageExtension = imageName.substr(found); //includes the dot in the extension
	imageName = imageName.substr(0, found);
	cout << "Image name: " << imageName << endl;
	cout << "Image extension: " << imageExtension << endl;

	if (!imagePath.empty())
	{
		try 
		{
			// Construct an image instance first so that we don't have to worry
			// about object construction failure due to a minor warning exception
			// being thrown.
			Magick::Image imageIn;
			try 
			{
				// Try reading image file
				imageIn.read(fullPath);
			}
			catch (Magick::WarningCoder &warning)
			{
				// Process coder warning while loading file (e.g. TIFF warning)
				// Maybe the user will be interested in these warnings (or not).
				// If a warning is produced while loading an image, the image
				// can normally still be used (but not if the warning was about
				// something important!)
				cerr << "Coder Warning: " << warning.what() << endl;
			}
			catch (Magick::Warning &warning)
			{
				// Handle any other Magick++ warning.
				cerr << "Warning: " << warning.what() << endl;
			}
			catch (Magick::ErrorFileOpen &error)
			{
				// Process Magick++ file open error
				cerr << "Error: " << error.what() << endl;
			}

			try 
			{
				imageIn.rotate(90);
				cout << "Writing new rotated image as: " << imageName + "_90rotation" << endl;
				imageIn.write(imagePath + imageName + "_90rotation" + imageExtension);
				//cout << "Test path for rotated image: " << imagePath + imageName + "_90rotation" + imageExtension << endl << endl;

				cout << "Writing images in JPG quality 0-100 in 10 increments suffixed with _JPG[0-100]: " << endl;
				for (int i = MIN_JPG_QUALITY; i <= MAX_JPG_QUALITY; i += QUALITY_INCREMENT)
				{
					imageIn.quality(i);
					cout << "New image path post JPEG'ing: " << imagePath + imageName + "_JPG" + to_string(i) + ".jpg" << endl;
					imageIn.write(imagePath + imageName + "_JPG" + to_string(i) + ".jpg");
				}
				

			}
			catch (Magick::Exception & error)
			{
				// Handle problem while rotating or writing outfile.
				cerr << "Caught Magick++ exception: " << error.what() << endl;
			}
		}
		catch (std::exception & error)
		{
			// Process any other exceptions derived from standard C++ exception
			cerr << "Caught C++ STD exception: " << error.what() << endl;
		}
		catch (...)
		{
			// Process *any* exception (last-ditch effort). There is not a lot
			// you can do here other to retry the operation that failed, or exit
		}
	}
	

	cout << "Verifying Magick++ is working as intended..." << endl;

	
}

