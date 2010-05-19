#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QSizePolicy>

#include "plotArea.h"
#include "../src/Network.h"
#include "../src/Simulator.h";
#include "../src/Percolation_Sim.h"
#include "../src/ChainBinomial_Sim.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

//Set default values that are not related to distribution

const QString default_num_runs="1";
const QString default_network_size="10000";
const QString default_P0="10";
const QString default_T ="0.1";
const QString default_infectious_pd ="5";

// Forward definitions of classes
class QMainWindow;
class QAction;
class QMainWindowButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QComboBox;
class QCheckBox;
class PlotArea;

//Define public and private functions and slots for 'MainWindow' class
class MainWindow : public QMainWindow
{
    Q_OBJECT

        public:
        MainWindow();
        void appendOutput(QString);
        void appendOutputLine(QString);

        Network* network;
        Simulator* simulator;
        QTextEdit* logEditor;

        enum DistType  { POI, EXP, POW, URB, CON};

    public slots:

        void simulatorWrapper();
        void changeParameterLabels(int dist_type);
        void changeNetSource(int source);
        void changeSimType(int type);
        void updateRZero();
        void defaultSettings();
        void readEdgeList();
        void clear_network();
        void clear_data();
        void generate_network();
        void connect_network (Network* net, DistType dist, double param1, double param2);
        void saveEdgeList();

    protected:
        void resizeEvent ( QResizeEvent *event );

    private:

        void createMenu();
        void createSettingsBox();
        void createNetworkSettingsBox();
        void createSimulatorSettingsBox();
        void createControlButtonsBox();
        //void createGridGroupBox();
        //void createFormGroupBox();
        void runSimulation(int j_max, int patient_zero_ct, string RunID);

        void makeReadonly(QLineEdit* lineEdit);
        void addStateData();

        QWidget* centralWidget;

        QLabel* distLabel;
        QLabel* param1Label;
        QLabel* param2Label;
        QLabel* netsourceLabel;
        QLabel* netfileLabel;
        QLabel* simLabel;
        QLabel* infectiousPeriodLabel;

        QGroupBox* mainBox;
        QGroupBox* leftBox;
        QSplitter* rightBox;

        QMenuBar* menuBar;
        QGroupBox* settingsGroupBox;
        QGroupBox* networkSettingsGroupBox;
        QGroupBox* simulatorSettingsGroupBox;
        QGroupBox* controlButtonsGroupBox;

        QComboBox* distBox;
        QComboBox* netsourceBox;
        QComboBox* simBox;

        QCheckBox* retainDataCheckBox;

        QPushButton* clearnetButton;
        QPushButton* loadnetButton;
        QPushButton* generatenetButton;

        QMainWindowButtonBox* buttonBox;

        double calculate_T_crit();
        double convertR0toT(double R0);
        double convertTtoR0(double T);
        double convertTtoTCB (double T, int d);
        double convertTCBtoT (double TCB, int d);


        // Define textboxes and other main menu items

        QLineEdit* numrunsLine;
        QLineEdit* numnodesLine;
        QLineEdit* param1Line;
        QLineEdit* param2Line;
        QLineEdit* pzeroLine;
        QLineEdit* transLine;
        QLineEdit* rzeroLine;
        QLineEdit* infectiousPeriodLine;
        QLineEdit* netfileLine;


        PlotArea* epiCurvePlot;
        PlotArea* statePlot;
        PlotArea* histPlot;

        QWidget* dockWidget1;
        QWidget* dockWidget2;

        QDoubleValidator* probValidator;
        QMenu* fileMenu;
        QMenu* plotMenu;
        QAction* exitAction;
        QAction* openAction;
};
#endif