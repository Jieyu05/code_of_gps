//
// Created by jieyu on 2021/11/22.
//
#include "judge.h"

#define N 10000
#define EPSILON 0.000001
double Num1[N], Num2[N], Num3[N], Num4[N], Num5[N], Num6[N];
int Len1, Len2, Len3;

double Judge::min(double x, double y) {
    if (x > y) return y;
    else return x;
}

double Judge::max(double x, double y) {
    if (x < y) return y;
    else return x;
}

//判断点在线段上：：线段和是否相等
bool Judge::IsPointOnLine(double px0, double py0, double px1, double py1, double px2, double py2) {
    bool flag = false;
    if (px0 >= min(px1, px2) && px0 <= max(px1, px2) && py0 >= min(py1, py2) && py0 <= max(py1, py2)) {
        double s1 = (px1 - px0) * (px1 - px0) + (py1 - py0) * (py1 - py0);
        double s2 = (px2 - px0) * (px2 - px0) + (py2 - py0) * (py2 - py0);
        double s3 = (px2 - px1) * (px2 - px1) + (py2 - py1) * (py2 - py1);
        if ((s1 + s2) == s3) {
            flag = true;
        }
    }
    return flag;
}

//判断两线段相交
bool
Judge::IsIntersect(double px1, double py1, double px2, double py2, double px3, double py3, double px4, double py4) {
    bool flag = false;
    if (min(px1, px2) <= max(px3, px4) && min(px3, px4) <= max(px1, px2) && min(py1, py2) <= max(py3, py4)
        && min(py3, py4) <= max(py1, py2)) {
        double U, V, W, Z;
        U = (px3 - px1) * (py2 - py1) - (px2 - px1) * (py3 - py1);
        V = (px4 - px1) * (py2 - py1) - (px2 - px1) * (py4 - py1);
        W = (px1 - px3) * (py4 - py3) - (px4 - px3) * (py1 - py3);
        Z = (px2 - px3) * (py4 - py3) - (px4 - px3) * (py2 - py3);
        if (U * V <= EPSILON && W * Z <= EPSILON) {
            flag = true;
        }
    }
    return flag;
}

//判断点在多边形内
bool Judge::PointInPolygon2D(double x, double y, const std::vector<Vec2d> &POL) {
    bool isInside = false;
    int count = 0;

    //
    double minX = DBL_MAX;
    for (int i = 0; i < POL.size(); i++) {
        minX = std::min(minX, POL[i].x);
    }
    //
    double px = x;
    double py = y;
    double linePoint1x = x;
    double linePoint1y = y;
    double linePoint2x = 70.17;            //取最小的X值还小的值作为射线的终点
    double linePoint2y = y;

    //遍历每一条边
    for (int i = 0; i < POL.size() - 1; i++) {
        double cx1 = POL[i].x;
        double cy1 = POL[i].y;
        double cx2 = POL[i + 1].x;
        double cy2 = POL[i + 1].y;

        if (IsPointOnLine(px, py, cx1, cy1, cx2, cy2)) {
            return true;
        }
        if (Isinlimit(cx1, cy1, px, py)) {
            return true;
        }
        if (fabs(cy2 - cy1) < EPSILON)   //平行则不相交
        {
            continue;
        }

        if (IsPointOnLine(cx1, cy1, linePoint1x, linePoint1y, linePoint2x, linePoint2y)) {
            if (cy1 > cy2)            //只保证上端点+1
            {
                count++;
            }
        } else if (IsPointOnLine(cx2, cy2, linePoint1x, linePoint1y, linePoint2x, linePoint2y)) {
            if (cy2 > cy1)            //只保证上端点+1
            {
                count++;
            }
        } else if (IsIntersect(cx1, cy1, cx2, cy2, linePoint1x, linePoint1y, linePoint2x, linePoint2y))   //已经排除平行的情况
        {
            count++;
        }
    }

    if (count % 2 == 1) {
        isInside = true;
    } else {
    }
    return isInside;
}

//点与顶点距离不超过某一个范围
bool Judge::Isinlimit(double x1, double y1, double x2, double y2) {
    bool flag = false;
    double r;
    r = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    if (r <= 0.03) {
        flag = true;
    } else if (r <= 0.16 && x1 >= 114.545 && x1 <= 134.741) {
        flag = true;
    } else if (x2 >= 134.834 && x2 <= 135.1016 && y2 >= 48.321 && y2 <=
                                                                  48.4688 && r <= 0.6) {
        flag = true;
    }
    return flag;
}

//调用判断算法
bool Judge::judgementoflocation(double x, double y) {
    bool flag = false;
    std::cout << "jieyu\n";
    double m = x;
    double n = y;
    std::cout << "经度：" << std::fixed << m << std::endl;
    std::cout << "纬度：" << std::fixed << n << std::endl;
    std::cout << "车辆坐标(" << m << "," << n << ")\n";
    std::vector<Vec2d> POL;
    std::vector<Vec2d> POL2;
    std::vector<Vec2d> POL3;
    if (Len1 == 0 || Len2 == 0 || Len3 == 0) {
        Readtxt();
    }
    //构建大陆地区
    POL.push_back(Vec2d(Num1[0], Num2[0]));
    for (int i = 1; i < Len1; i++) {
        POL.push_back(Vec2d(Num1[i], Num2[i]));
    }
    POL.push_back(Vec2d(Num1[0], Num2[0]));
    //构建台湾地区
    POL2.push_back(Vec2d(Num3[0], Num4[0]));
    for (int i = 1; i < Len2; i++) {
        POL2.push_back(Vec2d(Num3[i], Num4[i]));
    }
    POL2.push_back(Vec2d(Num3[0], Num4[0]));
    //构建海南地球
    POL3.push_back(Vec2d(Num5[0], Num6[0]));
    for (int i = 1; i < Len3; i++) {
        POL3.push_back(Vec2d(Num5[i], Num6[i]));
    }
    POL3.push_back(Vec2d(Num5[0], Num6[0]));
    if (PointInPolygon2D(m, n, POL) || PointInPolygon2D(m, n, POL2) ||
        PointInPolygon2D(m, n, POL3)) {
        flag=true;
    }
    return flag;
}

int Judge::Readtxt() {


    std::ifstream input1("/update/GPSTXT/mainlandlong.txt");
    std::ifstream input2("/update/GPSTXT/mainlandlat.txt");

    //台湾
    std::ifstream input3("/update/GPSTXT/twlong.txt");
    std::ifstream input4("/update/GPSTXT/twlat.txt");

    //海南岛
    std::ifstream input5("/update/GPSTXT/hnlong.txt");
    std::ifstream input6("/update/GPSTXT/hnlat.txt");

    for (int i = 0; i < N; i++) {
        if (!input1.eof()) {
            input1 >> Num1[i];
            input2 >> Num2[i];
            Len1++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (!input3.eof()) {
            input3 >> Num3[i];
            input4 >> Num4[i];
            Len2++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (!input5.eof()) {
            input5 >> Num5[i];
            input6 >> Num6[i];
            Len3++;
        }
    }
    input1.close();
    input2.close();
    input3.close();
    input4.close();
    input5.close();
    input6.close();
    return 0;
}

