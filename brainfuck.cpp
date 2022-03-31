#include <iostream>
#include <cstdio>

const int limit = 1e7;
char mem[limit+7], c;
int m=0, loopOpen=0, loopClose=0;

int main(int argc, char const *argv[]) {
  // Fucking your brain
  if(argc != 2) {
    fprintf(stderr, "The Fucking Usage: ./brainfuck *file* LEARN TO READ THE MARKDOWN!\n");
    exit(1);
  }

  // init
  FILE* src = fopen(argv[1], "r");
  if(!src){
    fprintf(stderr, "Fuck off\n");
    exit(1);
  }
  fseek(src, 0, SEEK_END);
  int len = ftell(src);
  char* code = (char*)malloc(len);
  rewind(src);
  for(int i=0; i<len; i++) {
    code[i] = fgetc(src);
  }

  // compile (interpret) (idk what to call this step)
  for(int i=0; i<len; i++) {
    c = code[i];

    if(c == '>' && (++m)==limit) {
      m=0;
    } else if(c == '<' && !(m--)) {
      m=limit-1;
    } else if(c == '+') {
      mem[m]++;
    } else if(c == '-') {
      mem[m]--;
    } else if(c == '.') {
      std::cout << mem[m];
    } else if(c == ',') {
      char in;
      std::cin >> in;
      mem[m] = in;
    } else if(c == '[' && !mem[m]) {
      loopOpen++;
      while(loopOpen) {
        if(++i == limit) {
          free(code);
          fclose(src);
          exit(0);
        }
        if(code[i] == '[') {
          loopOpen++;
        } else if(code[i] == ']') {
          loopOpen--;
        }
      }
    } else if(c == '[' && !mem[m]) {
      loopClose++;
      while(loopClose) {
        if(--i == -1) {
          free(code);
          fclose(src);
          exit(0);
        }
        if(code[i] == '[') {
          loopClose--;
        } else if(code[i] == ']') {
          loopClose++;
        }
      }
    }
  }

  free(code);
  fclose(src);
  return 0;
}
