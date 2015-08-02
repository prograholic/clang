// missing pack attribute
struct X {
  char a1;
  int a2;
};

// different pack value
#pragma pack(push, 2)
struct X2 {
  char a1;
  int a2;
};
#pragma pack(pop)


// everything is OK
#pragma pack(push, 1)
struct X3 {
  char a1;
  int a2;
};
#pragma pack(pop)