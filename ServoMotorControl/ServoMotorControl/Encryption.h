#pragma once
class Encryption
{
private:
	char* m_passward;
public:
	static Encryption *getInstance(char* passward = "zz2016");
	void encryption(char *str);
	void decryption(char *str);
private:
	Encryption(char* passward = "zz2016");
	~Encryption();
};

