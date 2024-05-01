#ifndef SRC_HEADERS_S21_SSCANF_H_
#define SRC_HEADERS_S21_SSCANF_H_

struct mode {
  int len;
  int skip;
  int h;
  int l;
  int ll;
};


typedef struct option {
  int format;
  long count;
  int end;
  int wid;
  int zvezd;
  int len;
  int err;
  char buff;
} option;

typedef struct mode mode;

#endif  // SRC_HEADERS_S21_SSCANF_H_