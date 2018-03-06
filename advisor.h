#ifndef ADVISOR_H
#define ADVISOR_H

#include <QApplication>
#include <QCheckBox>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
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
 * File: Advisor program header
 */

#include <QSignalMapper>
#include <QString>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QtGui>
#include <exception>
#include <stdexcept>

class Advisor : public QWidget {
  Q_OBJECT
 public:
  // Default constructor initalizes everything for the UI
  Advisor();

 public slots:
  void buttonClick(int button);

 private:
  // Contain data from dat files
  QStringList adviceList;
  QStringList weatherList;
  QStringList reminderList;

  // Used for when the reminder is already shown
  QStringList reminderListShown;

  // UI components
  QTextEdit *textEdit;
  QPushButton *pushButtons[4];
  QCheckBox *reminderPrompt;

  // Read in dat files into private data lists
  QStringList readDatFile(const QString datfileName);
};

#endif  // ADVISOR_H
