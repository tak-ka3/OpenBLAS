#include "common.h"
#include <riscv_vector.h>

#define KERNEL8x4_I \
	"addi       t1,    %[PB], 1*8  \n\t"\
	"addi       t2,    %[PB], 2*8  \n\t"\
	"addi       t3,    %[PB], 3*8  \n\t"\
	"fld        ft0,  (%[PB])      \n\t"\
	"fld        ft1,  (t1)         \n\t"\
	"fld        ft2,  (t2)         \n\t"\
	"fld        ft3,  (t3)         \n\t"\
	"vle64.v      v0,   (%[PA])      \n\t"\
	"addi       t4,    %[PA], 2*8  \n\t"\
	"addi       t5,    %[PA], 4*8  \n\t"\
	"vfmv.v.f   v8,   ft0          \n\t"\
	"addi       t6,    %[PA], 6*8  \n\t"\
	"addi       %[PA], %[PA], 8*8  \n\t"\
	"vle64.v      v1,   (t4)         \n\t"\
	"addi       t4,    t4,    8*8  \n\t"\
	"vfmv.v.f   v9,   ft1          \n\t"\
	"vle64.v      v2,   (t5)         \n\t"\
	"addi       t5,    t5,    8*8  \n\t"\
	"vle64.v      v3,   (t6)         \n\t"\
	"addi       t6,    t6,    8*8  \n\t"\
	"vfmv.v.f   v10,  ft2          \n\t"\
	"addi       %[PB], %[PB], 4*8  \n\t"\
	"vle64.v      v4,   (%[PA])      \n\t"\
	"addi       %[PA], %[PA], 8*8  \n\t"\
	"vfmv.v.f   v11,  ft3          \n\t"\
	"vfmacc.vv  v16,  v8,    v0   \n\t"\
	"addi       t1,   t1,     4*8  \n\t"\
	"vle64.v      v5,   (t4)         \n\t"\
	"addi       t4,    t4,    8*8  \n\t"\
	"vfmacc.vv  v17,  v8,    v1   \n\t"\
	"addi       t2,   t2,     4*8  \n\t"\
	"vle64.v      v6,   (t5)         \n\t"\
	"addi       t5,    t5,    8*8  \n\t"\
	"vfmacc.vv  v18,  v8,    v2   \n\t"\
	"addi       t3,   t3,     4*8  \n\t"\
	"vle64.v      v7,   (t6)         \n\t"\
	"addi       t6,    t6,    8*8  \n\t"\
	"vfmacc.vv  v19,  v8,    v3   \n\t"\
	"fld        ft4,  (%[PB])   \n\t"\
	"vfmacc.vv  v20,  v9,    v0   \n\t"\
	"fld        ft5,  (t1)        \n\t"\
	"vfmacc.vv  v21,  v9,    v1   \n\t"\
	"fld        ft6,  (t2)        \n\t"\
	"vfmacc.vv  v22,  v9,    v2   \n\t"\
	"fld        ft7,  (t3)        \n\t"\
	"vfmacc.vv  v23,  v9,    v3   \n\t"\
	"vfmv.v.f   v12,  ft4          \n\t"\
	"vfmacc.vv  v24,  v10,    v0    \n\t"\
	"vfmv.v.f   v13,  ft5          \n\t"\
	"vfmacc.vv  v25,  v10,    v1    \n\t"\
	"vfmv.v.f   v14,  ft6          \n\t"\
	"vfmacc.vv  v26,  v10,    v2    \n\t"\
	"vfmv.v.f   v15,  ft7          \n\t"\
	"vfmacc.vv  v27,  v10,    v3    \n\t"\
        "addi       %[PB], %[PB], 4*8  \n\t"\
	"vfmacc.vv  v28,  v11,    v0    \n\t"\
	"addi       t1,   t1,     4*8  \n\t"\
	"vfmacc.vv  v29,  v11,    v1    \n\t"\
	"addi       t2,   t2,     4*8  \n\t"\
	"vfmacc.vv  v30,  v11,    v2    \n\t"\
	"addi       t3,   t3,     4*8  \n\t"\
	"vfmacc.vv  v31,  v11,    v3    \n\t"

#define KERNEL8x4_M1 \
	"vfmacc.vv  v16,  v8,    v0   \n\t"\
	"vle64.v      v4,   (%[PA])      \n\t"\
	"addi       %[PA], %[PA], 8*8  \n\t"\
	"vfmacc.vv  v17,  v8,    v1   \n\t"\
	"vle64.v      v5,   (t4)         \n\t"\
	"addi       t4,    t4,    8*8  \n\t"\
	"vfmacc.vv  v18,  v8,    v2   \n\t"\
	"vle64.v      v6,   (t5)         \n\t"\
	"addi       t5,    t5,    8*8  \n\t"\
	"vfmacc.vv  v19,  v8,    v3   \n\t"\
	"vle64.v      v7,   (t6)         \n\t"\
	"addi       t6,    t6,    8*8  \n\t"\
	"vfmacc.vv  v20,  v9,    v0   \n\t"\
	"fld        ft4,  (%[PB])      \n\t"\
	"vfmacc.vv  v21,  v9,    v1   \n\t"\
	"fld        ft5,  (t1)        \n\t"\
	"vfmacc.vv  v22,  v9,    v2   \n\t"\
	"fld        ft6,  (t2)        \n\t"\
	"vfmacc.vv  v23,  v9,    v3   \n\t"\
	"fld        ft7,  (t3)        \n\t"\
        "addi       %[PB], %[PB], 4*8  \n\t"\
	"vfmacc.vv  v24,  v10,    v0   \n\t"\
	"addi       t1,   t1,     4*8  \n\t"\
	"vfmacc.vv  v25,  v10,    v1   \n\t"\
	"vfmv.v.f   v12,  ft4          \n\t"\
	"vfmacc.vv  v26,  v10,    v2   \n\t"\
	"addi       t2,   t2,     4*8  \n\t"\
	"vfmacc.vv  v27,  v10,    v3   \n\t"\
	"vfmv.v.f   v13,  ft5          \n\t"\
	"vfmacc.vv  v28,  v11,    v0   \n\t"\
	"addi       t3,   t3,     4*8  \n\t"\
	"vfmacc.vv  v29,  v11,    v1   \n\t"\
	"vfmv.v.f   v14,  ft6          \n\t"\
	"vfmacc.vv  v30,  v11,    v2   \n\t"\
	"vfmacc.vv  v31,  v11,    v3   \n\t"\
	"vfmv.v.f   v15,  ft7          \n\t"

#define KERNEL8x4_M2 \
	"vfmacc.vv  v16,  v12,    v4   \n\t"\
	"vle64.v      v0,   (%[PA])      \n\t"\
	"addi       %[PA], %[PA], 8*8  \n\t"\
	"vfmacc.vv  v17,  v12,    v5   \n\t"\
	"vle64.v      v1,   (t4)         \n\t"\
	"addi       t4,    t4,    8*8  \n\t"\
	"vfmacc.vv  v18,  v12,    v6   \n\t"\
	"vle64.v      v2,   (t5)         \n\t"\
	"addi       t5,    t5,    8*8  \n\t"\
	"vfmacc.vv  v19,  v12,    v7   \n\t"\
	"vle64.v      v3,   (t6)         \n\t"\
	"addi       t6,    t6,    8*8  \n\t"\
	"vfmacc.vv  v20,  v13,    v4   \n\t"\
	"fld        ft0,  (%[PB])      \n\t"\
	"vfmacc.vv  v21,  v13,    v5   \n\t"\
	"fld        ft1,  (t1)         \n\t"\
	"vfmacc.vv  v22,  v13,    v6   \n\t"\
	"fld        ft2,  (t2)         \n\t"\
	"vfmacc.vv  v23,  v13,    v7   \n\t"\
	"fld        ft3,  (t3)         \n\t"\
        "addi       %[PB], %[PB], 4*8  \n\t"\
	"vfmacc.vv  v24,  v14,    v4   \n\t"\
	"addi       t1,   t1,     4*8  \n\t"\
	"vfmacc.vv  v25,  v14,    v5   \n\t"\
	"vfmv.v.f   v8,   ft0          \n\t"\
	"vfmacc.vv  v26,  v14,    v6   \n\t"\
	"addi       t2,   t2,     4*8  \n\t"\
	"vfmacc.vv  v27,  v14,    v7   \n\t"\
	"vfmv.v.f   v9,   ft1          \n\t"\
	"vfmacc.vv  v28,  v15,    v4   \n\t"\
	"addi       t3,   t3,     4*8  \n\t"\
	"vfmacc.vv  v29,  v15,    v5   \n\t"\
	"vfmv.v.f   v10,  ft2          \n\t"\
	"vfmacc.vv  v30,  v15,    v6   \n\t"\
	"vfmacc.vv  v31,  v15,    v7   \n\t"\
	"vfmv.v.f   v11,  ft3          \n\t"

#define KERNEL8x4_E \
	"vfmacc.vv  v16,  v12,    v4   \n\t"\
	"vfmacc.vv  v17,  v12,    v5   \n\t"\
	"vfmacc.vv  v18,  v12,    v6   \n\t"\
	"vfmacc.vv  v19,  v12,    v7   \n\t"\
	"vfmacc.vv  v20,  v13,    v4   \n\t"\
	"vfmacc.vv  v21,  v13,    v5   \n\t"\
	"vfmacc.vv  v22,  v13,    v6   \n\t"\
	"vfmacc.vv  v23,  v13,    v7   \n\t"\
	"vfmacc.vv  v24,  v14,    v4   \n\t"\
	"vfmacc.vv  v25,  v14,    v5   \n\t"\
	"vfmacc.vv  v26,  v14,    v6   \n\t"\
	"vfmacc.vv  v27,  v14,    v7   \n\t"\
	"vfmacc.vv  v28,  v15,    v4   \n\t"\
	"vfmacc.vv  v29,  v15,    v5   \n\t"\
	"vfmacc.vv  v30,  v15,    v6   \n\t"\
	"vfmacc.vv  v31,  v15,    v7   \n\t"




int CNAME(BLASLONG bm,BLASLONG bn,BLASLONG bk,FLOAT alpha,FLOAT* ba,FLOAT* bb,FLOAT* C,BLASLONG ldc
#ifdef TRMMKERNEL
		,BLASLONG offset
#endif
		)
{
   BLASLONG i,j,k;
   FLOAT *C0,*C1,*C2,*C3;
   FLOAT *ptrba,*ptrbb;
   
   FLOAT loadb0,loadb1,loadb2,loadb3;
   FLOAT load0,load1,load2,load3,load4,load5,load6,load7;

   FLOAT res0,res1,res2,res3;
   FLOAT res4,res5,res6,res7;
   FLOAT res8,res9,res10,res11;
   FLOAT res12,res13,res14,res15;

   for (j=0; j<bn/4; j+=1){
	   C0 = C;
	   C1 = C0+ldc;
	   C2 = C1+ldc;
	   C3 = C2+ldc;

	   ptrba = ba;
	   for(i=0; i<bm/8; i+=1){
		   ptrbb = bb;
		   //t0 for k
		   //ft0-ft3,ft4-ft7,v8-v15 for B, t1-t3 for PB1-3
		   //v0-v3,v4-v7 for A, t4-t6 for PA1-3
		   //v16-v31 for temp C
		   
		   asm volatile(
				"vsetvli    zero, zero, e64,m1 \n\t"
				"fmv.w.x    ft11, zero         \n\t"
				"mv         t0,   %[BK]        \n\t"
				
				"vfmv.v.f   v16,  ft11         \n\t"
				"vfmv.v.f   v17,  ft11         \n\t"
				"vfmv.v.f   v18,  ft11         \n\t"
				"vfmv.v.f   v19,  ft11         \n\t"

				"vfmv.v.f   v20,  ft11         \n\t"
				"vfmv.v.f   v21,  ft11         \n\t"
				"vfmv.v.f   v22,  ft11         \n\t"
				"vfmv.v.f   v23,  ft11         \n\t"

				"vfmv.v.f   v24,  ft11         \n\t"
				"vfmv.v.f   v25,  ft11         \n\t"
				"vfmv.v.f   v26,  ft11         \n\t"
				"vfmv.v.f   v27,  ft11         \n\t"
				
				"vfmv.v.f   v28,  ft11         \n\t"
				"vfmv.v.f   v29,  ft11         \n\t"
				"vfmv.v.f   v30,  ft11         \n\t"
				"vfmv.v.f   v31,  ft11         \n\t"
				//unloop 8, so the number of loop is divided by 8
				"srli       t0,   %[BK], 3     \n\t"
				"blez       t0,   M8x4_TAIL    \n\t"
				
				//preloop
				KERNEL8x4_I
				KERNEL8x4_M2
				KERNEL8x4_M1
				KERNEL8x4_M2
				"addi       t0,   t0, -1       \n\t"
				"blez       t0,   M8x4_MAINLOOP_TAIL    \n\t"
				".align 4                      \n\t"
				"M8x4_MAINLOOP:                \n\t"
				KERNEL8x4_M1
				KERNEL8x4_M2
				KERNEL8x4_M1
				KERNEL8x4_M2
				KERNEL8x4_M1
				KERNEL8x4_M2
				KERNEL8x4_M1
				KERNEL8x4_M2
				"addi       t0,   t0, -1       \n\t"
				"bgtz       t0,   M8x4_MAINLOOP \n\t"
				
				"M8x4_MAINLOOP_TAIL:           \n\t"
				KERNEL8x4_M1
				KERNEL8x4_M2
				KERNEL8x4_M1
				KERNEL8x4_E
				
				//tail
				"M8x4_TAIL:                    \n\t"
				"andi       t0,   %[BK], 7     \n\t"
				"blez       t0,   M8x4_SAVERESULT   \n\t"

				"addi       t4,    %[PA], 2*8  \n\t"
				"addi       t5,    %[PA], 4*8  \n\t"
				"addi       t6,    %[PA], 6*8  \n\t"
				"addi       t1,    %[PB], 1*8  \n\t"
				"addi       t2,    %[PB], 2*8  \n\t"
				"addi       t3,    %[PB], 3*8  \n\t"

				".align 4                      \n\t"
				"M8x4_TAILLOOP:                \n\t"
				"fld        ft0,  (%[PB])      \n\t"
				"addi       %[PB], %[PB], 4*8  \n\t"
				"vle64.v      v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*8  \n\t"
				"vle64.v      v1,   (t4)         \n\t"
				"addi       t4,    t4,    8*8  \n\t"

				"vfmv.v.f   v8,   ft0          \n\t"
				"fld        ft1,  (t1)         \n\t"
				"addi       t1,   t1,     4*8  \n\t"
				"vle64.v      v2,   (t5)         \n\t"
				"addi       t5,    t5,    8*8  \n\t"
				"vle64.v      v3,   (t6)         \n\t"
				"addi       t6,    t6,    8*8  \n\t"

				"vfmacc.vv  v16,  v8,    v0    \n\t"
				"fld        ft2,  (t2)         \n\t"
				"addi       t2,   t2,     4*8  \n\t"
				"vfmacc.vv  v17,  v8,    v1    \n\t"
				"vfmacc.vv  v18,  v8,    v2    \n\t"
				"vfmv.v.f   v9,   ft1          \n\t"
				"vfmacc.vv  v19,  v8,    v3    \n\t"
								

				"vfmacc.vv  v20,  v9,    v0    \n\t"
				"fld        ft3,  (t3)         \n\t"
				"addi       t3,   t3,     4*8  \n\t"
				"vfmacc.vv  v21,  v9,    v1    \n\t"
				"vfmacc.vv  v22,  v9,    v2    \n\t"
				"vfmv.v.f   v10,  ft2          \n\t"
				"vfmacc.vv  v23,  v9,    v3    \n\t"

				"vfmv.v.f   v11,  ft3          \n\t"
				"vfmacc.vv  v24,  v10,    v0    \n\t"
				"vfmacc.vv  v25,  v10,    v1    \n\t"
				"vfmacc.vv  v26,  v10,    v2    \n\t"
				"vfmacc.vv  v27,  v10,    v3    \n\t"

				"vfmacc.vv  v28,  v11,    v0    \n\t"
				"vfmacc.vv  v29,  v11,    v1    \n\t"
				"vfmacc.vv  v30,  v11,    v2    \n\t"
				"vfmacc.vv  v31,  v11,    v3    \n\t"

				"addi       t0,   t0, -1       \n\t"
				"bgtz       t0,   M8x4_TAILLOOP \n\t"
				
				//Save result
				//load C
				"M8x4_SAVERESULT:              \n\t"
				//use v8 to store alpha
				"vfmv.v.f   v8,   %[ALPHA]     \n\t"
				"vle64.v      v0,   (%[C0])      \n\t"
				"addi       t4,   %[C0], 2*8   \n\t"
				"vle64.v      v1,   (%[C1])      \n\t"
				"addi       t5,   %[C1], 2*8   \n\t"
				"vle64.v      v2,   (%[C2])      \n\t"
				"addi       t6,   %[C2], 2*8   \n\t"
				"vle64.v      v3,   (%[C3])      \n\t"
				"addi       t3,   %[C3], 2*8   \n\t"
				
				//Multiply Alpha
				"vfmacc.vv  v0,   v8, v16 \n\t"
				"vle64.v      v4,   (t4)          \n\t"
				"vfmacc.vv  v1,   v8, v20 \n\t"
				"vle64.v      v5,   (t5)          \n\t"
				"vfmacc.vv  v2,   v8, v24 \n\t"
				"vle64.v      v6,   (t6)          \n\t"
				"vfmacc.vv  v3,   v8, v28 \n\t"
				"vle64.v      v7,   (t3)          \n\t"

				"vfmacc.vv  v4,   v8, v17 \n\t"
				"vse64.v      v0,   (%[C0])      \n\t"
				"add        %[C0], %[C0], 4*8  \n\t"
				"vfmacc.vv  v5,   v8, v21 \n\t"
				"vse64.v      v1,   (%[C1])      \n\t"
				"add        %[C1], %[C1], 4*8  \n\t"
				
				"vfmacc.vv  v6,   v8, v25 \n\t"
				"vse64.v      v2,   (%[C2])      \n\t"
				"add        %[C2], %[C2], 4*8  \n\t"

				"vfmacc.vv  v7,   v8, v29 \n\t"
				"vse64.v      v3,   (%[C3])      \n\t"
				"add        %[C3], %[C3], 4*8  \n\t"

				"vle64.v      v0,   (%[C0])      \n\t"
				"vse64.v      v4,   (t4)         \n\t"
				"add        t4,   t4,     4*8  \n\t"
				
				"vle64.v      v1,   (%[C1])      \n\t"
				"vse64.v      v5,   (t5)         \n\t"
				"add        t5,   t5,     4*8  \n\t"

				"vle64.v      v2,   (%[C2])      \n\t"
				"vse64.v      v6,   (t6)         \n\t"
				"add        t6,   t6,     4*8  \n\t"

				"vle64.v      v3,   (%[C3])      \n\t"
				"vse64.v      v7,   (t3)         \n\t"
				"add        t3,   t3,     4*8  \n\t"


				"vfmacc.vv  v0,   v8, v18 \n\t"
				"vle64.v      v4,   (t4)          \n\t"
				"vfmacc.vv  v1,   v8, v22 \n\t"
				"vle64.v      v5,   (t5)          \n\t"
				"vfmacc.vv  v2,   v8, v26 \n\t"
				"vle64.v      v6,   (t6)          \n\t"
				"vfmacc.vv  v3,   v8, v30 \n\t"
				"vle64.v      v7,   (t3)          \n\t"

				"vfmacc.vv  v4,   v8, v19 \n\t"
				"vse64.v      v0,   (%[C0])      \n\t"
				"add        %[C0], %[C0], 4*8  \n\t"

				"vfmacc.vv  v5,   v8, v23 \n\t"
				"vse64.v      v1,   (%[C1])      \n\t"
				"add        %[C1], %[C1], 4*8  \n\t"

				"vfmacc.vv  v6,   v8, v27 \n\t"
				"vse64.v      v2,   (%[C2])      \n\t"
				"add        %[C2], %[C2], 4*8  \n\t"

				"vfmacc.vv  v7,   v8, v31 \n\t"
				"vse64.v      v3,   (%[C3])      \n\t"
				"add        %[C3], %[C3], 4*8  \n\t"

				"vse64.v      v4,   (t4)         \n\t"
				"vse64.v      v5,   (t5)         \n\t"
				"vse64.v      v6,   (t6)         \n\t"
				"vse64.v      v7,   (t3)         \n\t"
				"M8x4_END:                     \n\t"
				
				// "r" = read only, "=r" = write only, "+r" = read and write
				// "f" = determined to use float register
				:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", "t4","t5","t6","t3","t1","t2",
				 "ft11", "ft0", "ft1", "ft2","ft3","ft4", "ft5", "ft6","ft7",
				 "v0", "v1", "v2", "v3","v4", "v5", "v6", "v7",
				 "v8", "v9", "v10", "v11","v12", "v13", "v14", "v15",
				 "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23",
				 "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31");
	   }
	   // if bm%8 != 0, 残りの要素を計算する。bm%8=5ならbm&4, bm&1の2つが実行される
	   if(bm&4){
		   ptrbb = bb;
      		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

			   res4 = res4 + load0 * loadb1;
			   res5 = res5 + load1 * loadb1;
			   res6 = res6 + load2 * loadb1;
			   res7 = res7 + load3 * loadb1;

			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
   			   res8 = res8 + load0 * loadb2;
			   res9 = res9 + load1 * loadb2;
			   res10 = res10 + load2 * loadb2;
			   res11 = res11 + load3 * loadb2;

			   res12 = res12 + load0 * loadb3;
			   res13 = res13 + load1 * loadb3;
			   res14 = res14 + load2 * loadb3;
			   res15 = res15 + load3 * loadb3;

			   ptrba += 4;
			   ptrbb += 4;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   
		   C1[0] += res4;
		   C1[1] += res5;
		   C1[2] += res6;
		   C1[3] += res7;

   		   C2[0] += res8;
		   C2[1] += res9;
		   C2[2] += res10;
		   C2[3] += res11;
		   
		   C3[0] += res12;
		   C3[1] += res13;
		   C3[2] += res14;
		   C3[3] += res15;

		   C0 += 4;
		   C1 += 4;
		   C2 += 4;
		   C3 += 4;
	   }
   	   if(bm&2){
		   ptrbb = bb;
		   
       		   res0 = 0;
		   res1 = 0;
		   
		   res4 = 0;
		   res5 = 0;
		   
		   res8 = 0;
		   res9 = 0;
		   
		   res12 = 0;
		   res13 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;

			   res4 = res4 + load0 * loadb1;
			   res5 = res5 + load1 * loadb1;

			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
   			   res8 = res8 + load0 * loadb2;
			   res9 = res9 + load1 * loadb2;

			   res12 = res12 + load0 * loadb3;
			   res13 = res13 + load1 * loadb3;

			   ptrba += 2;
			   ptrbb += 4;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;

		   res4 = res4 * alpha;
		   res5 = res5 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;

		   res12 = res12 * alpha;
		   res13 = res13 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;

		   C1[0] += res4;
		   C1[1] += res5;

   		   C2[0] += res8;
		   C2[1] += res9;
		   
		   C3[0] += res12;
		   C3[1] += res13;

		   C0 += 2;
		   C1 += 2;
		   C2 += 2;
		   C3 += 2;
	   }
	   if(bm&1){
		   ptrbb = bb;
		   		   
       		   res0 = 0;
		   
		   res4 = 0;
		   
		   res8 = 0;
		   
		   res12 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
				   
			   res0 = res0 + load0 * loadb0;

			   res4 = res4 + load0 * loadb1;

			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
   			   res8 = res8 + load0 * loadb2;

			   res12 = res12 + load0 * loadb3;

			   ptrba += 1;
			   ptrbb += 4;
		   }
		   
      		   res0 = res0 * alpha;

		   res4 = res4 * alpha;

       		   res8 = res8 * alpha;

		   res12 = res12 * alpha;

		   C0[0] += res0;
		   C1[0] += res4;
   		   C2[0] += res8;
		   C3[0] += res12;

		   C0 += 1;
		   C1 += 1;
		   C2 += 1;
		   C3 += 1;
	   }
	   
	   k = bk<<2;
	   bb = bb+k;
	   i = ldc<<2;
	   C = C+i;
   }
   
   if(bn&2){
	   C0 = C;
	   C1 = C0+ldc;

	   ptrba = ba;
	   for(i=0; i<bm/8; i+=1){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
			   load4 = ptrba[4];
			   load5 = ptrba[5];
			   load6 = ptrba[6];
			   load7 = ptrba[7];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

			   res4 = res4 + load4 * loadb0;
			   res5 = res5 + load5 * loadb0;
			   res6 = res6 + load6 * loadb0;
			   res7 = res7 + load7 * loadb0;

   			   res8 = res8 + load0 * loadb1;
			   res9 = res9 + load1 * loadb1;
			   res10 = res10 + load2 * loadb1;
			   res11 = res11 + load3 * loadb1;

			   res12 = res12 + load4 * loadb1;
			   res13 = res13 + load5 * loadb1;
			   res14 = res14 + load6 * loadb1;
			   res15 = res15 + load7 * loadb1;

			   ptrba += 8;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   C0[4] += res4;
		   C0[5] += res5;
		   C0[6] += res6;
		   C0[7] += res7;

   		   C1[0] += res8;
		   C1[1] += res9;
		   C1[2] += res10;
		   C1[3] += res11;
		   C1[4] += res12;
		   C1[5] += res13;
		   C1[6] += res14;
		   C1[7] += res15;

		   C0 += 8;
		   C1 += 8;
	   }
	   if(bm&4){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

   			   res8 = res8 + load0 * loadb1;
			   res9 = res9 + load1 * loadb1;
			   res10 = res10 + load2 * loadb1;
			   res11 = res11 + load3 * loadb1;

			   ptrba += 4;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;

   		   C1[0] += res8;
		   C1[1] += res9;
		   C1[2] += res10;
		   C1[3] += res11;

		   C0 += 4;
		   C1 += 4;
	   }
   	   if(bm&2){
		   ptrbb = bb;
      		   res0 = 0;
		   res1 = 0;
		   
		   res8 = 0;
		   res9 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;

   			   res8 = res8 + load0 * loadb1;
			   res9 = res9 + load1 * loadb1;

			   ptrba += 2;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;

   		   C1[0] += res8;
		   C1[1] += res9;
		   
		   C0 += 2;
		   C1 += 2;
	   }
	   if(bm&1){
		   ptrbb = bb;
       		   res0 = 0;
		   res8 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];
			   load0 = ptrba[0];
				   
			   res0 = res0 + load0 * loadb0;
   			   res8 = res8 + load0 * loadb1;
			   ptrba += 1;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
       		   res8 = res8 * alpha;

		   C0[0] += res0;
   		   C1[0] += res8;
		   
		   C0 += 1;
		   C1 += 1;
	   }
	   k = bk<<1;
	   bb = bb+k;
	   i = ldc<<1;
	   C = C+i;
   }

   if (bn&1){
	   C0 = C;
	   ptrba = ba;
	   for(i=0; i<bm/8; i+=1){
		   ptrbb = bb;
		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;

		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;
			   res2 = res2 + ptrba[2] * loadb0;
			   res3 = res3 + ptrba[3] * loadb0;

			   res4 = res4 + ptrba[4] * loadb0;
			   res5 = res5 + ptrba[5] * loadb0;
			   res6 = res6 + ptrba[6] * loadb0;
			   res7 = res7 + ptrba[7] * loadb0;
			   
			   ptrba += 8;
			   ptrbb += 1;
		   }
   		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   C0[4] += res4;
		   C0[5] += res5;
		   C0[6] += res6;
		   C0[7] += res7;
		   
		   C0 += 8;
	   }
	   if(bm&4){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;
			   res2 = res2 + ptrba[2] * loadb0;
			   res3 = res3 + ptrba[3] * loadb0;

			   ptrba += 4;
			   ptrbb += 1;
		   }
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   
		   C0 += 4;
	   }
   	   if(bm&2){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;

			   ptrba += 2;
			   ptrbb += 1;
		   }
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   
		   C0 += 2;
	   }
	   if(bm&1){
   		   ptrbb = bb;
   		   res0 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   ptrba += 1;
			   ptrbb += 1;
		   }
      		   res0 = res0 * alpha;
		   C0[0] += res0;
		   C0 += 1;
	   }

	   k = bk;
	   bb = bb+k;
	   C = C+ldc;
   }
   return 0;
}
