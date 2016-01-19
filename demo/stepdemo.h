#pragma once



namespace stepdemo
{
  using namespace std;

  void test()
  {

    int num = 1000;
    float startx = -1.99f;
    float dx = 3.f / (float)num;


    float x1 = startx, x2;
    for (int i = 1; i <= num; i++) {
      x1 += dx;
      x2 = i*dx + startx;
      cout << "x1 = " << x1 << endl;
      cout << "x2 = " << x2 << endl;

    }
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
  }

}

