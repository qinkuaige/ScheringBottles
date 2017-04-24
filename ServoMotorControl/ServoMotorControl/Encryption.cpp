#include "stdafx.h"
#include "Encryption.h"
#include <string.h>


Encryption::Encryption(char* passward) :m_passward(passward)
{
}


Encryption::~Encryption()
{
	auto instance = Encryption::getInstance();
	if (instance != NULL)
	{
		delete(instance);
	}
}

Encryption* Encryption::getInstance(char* passward)
{
	static Encryption* instance = NULL;
	if (instance == NULL)
	{
		instance = new Encryption(passward);
	}
	return instance;
}
//º”√‹
void Encryption::encryption(char *str)
{
	size_t password_size = strlen(m_passward);
	size_t str_size = strlen(str);
	for (size_t i = 0; i < str_size; i++)
	{
		for (size_t j = 0; j < password_size; j++)
		{
			str[i] = str[i] ^ m_passward[j];
		}
	}
}
//Ω‚√‹
void Encryption::decryption(char *str)
{
	size_t password_size = strlen(m_passward);
	size_t str_size = strlen(str);
	for (size_t i = 0; i < str_size; i++)
	{
		for (int j = password_size - 1; j >= 0 ; j--)
		{
			str[i] = str[i] ^ m_passward[j];
		}
	}
}