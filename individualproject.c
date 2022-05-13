#include <stdio.h>
#include <string.h>

void mygets(char *s, int n)
{
	fgets(s, n, stdin);	
	if (s[strlen(s) - 1] == '\n')	
		s[strlen(s) - 1] = 0;	
}

char base[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
void encoding(char *s)
{
	char enc[5] = {0};	
	int i = 0;		
	while (s[i])	
	{
		enc[0] = base[(s[i] >> 2) & 0x3f];	
		if (s[i + 1]==0)	
		{
			enc[1] = base[(s[i] << 4) & 0x3f];	
			enc[2] = '=';	
			enc[3] = '=';
			i++;		
		}
		else if(s[i + 2] == 0)	
		{
			enc[1] = base[((s[i] << 4)|((s[i+1]>>4)&0xf)) & 0x3f];	
			enc[2]= base[(s[i+1] << 2) & 0x3f];		
			enc[3] = '=';		
			i += 2;	
		}
		else
		{
			enc[1] = base[((s[i] << 4) | ((s[i + 1] >> 4) & 0xf)) & 0x3f];	
			enc[2] = base[((s[i + 1] << 2) | ((s[i + 2] >> 6) & 0x3)) & 0x3f];	
			enc[3] = base[s[i + 2] & 0x3f];		
			i += 3;		
		}
		printf("%s", enc);	
	}
}

void decoding(char *s)
{
	char dec[4] = { 0 };	
	int idx, i = 0;	
	char *p;
	while (s[i])	
	{
		dec[0] = 0;	
		dec[1] = 0;
		dec[2] = 0;
		p = strchr(base, s[i]);	
		if (p == NULL)			
		{
			return;		
		}
		idx = p - base;	
		dec[0] = idx << 2;	
		i++;	
		if(s[i])		
		{
			p = strchr(base, s[i]);	
			if (p == NULL)			
			{
				return;		
			}
			idx = p - base;	
			dec[0] |= (idx >> 4) & 3;	
			dec[1] = (idx & 0xf) << 4;	
			i++;	
		}
		if (s[i])	
		{
			if (s[i] != '=')	
			{
				p = strchr(base, s[i]);	
				if (p == NULL)			
				{
					return;		
				}
				idx = p - base;	
				dec[1] |= idx >> 2;	
				dec[2] = (idx & 3) << 6;	
			}
			i++;	
		}
		if (s[i])	
		{
			if (s[i] != '=')	
			{
				p = strchr(base, s[i]);	
				if (p == NULL)			
				{
					return;		
				}
				idx = p - base;	
				dec[2] |= idx;	
			}
			i++;	
		}
		printf(dec);
	}
}
int main()
{
	char ch[32];
	char str[1024];
	while (1)
	{
		printf("1 - Encoding\n");
		printf("2 - Decoding\n");
		printf("0 - Exit\n");
		mygets(ch, sizeof(ch));	
		if (ch[1] == 0)
		{
			switch (ch[0])
			{
			case '1':	
				printf("Enter string to Base64 encode: ");
				mygets(str, sizeof(str));	
				printf("Base64:\n");
				encoding(str);	
				printf("\n");
				break;
			case '2':	
				printf("Enter Base64-encoded string: ");
				mygets(str, sizeof(str));	
				printf("Decoded text:\n");
				decoding(str);		
				printf("\n");
				break;
			case '0':
				return 0;
			}
		}
	}
	return 0;
}
