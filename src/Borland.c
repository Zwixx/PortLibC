/*
 * =====================================================================================
 *
 *       Filename:  Borland.c
 *
 *    Description:  Various Borland function replacements
 *
 *        Version:  1.0
 *        Created:  08/24/2017 10:00:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  surkeh@protonmail.com
 *
 * =====================================================================================
 */
#include "Borland.h"




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fnsplit
 *  Description:  Separates a path into components
 *         NOTE:  Does not handle wildcard * due to shell handling this in Linux
 *       Return:  int, bitflags of what components were found in path, NULL args included
 *     Argument:  const char *, Valid Windows/Posix path
 *     Argument:  char *, Returns drive component, if not NULL and drive was found
 *     Argument:  char *, Returns directory component, if not NULL and dir was found
 *     Argument:  char *, Returns file name component, if not NULL and dir was found
 *     Argument:  char *, Returns extension component, if not NULL and dir was found
 * =====================================================================================
 */
int fnsplit(const char *path, 
                   char *drive, 
                   char *dir, 
                   char *name,
                   char *ext) 
{
  int i = 0;  // for loop iterator set after drive letter, if needed
  int flags = 0;

  if (path != NULL) {

    // Code using fnsplit suggests first char of all return args is set to NULL
    // (Undocumented behavior, could be sample code misusing fnsplit)
    if (drive != NULL)
      drive[0] = '\0';
    if (dir != NULL)
      dir[0] =   '\0';
    if (name != NULL)
      name[0] =  '\0';
    if (ext != NULL)
      ext[0] =   '\0';

  // Check for character denoting drive letter
    if (path[1] == ':') {
      flags |= DRIVE;
      if (drive != NULL) {
        strncat (drive, path, 2);
        drive[2] = '\0';
      }
      i = 2;
    }

    // path not necessarily terminated by \0
    // parse char by char
    char token[MAXPATH];
    int iToken = 0;

    for ( ; i < MAXPATH; i++) {
      // if delimiter, act accordingly
      // token is part of the directory
      if (path[i] == '/' || path[i] == '\\') {
        token[iToken++] = path[i];
        token[iToken++] = '\0';
        flags |= DIRECTORY;
        if (dir != NULL) 
          strcat (dir, token);
        iToken = 0;
        continue;
      }
      // token is name
      else if (path[i] == '.') {
        token[iToken] = '\0';
        if (flags & FILENAME) {
          flags |= EXTENSION;
          if (ext != NULL)
            strcat (ext, token);
        }
        else {
          flags |= FILENAME;
          if (name != NULL)
            strcpy (name, token);
        }
        token[0] = '.';
        iToken = 1;
        continue;
      }
      // token is name or extension
      else if (path[i] == '\0' 
               || i >= MAXPATH - 1 ) {
               //|| extCount >= MAXEXT - 1) {
        if (flags & FILENAME) {
          // is extension 
          token[iToken] = '\0';
          flags |= EXTENSION;
          if (ext != NULL)  
            strcat (ext, token);
          // all parts gathered, exit function
          break;
        } 
        else {
          // is name
          token[iToken] = '\0';
          flags |= FILENAME;
          if (name != NULL)
            strcpy (name, token);
          // all parts gathered, exit
          break;
        }
      }
      else {
        //if not delimiter, build string
        token[iToken++] = path[i]; 
      }
    }
  }

  return flags;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fnmerge
 *  Description:  Combines components into a path
 *         NOTE:  Does not handle wildcard * due to shell handling this in Linux
 *     Argument:  char *, Returns assembled path
 *     Argument:  const char *, Drive component
 *     Argument:  const char *, Directory component
 *     Argument:  const char *, File name component
 *     Argument:  const char *, Extension component
 * =====================================================================================
 */
void fnmerge (char *path,
                     const char *drive,
                     const char *dir,
                     const char *name,
                     const char *ext)
{
  if (path == NULL)
    return;

  path[0] = '\0';

  if (drive != NULL)
    strcat (path, drive);
  if (dir != NULL)
    strcat (path, dir);
  if (name != NULL)
    strcat (path, name);
  if (ext != NULL)
    strcat (path, ext);
}