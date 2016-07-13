#ifndef __STRINGUTILS_H
#define __STRINGUTILS_H

String padLeft(String num, int len)
{
  static String p_char = "0";
  while(num.length() < len) num = p_char + num;
  return num; 
}

#endif // __STRINGUTILS_H
