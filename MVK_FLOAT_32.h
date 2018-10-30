#ifndef _MVK_FLOAT_32_
#define _MVK_FLOAT_32_

#define BIAS 127

typedef union MVK_FLOAT_32 MVK_FLOAT_32;
typedef union MVK_FLOAT_32 mvk;

struct separated_1_8_23
{
	unsigned mant : 23;
	unsigned exp : 8;
	unsigned sign : 1;
};

struct adv_mant
{
	unsigned advanced : 24;
};

union MVK_FLOAT_32
{
	float fl;
	struct separated_1_8_23 n;
};

void set(MVK_FLOAT_32* a,float b);
void add(MVK_FLOAT_32 addend_1, MVK_FLOAT_32 addend_2, MVK_FLOAT_32* sum);
void subtraction(MVK_FLOAT_32 minuend, MVK_FLOAT_32 subtrahend, MVK_FLOAT_32* difference);
void SET_NAN(MVK_FLOAT_32* a);
void SET_PLUS_INF(MVK_FLOAT_32* a);
void SET_MINUS_INF(MVK_FLOAT_32* a);
void SET_PLUS_ZERO(MVK_FLOAT_32* a);
void SET_MINUS_ZERO(MVK_FLOAT_32* a);

void set(MVK_FLOAT_32* a, float b)
{
	a->fl = b; 
}

void SET_NAN(MVK_FLOAT_32* a)
{
	a->n.sign = 0;
	a->n.exp = (1 << 9) - 1;
	a->n.mant = 1;
}

void SET_PLUS_INF(MVK_FLOAT_32* a)
{
	a->n.sign = 0;
	a->n.exp = (1 << 9) - 1;
	a->n.mant = 0;
}

void SET_MINUS_INF(MVK_FLOAT_32* a)
{
	a->n.sign = 1;
	a->n.exp = (1 << 9) - 1;
	a->n.mant = 0;
}

void SET_PLUS_ZERO(MVK_FLOAT_32* a)
{
	a->n.sign = 0;
	a->n.exp = 0;
	a->n.mant = 0;
}

void SET_MINUS_ZERO(MVK_FLOAT_32* a)
{
	a->n.sign = 1;
	a->n.exp = 0;
	a->n.mant = 0;
}


void add(MVK_FLOAT_32 addend_1, MVK_FLOAT_32 addend_2, MVK_FLOAT_32* sum)
{
	struct adv_mant a;
	if (addend_1.n.sign == 0 && addend_2.n.sign == 0) // Both positive
	{
		sum->n.sign = 0;
		if (addend_1.n.exp > addend_2.n.exp)
		{ 
			sum->n.exp = addend_1.n.exp;
			int shift = addend_1.n.exp - addend_2.n.exp;
			addend_2.n.mant >>= shift;
			addend_2.n.mant |= (1 << (23 - shift )); // Shift != 0;
			addend_2.n.exp += shift; 
			if (addend_1.n.mant + addend_2.n.mant < (1 << 23))
			{
				a.advanced = addend_1.n.mant + addend_2.n.mant;
				sum->n.mant = a.advanced;
			}
			else
			{
				a.advanced = addend_1.n.mant + addend_2.n.mant;
				a.advanced &= ~(1 << 23); // clear first bit zero
				sum->n.mant = a.advanced;
				//sum->n.mant >> 1;
				sum->n.exp++;
			}
		}
	}
}

void subtraction(MVK_FLOAT_32 minuend, MVK_FLOAT_32 subtrahend, MVK_FLOAT_32* difference)
{
	;
}

#endif