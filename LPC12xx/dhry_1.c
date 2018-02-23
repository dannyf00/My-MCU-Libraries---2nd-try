#include "dhry.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOOPS   10000

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [25];        /* <-- changed from 50 */
int             Arr_2_Glob [25] [25];   /* <-- changed from 50 */

char Reg_Define[] = "Register option selected.";

#ifndef ROPT
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
#define REG register
#endif


/* end of variables for time measurement */

void Proc_1( REG Rec_Pointer Ptr_Val_Par );
void Proc_2( One_Fifty * Int_Par_Ref );
void Proc_3( Rec_Pointer * Ptr_Ref_Par );
void Proc_4( void );
void Proc_5( void );



void Proc_1( REG Rec_Pointer Ptr_Val_Par )
/******************/
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */

  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp,
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10,
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


void Proc_2( One_Fifty * Int_Par_Ref )
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */
{
  One_Fifty  Int_Loc;
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_3( Rec_Pointer * Ptr_Ref_Par )
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */
{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


void Proc_4( void ) /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */


void Proc_5( void ) /* without parameters */
/*******/
    /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */

Rec_Type  __Rec_Type1;
Rec_Type  __Rec_Type2;

void dhrystone (void)

{

        One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   int             Run_Index;
  REG   int             Number_Of_Runs;


  Next_Ptr_Glob = &__Rec_Type1;//(Rec_Pointer)emalloc (sizeof (Rec_Type));
  Ptr_Glob = &__Rec_Type2;//(Rec_Pointer)emalloc (sizeof (Rec_Type));

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob->variant.var_1.Str_Comp,
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */


  Number_Of_Runs=LOOPS;


    for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
       {

         Proc_5();
         Proc_4();
           /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
         Int_1_Loc = 2;
         Int_2_Loc = 3;
         strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
         Enum_Loc = Ident_2;
         Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
           /* Bool_Glob == 1 */
         while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
         {
           Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
             /* Int_3_Loc == 7 */
           Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
             /* Int_3_Loc == 7 */
           Int_1_Loc += 1;
         }   /* while */
            /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
         Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
           /* Int_Glob == 5 */
         Proc_1 (Ptr_Glob);
         for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                              /* loop body executed twice */
         {
           if (Enum_Loc == Func_1 (Ch_Index, 'C'))
               /* then, not executed */
             {
               Proc_6 (Ident_1, &Enum_Loc);
               strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
               Int_2_Loc = Run_Index;
               Int_Glob = Run_Index;
             }
         }
           /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
         Int_2_Loc = Int_2_Loc * Int_1_Loc;
         Int_1_Loc = Int_2_Loc / Int_3_Loc;
         Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
           /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
         Proc_2 (&Int_1_Loc);
           /* Int_1_Loc == 5 */

       }   /* loop "for Run_Index" */


}
