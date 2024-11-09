#include <iostream>
#include <raylib.h>

#define FPS 120
#define TIME 1/FPS
#define Tsq TIME*TIME
#define K 9000000000.00

struct velocity{
  float x;
  float y;
};

struct Charge{
  float pos_y;
  float pos_x;
  int charge;
  float mass;
  velocity v;
};

struct Force{
  float x;
  float y;
  float mag;
};


struct phy_elem{
  Charge a;
  Charge b;
  bool working;
};

Color White_col = {255,255,255,255};
Color grey_col = {55,55,55,255};
Color Red_col = {255,0,0,255};
Color Blue_col = {0,0,255,255};
Color Green_col = {0,255,0,255};
Color Yellow_col = {255,255,0,255};

phy_elem Physics_update(Charge,Charge);
int close(float, float);
Force calc_Forces(Charge, Charge);
float dist(Charge, Charge);
float square(float);
Force reverse(Force);
Charge walk(Charge, Force);

phy_elem Physics_update(Charge a, Charge b){

  phy_elem Update = {a,b,true};

  if(!close(a.pos_x,b.pos_x) && !close(a.pos_y,b.pos_y)){
    Force F = calc_Forces(a, b);
    Update.a = walk(a, F);
    Update.b = walk(b, reverse(F));
  }else{
    Update.working = false;
  }
  return Update;
}

int close(float a, float b){
  if(a/b > 0.9999 && a/b < 1.0001){
    return 1;
  }
  return 0;
}

Force calc_Forces(Charge a, Charge b){
  Force F;
  float D = dist(a,b);
  F.mag = K*a.charge * b.charge/square(D);
  F.x = (b.pos_x-a.pos_x)/D;
  F.y = (b.pos_y-a.pos_y)/D;

  if (F.mag > 0){
    F.x *= -1;
    F.y *= -1;
  }

  return F;
}

float dist(Charge a, Charge b){
  return sqrt(square(b.pos_x-a.pos_x) + square(b.pos_y-a.pos_y))*0.001;
}

float square(float a){
  return a*a;
}

Force reverse(Force f){
  f.x *= -1;
  f.y *= -1;
  return f;
}

Charge mergeCharges(Charge a, Charge b){
  Charge c;
  c.pos_y = (a.pos_y + b.pos_y)/2;
  c.pos_x = (a.pos_x + b.pos_x)/2;
  c.charge = a.charge + b.charge;
  c.mass = a.mass + b.mass;
  return c;
}

Charge walk(Charge a, Force f){
  float old_pos_x = a.pos_x;
  float old_pos_y = a.pos_y;

  float acc_x = f.x/a.mass;
  float acc_y = f.y/a.mass;

  a.pos_x += a.v.x * TIME + Tsq*acc_x;
  a.pos_y += a.v.y * TIME + Tsq*acc_y;

  a.v.y += acc_y*TIME;
  a.v.x += acc_x*TIME;

  return a;
}
