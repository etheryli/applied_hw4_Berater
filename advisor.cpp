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
 * File: Advisor program implementation
 */

#include "advisor.h"

Advisor::Advisor() {
  // Read into private lists
  adviceList = readDatFile("advice.dat");
  weatherList = readDatFile("weather.dat");
  reminderList = readDatFile("reminder.dat");

  // Main Box Layout
  QVBoxLayout *vBoxLayout = new QVBoxLayout();

  textEdit = new QTextEdit();

  // Signal mapper uses int to map to buttons
  QSignalMapper *signalMapper = new QSignalMapper(this);
  connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(buttonClick(int)));

  // Assign to our array of pushbuttons
  pushButtons[0] = new QPushButton("Advise", this);
  pushButtons[1] = new QPushButton("Weather", this);
  pushButtons[2] = new QPushButton("Reminder", this);
  pushButtons[3] = new QPushButton("Quit", this);

  // Add the text to the top
  vBoxLayout->addWidget(textEdit);

  // Quickly loop through and add each button and map them to click events
  for (int i = 0; i < 4; ++i) {
    vBoxLayout->addWidget(pushButtons[i]);
    signalMapper->setMapping(pushButtons[i], i);
    connect(pushButtons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
  }

  // Default reminder checked
  reminderPrompt = new QCheckBox("Show this message again");
  reminderPrompt->setChecked(true);

  // Set the layout to show
  this->setWindowTitle("Advisor");
  this->setLayout(vBoxLayout);
  this->show();
}

void Advisor::buttonClick(int button) {
  QString message;

  // Switch based on which button is pressed
  // Random number is generated based on list's size
  switch (button) {
    // Advice
    case 0: {
      int randomNumber = rand() % adviceList.length();
      message = "Advice: " + adviceList[randomNumber];
      textEdit->append(message);
      break;
    }
    // Weather
    case 1: {
      int randomNumber = rand() % weatherList.length();
      message = "Weather: " + weatherList[randomNumber];
      textEdit->append(message);
      break;
    }
    // Reminder
    case 2: {
      // Make a modal message box with checkbox, button
      QMessageBox *reminderMessageBox = new QMessageBox(this);

      reminderPrompt->blockSignals(true);
      reminderMessageBox->setIcon(QMessageBox::Information);
      reminderMessageBox->addButton(reminderPrompt, QMessageBox::ActionRole);
      reminderMessageBox->addButton("OK", QMessageBox::RejectRole);
      reminderMessageBox->setModal(true);

      int randomNumber = rand() % reminderList.length();
      message = reminderList[randomNumber];

      // Handling for shown reminder
      // Using while loop to generate (arrive) at a random message
      // that hasn't been shown
      while (reminderListShown.contains(message) &&
             reminderListShown.length() != reminderList.length()) {
        randomNumber = rand() % reminderList.length();
        message = reminderList[randomNumber];
      }

      // Only display if the random message wasn't shown already
      if (reminderListShown.length() != reminderList.length()) {
        reminderMessageBox->setText(message);
        reminderMessageBox->exec();
        if (reminderPrompt->checkState() == Qt::Unchecked)
          reminderListShown << message;
      }
      break;
    }
    // Quit
    case 3: {
      // Make a quit message box with a yes or no
      QMessageBox *quitMessageBox = new QMessageBox(this);
      quitMessageBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      quitMessageBox->setText("Are you sure you want to quit?");

      // 16384 = 0x4000 = Yes Button clicked
      int quitButtonClicked = quitMessageBox->exec();
      if (quitButtonClicked == 16384) QApplication::quit();

      break;
    }
  }
}

QStringList Advisor::readDatFile(const QString datFileName) {
  QFileInfo checkDatFile(datFileName);
  // Check if file exists, then readin
  if (checkDatFile.exists() && checkDatFile.isFile()) {
    // Open file
    QFile datFile(datFileName);
    datFile.open(QIODevice::ReadOnly);

    QString line;
    QStringList dataList;

    // Read until end of file
    while (!datFile.atEnd()) {
      line = datFile.readLine().trimmed();

      // Add the next line to current line if backslash detected
      while (line.endsWith('\\')) {
        // Error for when the file ends with a backslash
        if (datFile.atEnd())
          throw std::runtime_error("Backslash at the end of file");

        // Else continue replace backslash and add to current line
        line.chop(1);
        line.append(datFile.readLine().trimmed());
      }
      // Add the line to private list
      dataList << line;
    }
    return dataList;
  }

  // Else error
  throw std::runtime_error("One or more of the dat file can't be opened");
}
