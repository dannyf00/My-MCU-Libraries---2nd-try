#include "misc.h"						//misc functions

//hardware configuration
//end hardware configuration


const unsigned char _hex2bin[]={
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
	};

//turn a ul to decimal string, with leading zeros
unsigned char ultoa_0(unsigned char * str, unsigned long ul, unsigned char length) {
	//unsigned char sep_count=0;

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		str[--length] = _hex2bin[ul % 10];		//(ul % 10) + '0';			//convert the lowest number
		ul = ul / 10;					//next number
	} while (length);					//leading zeros
	//} while (ul);						//leading blank
	return length;
}

//turn a ul to decimal string, with no leading zeros
unsigned char ultoa_dec(unsigned char * str, unsigned long ul, unsigned char length) {
	//unsigned char sep_count=0;

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		str[--length] = _hex2bin[ul % 10];		//(ul % 10) + '0';			//convert the lowest number
		ul = ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//turn a ul to binary string, with leading zeros
unsigned char ultoa_bin(unsigned char * str, unsigned long ul, unsigned char length) {
	//unsigned char sep_count=0;

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		str[--length] = _hex2bin[ul & 0x01];		//(ul % 10) + '0';			//convert the lowest number
		ul = ul >> 1;					//ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//turn a ul to hex string, with leading zeros
unsigned char ultoa_hex(unsigned char * str, unsigned long ul, unsigned char length) {
	//unsigned char sep_count=0;

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		str[--length] = _hex2bin[ul & 0x0f];		//(ul % 10) + '0';			//convert the lowest number
		ul = ul >> 4;					//ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//turn a ul to string, with leading zeros
//inserting ',' separators
unsigned char ultoa_s(unsigned char * str, unsigned long ul, unsigned char length) {
	unsigned char sep_count=0;

	do {
		//process separator sing ','
		if (sep_count==3) {
			sep_count=0;				//reset the separator count
			str[--length]=ULTOA_SEPARATOR;		//insert the separator
		}
		sep_count+=1;					//increment separator counter

		//perform the string conversion
		str[--length] = (ul % 10) + '0';			//convert the lowest number
		ul = ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//turn a sl to decimal string, with leading zeros
unsigned char ltoa_0(unsigned char * str, signed long sl, unsigned char length) {
	if (sl > 0) {
		length=ultoa_0(&str[1], sl, length-1);
		str[length]='+';
	} else {
		length=ultoa_0(&str[1], -sl, length-1);
		str[length]='-';
	}
	return length;
}

//turn a ul to decimal string, with no leading zeros
unsigned char ltoa_dec(unsigned char * str, signed long sl, unsigned char length) {
	if (sl > 0) {
		length=ultoa_dec(&str[1], sl, length-1);
		str[length]='+';
	} else {
		length=ultoa_dec(&str[1], -sl, length-1);
		str[length]='-';
	}
	return length;
}

//turn a sl to binary string, with leading zeros
unsigned char ltoa_bin(unsigned char * str, signed long sl, unsigned char length) {
	if (sl > 0) {
		length=ultoa_bin(&str[1], sl, length-1);
		str[length]='+';
	} else {
		length=ultoa_bin(&str[1], -sl, length-1);
		str[length]='-';
	}
	return length;
}

//turn a sl to hex string, with leading zeros
unsigned char ltoa_hex(unsigned char * str, signed long sl, unsigned char length) {
	if (sl > 0) {
		length=ultoa_bin(&str[1], sl, length-1);
		str[length]='+';
	} else {
		length=ultoa_bin(&str[1], -sl, length-1);
		str[length]='-';
	}
	return length;
}

//turn a sl to string, with leading zeros
//inserting ',' separators
unsigned char ltoa_s(unsigned char * str, signed long sl, unsigned char length) {
	if (sl > 0) {
		length=ultoa_bin(&str[1], sl, length-1);
		str[length]='+';
	} else {
		length=ultoa_bin(&str[1], -sl, length-1);
		str[length]='-';
	}
	return length;
}

//convert double to string, 1 decimal points
unsigned char ftoc1(unsigned char * str, double f, unsigned char length) {
	unsigned char dp_index=0;
	unsigned long ul = (unsigned long) (f * 10); //two decimal point

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		if (dp_index++==1) str[--length]='.';
			str[--length] = '0'+(ul % 10);		//(ul % 10) + '0';			//convert the lowest number
			ul = ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//convert double to string, 2 decimal points
unsigned char ftoc2(unsigned char * str, double f, unsigned char length) {
	unsigned char dp_index=0;
	unsigned long ul = (unsigned long) (f * 100); //two decimal point

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		if (dp_index++==2) str[--length]='.';
			str[--length] = '0'+(ul % 10);		//(ul % 10) + '0';			//convert the lowest number
			ul = ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//convert double to string, 3 decimal points
unsigned char ftoc3(unsigned char * str, double f, unsigned char length) {
	unsigned char dp_index=0;
	unsigned long ul = (unsigned long) (f * 1000); //four decimal point

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		if (dp_index++==3) str[--length]='.';
		str[--length] = '0'+(ul % 10);		//(ul % 10) + '0';			//convert the lowest number
		ul = ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//convert double to string, 4 decimal points
unsigned char ftoc4(unsigned char * str, double f, unsigned char length) {
	unsigned char dp_index=0;
	unsigned long ul = (unsigned long) (f * 10000); //four decimal point

	do {
		//process separator sing ','
		//if (sep_count==3) {
		//	sep_count=0;				//reset the separator count
		//	str[--length]=ULTOA_SEPARATOR;		//insert the separator
		//}
		//sep_count+=1;					//increment separator counter

		//perform the string conversion
		if (dp_index++==4) str[--length]='.';
		str[--length] = '0'+(ul % 10);		//(ul % 10) + '0';			//convert the lowest number
		ul = ul / 10;					//next number
	//} while (length);					//leading zeros
	} while (ul);						//leading blank
	return length;
}

//fast ultoa routine
unsigned char ultoa_fast(unsigned char * str, unsigned long ul, unsigned char len) {
	unsigned char tmp=0;
	unsigned char len_cur=10;

	tmp=0;						//reset tmp
	while (ul >= 1000000000ul) {
		ul -= 1000000000ul;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 100000000ul) {
		ul -= 100000000ul;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 10000000ul) {
		ul -= 10000000ul;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 1000000ul) {
		ul -= 1000000ul;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 100000ul) {
		ul -= 100000ul;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 10000) {
		ul -= 10000;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 1000) {
		ul -= 1000;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 100) {
		ul -= 100;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	tmp=0;						//reset tmp
	while (ul >= 10) {
		ul -= 10;		//subtract the surplus
		tmp+=1;					//increment tmp
	}
	if (len_cur <= len) str[len-len_cur]=tmp + '0';	//convert it to char
	len_cur-=1;					//move to the next digit

	//last digit
	str[len-1]=ul + '0';

	return len;
}

//convert ul (8-digit) to ascii
void ul8toa(char * str, uint32_t num) {
	str[7]=(num % 10) + '0'; num /= 10;
	str[6]=(num % 10) + '0'; num /= 10;
	str[5]=(num % 10) + '0'; num /= 10;
	str[4]=(num % 10) + '0'; num /= 10;
	str[3]=(num % 10) + '0'; num /= 10;
	str[2]=(num % 10) + '0'; num /= 10;
	str[1]=(num % 10) + '0'; num /= 10;
	str[0]=(num % 10) + '0'; num /= 10;
}

//convert ul (8-digit) to ascii, fast
void ul8toa_fast(char *str, uint32_t num) {
	uint8_t tmp;
	
	tmp = 0; while (num >=10000000ul) {num -=10000000ul; tmp+=1;}; str[0]=tmp + '0';
	tmp = 0; while (num >= 1000000ul) {num -= 1000000ul; tmp+=1;}; str[1]=tmp + '0';
	tmp = 0; while (num >=  100000ul) {num -=  100000ul; tmp+=1;}; str[2]=tmp + '0';
	tmp = 0; while (num >=   10000ul) {num -=   10000ul; tmp+=1;}; str[3]=tmp + '0';
	tmp = 0; while (num >=    1000ul) {num -=    1000ul; tmp+=1;}; str[4]=tmp + '0';
	tmp = 0; while (num >=     100ul) {num -=     100ul; tmp+=1;}; str[5]=tmp + '0';
	tmp = 0; while (num >=      10ul) {num -=      10ul; tmp+=1;}; str[6]=tmp + '0';
	//tmp = 0; while (num >=       1ul) {num -=       1ul; tmp+=1;}; str[7]=tmp + '0';
	str[7]=num + '0';
}
