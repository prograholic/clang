// extra pack attribute
#pragma pack(push, 1)
struct X {
  char a1;
  int a2;
};
#pragma pack(pop)

// different pack value
#pragma pack(push, 1)
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
