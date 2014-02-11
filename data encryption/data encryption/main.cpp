#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
using namespace cv;

unsigned keyimage [512*512];
char* FileName="lena_gray.bmp";
IplImage *Encryptionimage;
int Np=20;
int M=2,L=14,S=4;
int NpPixel[20];

void keyimageGenerate (int Enkey){
	unsigned seed=Enkey;
	srand(seed);
	for(int i =0 ; i<512*512 ;i++)
	{
		keyimage[i]=(rand()%256);
	}
}


IplImage *imageEncryption (IplImage *input){
	
	IplImage *output=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);

	int Height=cvGetDimSize(input,0);//讀取矩陣高度
	int Width=cvGetDimSize(input,1);//讀取矩陣寬度
	//CvScalar Scalar1;
	int imagedata;
	for(int i=0;i<Height*Width;i++){
		
			output->imageData[i]=(((input->imageData[i])^keyimage[i]));
			//printf("%d",output->imageData[i]);
		/*	printf("%d",(unsigned)input->imageData[i*j]+128);
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
	/*imagerecovery=imageEncryption(Encryptionimage);*/

	/*cvNamedWindow("Show Image",0);
	cvResizeWindow("Show Image",512,512);
    cvShowImage("Show Image",Encryptionimage);
*/
	
	/*cvNamedWindow("Show Image2",0);
	cvResizeWindow("Show Image2",512,512);
    cvShowImage("Show Image2",imagerecovery);*/


	/*cvWaitKey(0);
	cvDestroyWindow("Show Image");
	cvReleaseImage(&Encryptionimage);
	cvDestroyWindow("Show Image2");
	cvReleaseImage(&imagerecovery);*/
}

void selectNp(int Dekey){
	unsigned seed=Dekey;
	srand(seed);

	for(int i =0 ; i<Np ;i++)
	{
		NpPixel[i]=(rand()%(512*512));
		printf("%d",NpPixel[i]);
		printf("\t");
	}

}

void PermuteOtherPixel(int Dekey){
	unsigned seed=Dekey;
	srand(seed);
	int OtherPixel=(512*512)-Np;
	IplImage *output=cvCreateImage(cvGetSize(Encryptionimage),IPL_DEPTH_8U,1);
	//int keyimage[512*512];
	int Height=cvGetDimSize(Encryptionimage,0);//讀取矩陣高度
	int Width=cvGetDimSize(Encryptionimage,1);//讀取矩陣寬度
	memset(keyimage, 0x00, sizeof(keyimage));
	int flag=0;
	for(int i =0 ; i<Height*Width-Np ;i++)
	{
		flag=0;
		for (int j=0; j<Np ;j++){
			if(i==NpPixel[j]){
				//keyimage[i]=0;
				flag=1;
			}
		}
		if (flag==0){ 
			keyimage[i]=Encryptionimage->imageData[rand()%(512*512)]+128;
	/*		printf("%d",keyimage[i]);
			printf("\t");*/
		}
	}
	

}
void Generatesparsespace (){

}
void dataembedding (){
	int Dekey;
	cout<<"enter Dekey"<<endl;
	cin>>Dekey;
	selectNp(Dekey);
	PermuteOtherPixel(Dekey);
}


int main (){
	
	dataEncryption();
	dataembedding();
	return 0;
}


