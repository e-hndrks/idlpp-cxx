
/*
 
COPYRIGHT
 
Copyright 1992, 1993, 1994 Sun Microsystems, Inc.  Printed in the United
States of America.  All Rights Reserved.
 
This product is protected by copyright and distributed under the following
license restricting its use.
 
The Interface Definition Language Compiler Front End (CFE) is made
available for your use provided that you include this license and copyright
notice on all media and documentation and the software program in which
this product is incorporated in whole or part. You may copy and extend
functionality (but may not remove functionality) of the Interface
Definition Language CFE without charge, but you are not authorized to
license or distribute it to anyone else except as part of a product or
program developed by you or with the express written consent of Sun
Microsystems, Inc. ("Sun").
 
The names of Sun Microsystems, Inc. and any of its subsidiaries or
affiliates may not be used in advertising or publicity pertaining to
distribution of Interface Definition Language CFE as permitted herein.
 
This license is effective until terminated by Sun for failure to comply
with this license.  Upon termination, you shall destroy or return all code
and documentation for the Interface Definition Language CFE.
 
INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED AS IS WITH NO WARRANTIES OF
ANY KIND INCLUDING THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF
DEALING, USAGE OR TRADE PRACTICE.
 
INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED WITH NO SUPPORT AND WITHOUT
ANY OBLIGATION ON THE PART OF Sun OR ANY OF ITS SUBSIDIARIES OR AFFILIATES
TO ASSIST IN ITS USE, CORRECTION, MODIFICATION OR ENHANCEMENT.
 
SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES SHALL HAVE NO LIABILITY WITH
RESPECT TO THE INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY
INTERFACE DEFINITION LANGUAGE CFE OR ANY PART THEREOF.
 
IN NO EVENT WILL SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES BE LIABLE FOR
ANY LOST REVENUE OR PROFITS OR OTHER SPECIAL, INDIRECT AND CONSEQUENTIAL
DAMAGES, EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 
Use, duplication, or disclosure by the government is subject to
restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227-7013 and FAR
52.227-19.
 
Sun, Sun Microsystems and the Sun logo are trademarks or registered
trademarks of Sun Microsystems, Inc.
 
SunSoft, Inc.  
2550 Garcia Avenue 
Mountain View, California  94043
 
NOTE:
 
SunOS, SunSoft, Sun, Solaris, Sun Microsystems or the Sun logo are
trademarks or registered trademarks of Sun Microsystems, Inc.
 
 */


// utl_wstring.cc - Implementation of quick and dirty TEMPORARY WString
//     for IDL compiler

#include "idl.h"
#include "idl_extern.h"
#include "os_stdlib.h"

/*
 * Constructors
 */

UTL_WString::UTL_WString() : p_str(NULL), len(0), alloced(0)
{}

UTL_WString::UTL_WString(const char *str)
{
   if (str == NULL)
   {
      len = alloced = 0;
      p_str = c_str = NULL;
   }
   else
   {
      len = strlen(str);
      alloced = len + 1;
      p_str = new char [alloced];
      c_str = new char [alloced];
      os_strcpy(p_str, str);
      canonicalize();
   }
}

UTL_WString::UTL_WString(unsigned long maxlen)
{
   len = maxlen;
   alloced = maxlen + 1;
   p_str = new char [alloced];
   c_str = new char [alloced];
   p_str[0] = '\0';
   c_str[0] = '\0';
}

UTL_WString::UTL_WString(UTL_WString *s)
{
   char *b;

   if (s == NULL)
   {
      p_str = c_str = NULL;
      alloced = len = 0;
   }
   else
   {
      b = s->get_string();

      if (b == NULL)
      {
         p_str = c_str = NULL;
         alloced = len = 0;
      }
      else
      {
         len = strlen(b);
         alloced = len + 1;
         p_str = new char [alloced];
         c_str = new char [alloced];
         os_strcpy(p_str, b);
         canonicalize();
      }
   }
}

/*
 * Private operations
 */

// Compute a canonical form for this string. This is (implemented as)
// a corresponding string with all upper case characters where the
// original has lower case characters, identical characters otherwise
void
UTL_WString::canonicalize()
{
   unsigned long i;

   for (i = 0; i < len; i++)
      c_str[i] = isalpha(p_str[i]) ? toupper(p_str[i]) : p_str[i];

   c_str[i] = '\0';
}

/*
 * Public operations
 */

// Compare two WString *
bool UTL_WString::compare(UTL_WString *s)
{
   char *s_c_str;
   bool result;

   if (c_str == NULL || s == NULL || (s_c_str = s->get_canonical_rep()) == NULL)
      result = false;
   else
      result = (strcmp(c_str, s_c_str) == 0) ? true : false;

   /*
    * Check that the names are typed consistently
    */
   if (result && strcmp(p_str, s->get_string()) != 0)
      idl_global->err()->name_case_error(p_str, s->get_string());

   return result;
}

// Get the char * from a WString
char *
UTL_WString::get_string()
{
   return p_str;
}

// Get the canonical representation from a WString
char *
UTL_WString::get_canonical_rep()
{
   if (c_str == NULL)
   {
      c_str = new char [alloced];
      canonicalize();
   }

   return c_str;
}

/*
 * Redefined virtual operations
 */

// AST Dumping
void
UTL_WString::dump(ostream &o)
{
   o << p_str;
}
