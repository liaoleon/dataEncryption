#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
using namespace cv;

unsigned keyimage [512*512];
char* FileName="lena_gray.bmp";
IplImage *Encryptionimage;

void keyimageGenerate (int Enkey){
	unsigned seed=Enkey;
	srand(seed);
	for(int i =0 ; i<512*512 ;i++)
	{
		keyimage[i]=(rand()%256);
	}
}


IplImage *imageEncryption (IplImage *input){
	
	IplImage *output=input;

	int Height=cvGetDimSize(input,0);//讀取矩陣高度
	int Width=cvGetDimSize(input,1);//讀取矩陣寬度
	CvScalar Scalar1;
	int imagedata;
	for(int i=0;i<Height*Width;i++){
		
			output->imageData[i]=(((input->imageData[i])^keyimage[i]));
			/*printf("%d",(unsigned)input->imageData[i*j]+128);
			if((unsigned)input->imageData[i*j]+128==255)
				return *input;
			printf("\t");*/
			
		
	}
	return output;
}

void dataEncryption(){
	int Enkey;
	cout<<"enter Enkey"<<endl;
	cin>>Enkey;
	keyimageGenerate(Enkey);
	IplImage *originalimage = cvLoadImage(FileName,CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *imagerecovery;
	Encryptionimage=imageEncryption(originalimage);
	

	cvNamedWindow("Show Image",0);
	cvResizeWindow("Show Image",512,512);
    cvShowImage("Show Image",Encryptionimage);

	imagerecovery=imageEncryption(Encryptionimage);
	cvNamedWindow("Show Image2",0);
	cvResizeWindow("Show Image2",512,512);
    cvShowImage("Show Image2",imagerecovery);


	cvWaitKey(0);
	cvDestroyWindow("Show Image");
	cvReleaseImage(&Encryptionimage);
	cvDestroyWindow("Show Image2");
	cvReleaseImage(&imagerecovery);
}

void selectNp(int Dekey){
}

void dataembedding (){
	int Dekey;
	cout<<"enter Dekey"<<endl;
	cin>>Dekey;
}


int main (){
	
	dataEncryption();
	//dataembedding ()
	return 0;
}


