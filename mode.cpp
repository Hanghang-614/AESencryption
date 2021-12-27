class Mode{
	public:
		int ECB(char *p,char *key);
		void deECB(char *c,char *key,int len);
		
		int CBC(char *p,char *key);
		void deCBC(char *c,char *key,int len);
		
		int CTR(char *p,char *key);
		void deCTR(char *c,char *key,int len);
		
		void padding(char *in,int &len);
	private:
		AES aes;
};
void Mode::padding(char *in,int &len){
	if(len%16==0){
		return;
	}
	int r = 16-(len%16);
	len+= r;
	char res[r];
	memset(res,'#',r);
	strcat(in,res);
}
int Mode::CBC(char *p,char *key){
	int len = strlen(p);
	padding(p,len);
	cout<<"len= "<<len<<endl;
	char temp[17]="cykkcykkcykkcykk";
	int k,i;
	for(k=0;k<len;k+=16){
	  aes.strXor(p+k,temp);
	  aes.encryption(p+k,key);
	  for(i=0;i<16;i++){
	  	temp[i] = p[i+k];
	  }
	}
	return len;
}
void Mode::deCBC(char *c,char *key,int len){
	int k,i;
	char temp[17]="cykkcykkcykkcykk";
	char temp_[17]="cykkcykkcykkcykk";
	for(k=0;k<len;k+=16){
	  for(i=0;i<16;i++){
	  	temp_[i] = c[i+k];
	  }
	  aes.deencryption(c+k,key);
	  aes.strXor(c+k,temp);
	  for(i=0;i<16;i++){
	  	temp[i] = temp_[i];
	  }
	}
}
int Mode::ECB(char*p,char*key){
	int len = strlen(p);
	padding(p,len);
	cout<<"len= "<<len<<endl;
	int k;
	for(k=0;k<len;k+=16){
	  aes.encryption(p+k,key);	
	}
	return len;
}
void Mode::deECB(char*c,char*key,int plen){
	int k;
	for(k=0;k<plen;k+=16){
	  aes.deencryption(c+k,key);	
	}
}
int Mode::CTR(char *p,char *key){
	int len = strlen(p);
	padding(p,len);
	char counter[17] = "abcdefghijklmnop";
	int k,i;
	for(k=0;k<len;k+=16){
	  aes.encryption(counter,key);
	  aes.strXor(p+k,counter);
	  for(i=0;i<16;i++){
	  	counter[i]++;
	  }	
	}
	return len;
}
void Mode::deCTR(char *c,char *key,int len){
	int k,i;
	char counter[17] = "abcdefghijklmnop";
	for(k=0;k<len;k+=16){
	  aes.encryption(counter,key);
	  aes.strXor(c+k,counter);
	  for(i=0;i<16;i++){
	  	counter[i]++;
      }	
	}
}
