//
// Created by jieyu on 2021/9/18.
//

#ifndef TEST_JUDGE_H
#define TEST_JUDGE_H
//
// Created by jieyu on 2021/9/18.
//

#ifndef TBOX_JUDGE_H
#define TBOX_JUDGE_H

//#include "appconfig.h"
#include<iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cfloat>
#include <limits>
#include <fstream>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

class Judge {
public:
    struct Vec2d {
        double x, y;

        Vec2d() {
            x = 0.0;
            y = 0.0;
        }

        Vec2d(double dx, double dy) {
            x = dx;
            y = dy;
        }

        void Set(double dx, double dy) {
            x = dx;
            y = dy;
        }
    };

    static double min(double, double);

    static double max(double, double);

    //点在线上
    static bool IsPointOnLine(double, double, double, double, double, double);

    //点在区域内
    static bool IsIntersect(double, double, double, double, double, double, double, double);

    //点在多边形内的判断
    static bool PointInPolygon2D(double, double, const std::vector<Vec2d> &POL);

    //读取坐标信息
    static int Readtxt();
    //点与顶点距离不超过某一个范围

    static bool Isinlimit(double, double, double, double);

    //调用判断算法
    static bool judgementoflocation(double, double);


protected:
    double x;
    double y;
};

#endif //TBOX_JUDGE_H

#endif //TEST_JUDGE_H
