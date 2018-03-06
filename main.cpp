/*
 * Created by Hung Nguyen
 * Student ID: 905925175
 * Email: dnhung7@vt.edu
 * Class: ECE 3574
 * Assignment: Homework 4
 *
 * As a Hokie, I will conduct myself with honor and integrity at all times.
 * I will not lie, cheat, or steal, nor will I accept the actions of those
 * who do.”
 *
 * File: main that runs the program
 */

#include <QApplication>
#include <QTextStream>
#include "advisor.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Advisor advisor;
  advisor.show();
  return app.exec();
}
