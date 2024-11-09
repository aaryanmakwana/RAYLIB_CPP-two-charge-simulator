#include <iostream>
#include <raylib.h>
#include "./lib/assets.hpp"

/*
TOP LEFT = 0,0
TOP RIGHT = MAX,0
BOTTOM LEFT = 0,MAX
BOTTOM RIGHT = MAX,MAX
*/

Color Charge_cols[3] = {Red_col, Yellow_col, Blue_col};

int H = GetScreenHeight();
int W = GetScreenWidth();

void DrawCharge(Charge);
Color charge_col(int);
int C_size(int);

int main() {

  InitWindow(W,H,"SIM_1");
  SetTargetFPS(FPS);
  velocity v1 = {15,20};
  velocity v2 = {-15,-20};

  Charge p1 = {-50,100,5,5, v1};
  Charge p2 = {100,150,-5,5, v2};
  phy_elem pnts= {p1,p2, true};
  int Frame = 0;
  int sim = 0;

  Charge netCharge;

  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(White_col);
    DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), grey_col);
    DrawLine(0, GetScreenHeight()/2, GetScreenWidth(), GetScreenHeight()/2, grey_col);

    if(IsKeyPressed(KEY_K)){
      sim ++;
    }

    if(sim%2){
      DrawCharge(pnts.a);
      DrawCharge(pnts.b);
      netCharge = mergeCharges(pnts.a, pnts.b);
      //DrawCharge(netCharge);
      pnts = Physics_update(pnts.a,pnts.b);
      if(!pnts.working){
        sim = false;
      }
      Frame ++;
    }

    DrawText(TextFormat("TIME: %d s\n\nA: ( %lf.1, %.1lf )\t( %.1lf, %.1lf) \n\nB: ( %.1lf, %.1lf )\t( %.1lf, %.1lf)", Frame/FPS,pnts.a.pos_x,pnts.a.pos_y,pnts.a.v.x,pnts.a.v.y,pnts.b.pos_x,pnts.b.pos_y,pnts.b.v.x,pnts.b.v.y),5,5,20,grey_col);

    if(!pnts.working){
        char str[] = "COMPLETED SIMULATION";
        DrawText(str,GetScreenWidth()/2 - 300,GetScreenHeight()/2 - 15,30,Red_col);
    }

    EndDrawing();

  }

  printf("%d %d", H, W);

  return 0;
}

void DrawCharge(Charge C) {
  DrawCircle(C.pos_y+GetScreenWidth()/2, C.pos_x+GetScreenHeight()/2, C_size(C.mass), charge_col(C.charge));
}

Color charge_col(int x){
  if (x<0){return Charge_cols[0];}
  return Charge_cols[2];
}

int C_size(int x){
  if (x<0){x=-x;}
  return x;
}
