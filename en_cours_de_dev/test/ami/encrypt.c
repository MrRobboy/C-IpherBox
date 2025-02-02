void encryptDecrypt(char *data, int dataLen, const char *key, int keyLen)
{
	for (int i = 0; i < dataLen; i++)
	{
		data[i] ^= key[i % keyLen]; // XOR pour chiffrer/déchiffrer
	}
}
