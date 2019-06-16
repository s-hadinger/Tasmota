/*
 * Copyright (c) 2017 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "inner.h"
//#undef pgm_read_word
//#define pgm_read_word(addr)             (*(const uint16_t*)(addr))

#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"

/* see inner.h */
__attribute__((optimize("-O3"))) void
br_i15_montymul(uint16_t *d, const uint16_t *x, const uint16_t *y,
	const uint16_t *m, uint16_t m0i)
{
	size_t len, len4, u, v;
	uint32_t dh;

	len = (pgm_read_word(&m[0]) + 15) >> 4;
	len4 = len & ~(size_t)3;
	br_i15_zero(d, pgm_read_word(&m[0]));
	dh = 0;
	for (u = 0; u < len; u ++) {
		uint32_t f, xu, r, zh;

		xu = pgm_read_word(&x[u + 1]);
		f = MUL15((d[1] + MUL15(pgm_read_word(&x[u + 1]), pgm_read_word(&y[1]))) & 0x7FFF, m0i)
			& 0x7FFF;
#if BR_ARMEL_CORTEXM_GCC
		if (len4 != 0) {
			uint16_t *limit;

			limit = d + len4;
			asm volatile (
"\n\
	@ carry: r=r2                                              \n\
	@ multipliers: xu=r3 f=r4                                  \n\
	@ base registers: d+v=r5 y+v=r6 m+v=r7                     \n\
	@ r8 contains 0x7FFF                                       \n\
	@ r9 contains d+len4                                       \n\
	ldr	r0, %[limit]                                       \n\
	ldr	r3, %[xu]                                          \n\
	mov	r9, r0                                             \n\
	ldr	r4, %[f]                                           \n\
	eor	r2, r2                                             \n\
	ldr	r5, %[d]                                           \n\
	sub	r1, r2, #1                                         \n\
	ldr	r6, %[y]                                           \n\
	lsr	r1, r1, #17                                        \n\
	ldr	r7, %[m]                                           \n\
	mov	r8, r1                                             \n\
loop%=:                                                            \n\
	ldrh	r0, [r6, #2]                                       \n\
	ldrh	r1, [r7, #2]                                       \n\
	mul	r0, r3                                             \n\
	mul	r1, r4                                             \n\
	add	r2, r0, r2                                         \n\
	ldrh	r0, [r5, #2]                                       \n\
	add	r2, r1, r2                                         \n\
	mov	r1, r8                                             \n\
	add	r2, r0, r2                                         \n\
	and	r1, r2                                             \n\
	lsr	r2, r2, #15                                        \n\
	strh	r1, [r5, #0]                                       \n\
		                                                   \n\
	ldrh	r0, [r6, #4]                                       \n\
	ldrh	r1, [r7, #4]                                       \n\
	mul	r0, r3                                             \n\
	mul	r1, r4                                             \n\
	add	r2, r0, r2                                         \n\
	ldrh	r0, [r5, #4]                                       \n\
	add	r2, r1, r2                                         \n\
	mov	r1, r8                                             \n\
	add	r2, r0, r2                                         \n\
	and	r1, r2                                             \n\
	lsr	r2, r2, #15                                        \n\
	strh	r1, [r5, #2]                                       \n\
		                                                   \n\
	ldrh	r0, [r6, #6]                                       \n\
	ldrh	r1, [r7, #6]                                       \n\
	mul	r0, r3                                             \n\
	mul	r1, r4                                             \n\
	add	r2, r0, r2                                         \n\
	ldrh	r0, [r5, #6]                                       \n\
	add	r2, r1, r2                                         \n\
	mov	r1, r8                                             \n\
	add	r2, r0, r2                                         \n\
	and	r1, r2                                             \n\
	lsr	r2, r2, #15                                        \n\
	strh	r1, [r5, #4]                                       \n\
		                                                   \n\
	ldrh	r0, [r6, #8]                                       \n\
	ldrh	r1, [r7, #8]                                       \n\
	mul	r0, r3                                             \n\
	mul	r1, r4                                             \n\
	add	r2, r0, r2                                         \n\
	ldrh	r0, [r5, #8]                                       \n\
	add	r2, r1, r2                                         \n\
	mov	r1, r8                                             \n\
	add	r2, r0, r2                                         \n\
	and	r1, r2                                             \n\
	lsr	r2, r2, #15                                        \n\
	strh	r1, [r5, #6]                                       \n\
		                                                   \n\
	add	r5, r5, #8                                         \n\
	add	r6, r6, #8                                         \n\
	add	r7, r7, #8                                         \n\
	cmp	r5, r9                                             \n\
	bne	loop%=                                             \n\
		                                                   \n\
	str	r2, %[carry]                                       \n\
"
: [carry] "=m" (r)
: [xu] "m" (xu), [f] "m" (f), [d] "m" (d), [y] "m" (y),
	[m] "m" (m), [limit] "m" (limit)
: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9" );
		} else {
			r = 0;
		}
		v = len4;
#else
		r = 0;
		//#undef pgm_read_word
		const uint16_t *py;
		const uint16_t *pm;
		#define pgm_read_word2(addr)             (*(const uint16_t*)(addr))

		// py = &y[v];
		// if (0) {
		// 	if (((int)py) & 0x02) {
		// 		// unaligned -- NEVER TAKEN
		// 		py++;
		// 		t = *(uint32_t*)py;
		// 		y1 = t;
		// 		y2 = t >> 16;
		// 		py += 2;
		// 		t = *(uint32_t*)py;
		// 		y3 = t;
		// 		y4 = t >> 16;
		// 	} else {
		// 		// aligned
		// 		t = *(uint32_t*)py;
		// 		y1 = t >> 16;
		// 		py += 2;
		// 		t = *(uint32_t*)py;
		// 		y2 = t;
		// 		y3 = t >> 16;
		// 		py += 2;
		// 		t = *(uint32_t*)py;
		// 		y4 = t;
		// 	}
		// } else {
		// 	// py++;
		// 	// y1 = *py++;
		// 	// y2 = *py++;
		// 	// y3 = *py++;
		// 	// y4 = *py++;
		// 	// aligned
		// 	t = *(uint32_t*)py;
		// 	y1 = t >> 16;
		// 	py += 2;
		// 	t = *(uint32_t*)py;
		// 	y2 = t;
		// 	y3 = t >> 16;
		// 	py += 2;
		// 	t = *(uint32_t*)py;
		// 	y4 = t;
		// }
		//
		// pm = &m[v];
		// if (0) {
		// 	if (((int)py) & 0x02) {
		// 		// unaligned
		// 		pm++;
		// 		t = *(uint32_t*)pm;
		// 		m1 = t;
		// 		m2 = t >> 16;
		// 		pm += 2;
		// 		t = *(uint32_t*)pm;
		// 		m3 = t;
		// 		m4 = t >> 16;
		// 	} else {
		// 		// aligned
		// 		t = *(uint32_t*)pm;
		// 		m1 = t >> 16;
		// 		pm += 2;
		// 		t = *(uint32_t*)pm;
		// 		m2 = t;
		// 		m3 = t >> 16;
		// 		pm += 2;
		// 		t = *(uint32_t*)pm;
		// 		m4 = t;
		// 	}
		// } else {
		// 	pm++;
		// 	m1 = *pm++;
		// 	m2 = *pm++;
		// 	m3 = *pm++;
		// 	m4 = *pm++;
		// }


		py = &y[0];
		pm = &m[0];
		uint32_t ty, tm;
		if (!(((int)py) & 2) && !(((int)pm) & 2)) {
			// both are aligned to 32 bits
			ty = *(uint32_t*)py;		// pre-load with 32 bits value
			tm = *(uint32_t*)pm;
			for (v = 0; v < len4; v += 4) {
				uint16_t y1, y2, y3, y4;
				uint16_t m1, m2, m3, m4;
				uint32_t z;

				y1 = ty >> 16;		// +1
				m1 = tm >> 16;
				z = d[v + 1] + MUL15(xu, y1) + MUL15(f, m1) + r;
				r = z >> 15;
				d[v + 0] = z & 0x7FFF;
				//
				py += 2;
				ty = *(uint32_t*)py;
				pm += 2;
				tm = *(uint32_t*)pm;
				y2 = ty;
				m2 = tm;
				z = d[v + 2] + MUL15(xu, y2) + MUL15(f, m2) + r;
				r = z >> 15;
				d[v + 1] = z & 0x7FFF;
				//
				y3 = ty >> 16;
				m3 = tm >> 16;
				z = d[v + 3] + MUL15(xu, y3) + MUL15(f, m3) + r;
				r = z >> 15;
				d[v + 2] = z & 0x7FFF;
				//
				py += 2;
				ty = *(uint32_t*)py;
				y4 = ty;
				pm += 2;
				tm = *(uint32_t*)pm;
				m4 = tm;
				z = d[v + 4] + MUL15(xu, y4) + MUL15(f, m4) + r;
				r = z >> 15;
				d[v + 3] = z & 0x7FFF;
			}
		} else if (!(((int)py) & 2) && (((int)pm) & 2)) {
				pm--;
				ty = *(uint32_t*)py;		// pre-load with 32 bits value
				for (v = 0; v < len4; v += 4) {
					uint16_t y1, y2, y3, y4;
					uint16_t m1, m2, m3, m4;
					uint32_t z;

					y1 = ty >> 16;		// +1
					pm += 2;
					tm = *(uint32_t*)pm;
					m1 = tm;
					z = d[v + 1] + MUL15(xu, y1) + MUL15(f, m1) + r;
					r = z >> 15;
					d[v + 0] = z & 0x7FFF;
					//
					py += 2;
					ty = *(uint32_t*)py;
					y2 = ty;
					m2 = tm >> 16;
					z = d[v + 2] + MUL15(xu, y2) + MUL15(f, m2) + r;
					r = z >> 15;
					d[v + 1] = z & 0x7FFF;
					//
					y3 = ty >> 16;
					pm += 2;
					tm = *(uint32_t*)pm;
					m3 = tm;
					z = d[v + 3] + MUL15(xu, y3) + MUL15(f, m3) + r;
					r = z >> 15;
					d[v + 2] = z & 0x7FFF;
					//
					py += 2;
					ty = *(uint32_t*)py;
					y4 = ty;
					m4 = tm >> 16;
					z = d[v + 4] + MUL15(xu, y4) + MUL15(f, m4) + r;
					r = z >> 15;
					d[v + 3] = z & 0x7FFF;
				}
			} else if ((((int)py) & 2) && !(((int)pm) & 2)) {		// buggy
				// py unaligned, pm aligned
				py--;
				tm = *(uint32_t*)pm;
				for (v = 0; v < len4; v += 4) {
					uint16_t y1, y2, y3, y4;
					uint16_t m1, m2, m3, m4;
					uint32_t z;

					py += 2;
					ty = *(uint32_t*)py;
					y1 = ty;
					m1 = tm >> 16;
					z = d[v + 1] + MUL15(xu, y1) + MUL15(f, m1) + r;
					r = z >> 15;
					d[v + 0] = z & 0x7FFF;
					//
					y2 = ty >> 16;
					pm += 2;
					tm = *(uint32_t*)pm;
					m2 = tm;
					z = d[v + 2] + MUL15(xu, y2) + MUL15(f, m2) + r;
					r = z >> 15;
					d[v + 1] = z & 0x7FFF;
					//
					py += 2;
					ty = *(uint32_t*)py;
					y3 = ty;
					m3 = tm >> 16;
					z = d[v + 3] + MUL15(xu, y3) + MUL15(f, m3) + r;
					r = z >> 15;
					d[v + 2] = z & 0x7FFF;
					//
					y4 = ty >> 16;
					pm += 2;
					tm = *(uint32_t*)pm;
					m4 = tm;
					z = d[v + 4] + MUL15(xu, y4) + MUL15(f, m4) + r;
					r = z >> 15;
					d[v + 3] = z & 0x7FFF;
				}
			} else if ((((int)py) & 2) && (((int)pm) & 2)) {
					// py unaligned, pm unaligned
					py--;
					pm--;
					for (v = 0; v < len4; v += 4) {
						uint16_t y1, y2, y3, y4;
						uint16_t m1, m2, m3, m4;
						uint32_t z;

						py += 2;
						ty = *(uint32_t*)py;
						y1 = ty;		// +1
						pm += 2;
						tm = *(uint32_t*)pm;
						m1 = tm;
						z = d[v + 1] + MUL15(xu, y1) + MUL15(f, m1) + r;
						r = z >> 15;
						d[v + 0] = z & 0x7FFF;
						//
						y2 = ty >> 16;
						m2 = tm >> 16;
						z = d[v + 2] + MUL15(xu, y2) + MUL15(f, m2) + r;
						r = z >> 15;
						d[v + 1] = z & 0x7FFF;
						//
						py += 2;
						ty = *(uint32_t*)py;
						y3 = ty;
						pm += 2;
						tm = *(uint32_t*)pm;
						m3 = tm;
						z = d[v + 3] + MUL15(xu, y3) + MUL15(f, m3) + r;
						r = z >> 15;
						d[v + 2] = z & 0x7FFF;
						//
						y4 = ty >> 16;
						m4 = tm >> 16;
						z = d[v + 4] + MUL15(xu, y4) + MUL15(f, m4) + r;
						r = z >> 15;
						d[v + 3] = z & 0x7FFF;
					}
		} else {
				for (v = 0; v < len4; v += 4) {
					uint32_t z;
					z = d[v + 1] + MUL15(xu, pgm_read_word(&y[v + 1]))
						+ MUL15(f, pgm_read_word(&m[v + 1])) + r;
					r = z >> 15;
					d[v + 0] = z & 0x7FFF;
					z = d[v + 2] + MUL15(xu, pgm_read_word(&y[v + 2]))
						+ MUL15(f, pgm_read_word(&m[v + 2])) + r;
					r = z >> 15;
					d[v + 1] = z & 0x7FFF;
					z = d[v + 3] + MUL15(xu, pgm_read_word(&y[v + 3]))
						+ MUL15(f, pgm_read_word(&m[v + 3])) + r;
					r = z >> 15;
					d[v + 2] = z & 0x7FFF;
					z = d[v + 4] + MUL15(xu, pgm_read_word(&y[v + 4]))
						+ MUL15(f, pgm_read_word(&m[v + 4])) + r;
					r = z >> 15;
					d[v + 3] = z & 0x7FFF;
				}
			}


		// for (v = 0; v < len4; v += 4) {
		// 	uint32_t z;
		//
		// 	z = d[v + 1] + MUL15(xu, pgm_read_word(&y[v + 1]))
		// 		+ MUL15(f, pgm_read_word(&m[v + 1])) + r;
		// 	r = z >> 15;
		// 	d[v + 0] = z & 0x7FFF;
		// 	z = d[v + 2] + MUL15(xu, pgm_read_word(&y[v + 2]))
		// 		+ MUL15(f, pgm_read_word(&m[v + 2])) + r;
		// 	r = z >> 15;
		// 	d[v + 1] = z & 0x7FFF;
		// 	z = d[v + 3] + MUL15(xu, pgm_read_word(&y[v + 3]))
		// 		+ MUL15(f, pgm_read_word(&m[v + 3])) + r;
		// 	r = z >> 15;
		// 	d[v + 2] = z & 0x7FFF;
		// 	z = d[v + 4] + MUL15(xu, pgm_read_word(&y[v + 4]))
		// 		+ MUL15(f, pgm_read_word(&m[v + 4])) + r;
		// 	r = z >> 15;
		// 	d[v + 3] = z & 0x7FFF;
		// }
#endif
		for (; v < len; v ++) {
			uint32_t z;

			z = d[v + 1] + MUL15(xu, pgm_read_word(&y[v + 1]))
				+ MUL15(f, pgm_read_word(&m[v + 1])) + r;
			r = z >> 15;
			d[v + 0] = z & 0x7FFF;
		}

		zh = dh + r;
		d[len] = zh & 0x7FFF;
		dh = zh >> 15;
	}

	/*
	 * Restore the bit length (it was overwritten in the loop above).
	 */
	d[0] = pgm_read_word(&m[0]);

	/*
	 * d[] may be greater than m[], but it is still lower than twice
	 * the modulus.
	 */
	br_i15_sub(d, m, NEQ(dh, 0) | NOT(br_i15_sub(d, m, 0)));
}
