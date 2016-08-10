#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <iostream>
#include <fstream>
using namespace std;

int byteStream2BinaryString(uint8_t byteBuf[],int byteLen,char charBuf[],int charLen,int type);

/*************************************
*@brief:中文与二进制字符串之间的相互转换
*@加密:-e -f inputFile.txt -o outFile
*@解密:-d -f inputFile.txt -o outFile
*@帮助：-h 或者 --help
#@将结果输出到标准输出:-O
**************************************/
int main(int argc,char* argv[]){
	//print help
	if(argc==2&&(strcmp(argv[1],"-h")==0||strcmp(argv[1],"--help")==0)){
		cout<<"Usage:"<<endl;
		cout<<"encryption: b2bs.out -e -O -f [inputFile] -o [outFile]"<<endl;
		cout<<"decryption: b2bs.out -d -O -f [inputFile] -o [outFile]"<<endl<<endl;
		
		cout<<"Options:"<<endl;
		cout<<"-e <encrypt> encrypt chinese to binary string."<<endl;
		cout<<"-d <decrypt> decrypt binary string to chinese."<<endl;
		cout<<"-f <file> specify the input file."<<endl;
		cout<<"-o <output> specify the output file."<<endl;
		cout<<"-O <Output> output the descrypt or encrypt result to standard output."<<endl;
		cout<<"-h or --help output help information."<<endl<<endl;
		
		cout<<"Author:"<<endl;
		cout<<"Written by Dablelv(吕吕)"<<endl;

		cout<<"Reporting:"<<endl;
		cout<<"Any suggestions or bugs,please report to 1589276509@qq.com,thx!"<<endl;
		return 0;
	}
	
	if(argc!=6&&argc!=7){
		cerr<<"error usage,check input or try -h | --help!"<<endl;
		return -1;
	}
	
	bool isStdout=false,isDecrypt=false,isEncrypt=false;
	ifstream ifs;
	ofstream ofs;
	string outFilePath;
	for(int i=0;i<argc;++i){
		if(strcmp(argv[i],"-O")==0){
			isStdout=true;
		}
		if(strcmp(argv[i],"-e")==0){
			isEncrypt=true;
		}
		if(strcmp(argv[i],"-d")==0){
			isDecrypt=true;
		}
		if(strcmp(argv[i],"-f")==0){
			ifs.open(argv[i+1], ios::in);
			if(!ifs.is_open()){
				//cerr<<"can't find file "<<argv[i+1]<<endl;
				cerr<<"ERRCODE:"<<errno<<" "<<strerror(errno)<<endl;
				return -1;
			}
		}
		if(strcmp(argv[i],"-o")==0){
			ofs.open(argv[i+1],ios::out);
			if(!ifs.is_open()){
				//cerr<<"can't find file "<<argv[i+1]<<endl;
				cerr<<"ERRCODE:"<<errno<<" "<<strerror(errno)<<endl;
				return -1;
			}
		}
	}
	if((isEncrypt&&isDecrypt)||(!isEncrypt&&!isDecrypt)){
		cerr<<"error usage,check input or try -h|--help!"<<endl;
		return -1;
	}
	
	/************* 加密 **************/
	if(isEncrypt){
		ifs.seekg(0,ios::end);
		int byteLen=ifs.tellg();
		uint8_t* byteBuf=new uint8_t[byteLen];
		char* charBuf=new char[byteLen*8];
		ifs.seekg(0,ios::beg);
		ifs.read((char*)byteBuf,byteLen);
		int ret=byteStream2BinaryString(byteBuf,byteLen,charBuf,byteLen*8,0);
		if(ret!=0){
			cerr<<"encrypt failed!"<<endl;
			return -1;
		}
		ofs.write(charBuf,byteLen*8);
		if(isStdout){
			cout<<"encrypt result:"<<endl;
			cout<<charBuf<<endl;
		}
		delete[] byteBuf;
		delete[] charBuf;
		return 0;
	}
	
	/************* 解密 **************/
	if(isDecrypt){
		ifs.seekg(0,ios::end);
		int charLen=ifs.tellg();
		char* charBuf=new char[charLen];
		int byteLen=charLen%8==0?charLen/8:charLen/8+1;
		uint8_t* byteBuf=new uint8_t[byteLen];
		ifs.seekg(0,ios::beg);
		ifs.read(charBuf,charLen);
		int ret=byteStream2BinaryString(byteBuf,byteLen,charBuf,charLen,1);
		if(ret!=0){
			cerr<<"decrypt failed!"<<endl;
			return -1;
		}
		ofs.write((char*)byteBuf,byteLen);
		if(isStdout){
			cout<<"decrypt result:"<<endl;
			cout<<(char*)byteBuf<<endl;
		}
		delete[] byteBuf;
		delete[] charBuf;
		return 0;
	}
}

/*****************************************
*@brief:字节流转换与二进制字符流相互转换
*@para:byteBuf:输入字节流;byteLen:字节流长度;charBuf:二进制字符流;charLen:二进制字符流长度;type:0字节流转二进制字符流,1二进制字符流转字节流
*@return:0:success;-1:error
*@author:dablelv
*@date:20160809
******************************************/
int byteStream2BinaryString(uint8_t byteBuf[],int byteLen,char charBuf[],int charLen,int type){
	if(type!=0&&type!=1){
		return -1;
	}
	//字节流转二进制字符流
	if(type==0){
		if(charLen<8*byteLen)
			return -1;
		int charBufIndex=0;
		for(int i=0;i<byteLen;++i){
			for(int j=7;j>=0;--j){
				if(byteBuf[i]>>j&0x1){
					charBuf[charBufIndex++]='1';
				}else{
					charBuf[charBufIndex++]='0';
				}
			}
		}
		return 0;
	}
	
	//二进制字符流转字节流
	if(type==1){
		if(8*byteLen<charLen)
			return -1;
		char tmpStr[9]="";
		int byteBufIndex=0;
		for(int i=0;i<charLen;i=i+8){
			strncpy(tmpStr,charBuf+i,8);
			for(int j=0;j<8;++j){
				byteBuf[byteBufIndex]+=tmpStr[j]-'0'<<7-j;
			}
			++byteBufIndex;
		}
		return 0;
	}
}
