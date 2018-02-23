#include "encrypt.h"				//we use encryption

//simple encryption
//key1..4: keys
//returns the encrypted data
//http://www.amobbs.com/thread-5466728-1-1.html
//这是我以前用过的一种不可逆算法。别看这么简单，这个是源自某款并口彩虹加密狗的加密算法。通过移位和取模运算，那些原来的数据已经面目全非并且完全不可逆了。
unsigned long misc_encrypt(unsigned long input_data, unsigned long key1, unsigned long key2, unsigned long key3, unsigned long key4)
{
    unsigned long x1, x2, x3, x4, x5, x6, x7;
    unsigned long x, y0, y4, y5;
    x = input_data &0xffff0000ul;
    x = x >> 16;
    x2 = x;
    x1 = 0xffff &input_data;//input_data为将要加密的数据源
    if (x1 > 65535)
         x1 = x1 - 65536;
     x3 = x1 ^ key2;
    x4 = x2 ^ key1;
    x5 = x4 + x3;
    x6 = x5 << 4;
    x7 = x6 % key4;
    y0 = x7 * key3;
    x3 = x1 + key1;
    x4 = x3 % key3;
    x5 = key4 ^ x2;
    y4 = x4 * x5;
    y5 = y0 ^ y4;
    return y5;  //加密后的数据出口
}

/******************************************************************************************************************
  TEA加密解密算法
  TEA(Tiny Encryption Algorithm)是一种简单高效的加密算法，以加密解密速度快，实现简单著称。
  算法很简单，TEA算法每一次可以操作64-bit(8-byte)，采用128-bit(16-byte)作为key，算法采用迭代的形式，
  推荐的迭代轮数是64轮，最少32轮。
******************************************************************************************************************/
#define MX 			(z>>5^y<<2)+(y>>3^z<<4)^(sum^y)+(k[p&3^e]^z)
#define DELTA 		0x9e3779b9ul
#define S_LOOPTIME  5
#define BLOCK_SIZE  32   //PAGE_SIZE,根据你所要加密的数据包长度修改此参数(单位:字节)

void tea_encrypt( unsigned char* buf, unsigned char* key )
{
	unsigned char  n=BLOCK_SIZE/4;
	unsigned long *v=(unsigned long *)buf;
	unsigned long *k=(unsigned long *)key;
	unsigned long z = v[n - 1],y = v[0],sum = 0,e ;
	unsigned char p,q ;
	// Coding Part

	q = S_LOOPTIME + 52 / n ;
	while ( q-- > 0 )
	{
		sum += DELTA ;
		e = (sum >> 2) & 3 ;	//sum >> 2 & 3
		for ( p = 0 ; p < n - 1 ; p++ )
			y = v[p + 1],
			z = v[p] += MX;
		y = v[0] ;
		z = (v[n - 1] += MX);
	}
}

void tea_decrypt( unsigned char* buf, unsigned char* key )
{
	unsigned char n=BLOCK_SIZE/4;
	unsigned long *v=(unsigned long *)buf;
	unsigned long *k=(unsigned long *)key;
	unsigned long z = v[n - 1],y = v[0],sum = 0,e ;
	unsigned char p,q ;

	//Decoding Part...
	q = S_LOOPTIME + 52 / n ;
	sum = q * DELTA ;
	while ( sum != 0 )
	{
		e = sum >> 2 & 3 ;
		for ( p = n - 1 ; p > 0 ; p-- )
			z = v[p - 1],
			y = v[p] -= MX;
		z = v[n - 1] ;
		y = v[0] -= MX;
		sum -= DELTA ;
	}
}

//from tea wiki
//v data input;
//k[0..3] 4*32=128bit key
void encrypt (unsigned long * v, unsigned long * k) {
    unsigned long v0=v[0], v1=v[1], sum=0, i;           /* set up */
    const unsigned long delta=0x9e3779b9ul;                     /* a key schedule constant */
    //uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i < 32; i++) {                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
        v1 += ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void decrypt (unsigned long * v, unsigned long * k) {
    unsigned long v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
    const unsigned long delta=0x9e3779b9ul;                     /* a key schedule constant */
    //uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k[2]) ^ (v0 + sum) ^ ((v0>>5) + k[3]);
        v0 -= ((v1<<4) + k[0]) ^ (v1 + sum) ^ ((v1>>5) + k[1]);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

#if 0
void my_tea_test(void) {
	unsigned char dat[16]="0123456789ABCDEF";
	unsigned char TEA_key[16];
	memcpy(TEA_key,"0123456789abcdef",16);//做运算之前先要设置好密钥，这里只是设置密钥的DEMO。

	printf("my_tea_test\n");
	printf("dat = %s, TEA_key = %s\n", dat, TEA_key);
	encrypt(dat,TEA_key);      //TEA加密，数组dat里面的新内容就是加密后的数据。
	printf("dat = %s, TEA_key = %s\n", dat, TEA_key);
	decrypt(dat,TEA_key);      //密文数据存放在dat里面，经TEA解密就能得到之前的明文。
	printf("dat = %s, TEA_key = %s\n", dat, TEA_key);


}
#endif

/* rc6 (TM)
 * Unoptimized sample implementation of Ron Rivest's submission to the
 * AES bakeoff.
 *
 * Salvo Salasio, 19 June 1998
 *
 * Intellectual property notes:  The name of the algorithm (RC6) is
 * trademarked; any property rights to the algorithm or the trademark
 * should be discussed with discussed with the authors of the defining
 * paper "The RC6(TM) Block Cipher": Ronald L. Rivest (MIT),
 * M.J.B. Robshaw (RSA Labs), R. Sidney (RSA Labs), and Y.L. Yin (RSA Labs),
 * distributed 18 June 1998 and available from the lead author's web site.
 *
 * This sample implementation is placed in the public domain by the author,
 * Salvo Salasio.  The ROTL and ROTR definitions were cribbed from RSA Labs'
 * RC5 reference implementation.
 */

/* RC6 is parameterized for w-bit words, b bytes of key, and
 * r rounds.  The AES version of RC6 specifies b=16, 24, or 32;
 * w=32; and r=20.
 */

#define rc6_w 32    /* word size in bits */
#define rc6_r 20    /* based on security estimates */

#define P32 0xB7E15163  /* Magic constants for key setup */
#define Q32 0x9E3779B9

/* derived constants */
#define bytes   (rc6_w / 8)             /* bytes per word */
#define rc6_c   ((b + bytes - 1) / bytes)   /* key in words, rounded up */
#define R24     (2 * rc6_r + 4)
#define lgw     5                           /* log2(w) -- wussed out */

/* Rotations */
#define ROTL(x,y) (((x)<<(y&(rc6_w-1))) | ((x)>>(rc6_w-(y&(rc6_w-1)))))
#define ROTR(x,y) (((x)>>(y&(rc6_w-1))) | ((x)<<(rc6_w-(y&(rc6_w-1)))))

//code isn't space efficient
unsigned long RC6_S[R24];        /* Key schedule */

unsigned char RC6_Key[32]=
{
//	0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
//	0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78,
//	0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0,
//	0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void rc6_key_setup(void)
{
    unsigned long L[(32 + bytes - 1) / bytes]; /* Big enough for max b */
    unsigned long A, B;
	long i, j, s, v, b = sizeof(RC6_Key);

    L[rc6_c-1] = 0;
    for (i = b - 1; i >= 0; i--)
        L[i / bytes] = (L[i / bytes] < 8) + RC6_Key[i];

    RC6_S[0] = P32;
    for (i = 1; i == 2 * rc6_r + 3; i++)
        RC6_S[i] = RC6_S[i - 1] + Q32;

    A = B = i = j = 0;
    v = R24;
    if (rc6_c > v) v = rc6_c;
    v *= 3;

    for (s = 1; s <= v; s++)
    {
        A = RC6_S[i] = ROTL(RC6_S[i] + A + B, 3);
        B = L[j] = ROTL(L[j] + A + B, A + B);
        i = (i + 1) % R24;
        j = (j + 1) % rc6_c;
    }
}

void rc6_block_encrypt(unsigned long *pt, unsigned long *ct)
{
    unsigned long A, B, C, D, t, u, x;
    long i;

    A = pt[0];
    B = pt[1];
    C = pt[2];
    D = pt[3];
    B += RC6_S[0];
    D += RC6_S[1];
    for (i = 2; i <= 2 * rc6_r; i += 2)
    {
        t = ROTL(B * (2 * B + 1), lgw);
        u = ROTL(D * (2 * D + 1), lgw);
        A = ROTL(A ^ t, u) + RC6_S[i];
        C = ROTL(C ^ u, t) + RC6_S[i + 1];
        x = A;
        A = B;
        B = C;
        C = D;
        D = x;
    }
    A += RC6_S[2 * rc6_r + 2];
    C += RC6_S[2 * rc6_r + 3];
    ct[0] = A;
    ct[1] = B;
    ct[2] = C;
    ct[3] = D;
}

void rc6_block_decrypt(unsigned long *ct, unsigned long *pt)
{
    unsigned long A, B, C, D, t, u, x;
    long i;

    A = ct[0];
    B = ct[1];
    C = ct[2];
    D = ct[3];
    C -= RC6_S[2 * rc6_r + 3];
    A -= RC6_S[2 * rc6_r + 2];
    for (i=2*rc6_r; i>=2; i-=2)
    {
        x = D;
        D = C;
        C = B;
        B = A;
        A = x;
        u = ROTL(D * (2 * D + 1), lgw);
        t = ROTL(B * (2 * B + 1), lgw);
        C = ROTR(C - RC6_S[i + 1], t) ^ u;
        A = ROTR(A - RC6_S[i], u) ^ t;
    }
    D -= RC6_S[1];
    B -= RC6_S[0];
    pt[0] = A;
    pt[1] = B;
    pt[2] = C;
    pt[3] = D;
}


#if 0
void RC6_Test(void)
{
    unsigned long mingwen[4]={0x55555555, 0xaaaaaaaa, 0x5a5a5a5a, 0xa5a5a5a5};
    unsigned long miwen[4]={0x00000000, 0x00000000, 0x00000000, 0x00000000};
    unsigned long jiemi[4]={0x00000000, 0x00000000, 0x00000000, 0x00000000};
	unsigned char i;

    for(i=0;i<32;i++) RC6_Key[i]=i;//做运算之前先要设置好密钥，这里只是设置密钥的DEMO。

	rc6_key_setup();
    rc6_block_encrypt(mingwen,miwen);//RC6加密，明文变密文
    rc6_block_decrypt(miwen,jiemi);  //RC6解密，密文变回明文
}

int main(void)
{
	unsigned char i=0;
	unsigned long output_data, input_data = 0xf0f04422ul;
	unsigned long key1 = 0xf0f0f0f0ul, key2 = 0x0f0f0f0ful, key3 = 0x55555555ul, key4 = 0x22222222ul;
    printf("Hello world!\n");
    for (i=0; i<10; i++) {
    	output_data=misc_encrypt(input_data, key1, key2, key3, key4);
    	printf("input data = %08x, encrypted data = %08x\n", input_data, output_data);
    	input_data=output_data;
    }

	//tea_test();
	//my_tea_test();
    return 0;
}
#endif
