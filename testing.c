#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "member.c"

#define MxN 255
#define ll long long int
#define ld long double

AVLMember member_list = NULL;

int main() {
  AVLMember_Insert(&member_list,newDataMember("test","test","test","123123123"));
  AVLMember_Insert(&member_list,newDataMember("test","test","test","101239123"));
  AVLMember_Insert(&member_list,newDataMember("test","test","test","123912030"));
  AVLMember_Insert(&member_list,newDataMember("test","test","test","812391230"));
  AVLMember_Insert(&member_list,newDataMember("test","test","test","120391230"));
  AVLMember_Insert(&member_list,newDataMember("test","test","test","123001239"));
  AVLMember_Display(member_list);
  return 0;
}