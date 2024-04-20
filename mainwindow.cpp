#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GanntChart.h"
#include "metrics.h"
#include <vector>
#include <time.h>

using namespace std;



int all_terminated(vector<process> &processes)
{
    for(int i=0;i<processes.size();i++)
    {
        if(processes[i].process_state!=terminated)
        {
            return i;
        }
    }
    return -1;
}
int process_running(vector<process> &processes)
{
    for(int i=0;i<processes.size();i++)
    {
        if(processes[i].process_state==running)
        {
            return i;
        }
    }
    return -1;
}
int FCFS(vector<process> &processes,int time)
{
    if(all_terminated(processes)==-1)
    {
        return -1;
    }
    int x=processes.size();
    int first_process=all_terminated(processes);
    for(int i=first_process+1;i<x;i++)
    {
        if((processes[i].arrival_time<processes[first_process].arrival_time)&&(processes[i].process_state!=terminated))
        {
            first_process=i;
        }
        else if((processes[i].arrival_time==processes[first_process].arrival_time)&&(processes[i].process_state!=terminated))
        {
            if(processes[i].process_id<processes[first_process].process_id)
                first_process=i;
        }
    }
    if(processes[first_process].reamaing_time==processes[first_process].bursttime)
        processes[first_process].serve_time=time;
    processes[first_process].reamaing_time--;
    if(processes[first_process].reamaing_time==0)
    {
        processes[first_process].process_state=terminated;
        processes[first_process].finish_time=time+1;
    }
    return processes[first_process].process_id;
}

int SJF_Preemptive(vector<process> &processes,int time)
{
    if(all_terminated(processes)==-1)
    {
        return -1;
    }
    int x=processes.size();
    int first_process=all_terminated(processes);
    for(int i=first_process+1;i<x;i++)
    {
        if((processes[i].reamaing_time<processes[first_process].reamaing_time)&&(processes[i].process_state!=terminated))
        {
            first_process=i;
        }
        else if((processes[i].reamaing_time==processes[first_process].reamaing_time)&&(processes[i].process_state!=terminated))
        {
            if(processes[i].process_id<processes[first_process].process_id)
                first_process=i;
        }
    }
    if(processes[first_process].reamaing_time==processes[first_process].bursttime)
        processes[first_process].serve_time=time;
    processes[first_process].reamaing_time--;
    if(processes[first_process].reamaing_time==0)
    {
        processes[first_process].process_state=terminated;
        processes[first_process].finish_time=time+1;
    }
    return processes[first_process].process_id;
}

int SJF_Non_Preemptive(vector<process> &processes,int time)
{
    if(all_terminated(processes)==-1)
    {
        return -1;
    }
    if(process_running(processes)!=-1)
    {
        int first_process=process_running(processes);
        processes[first_process].reamaing_time--;
        if(processes[first_process].reamaing_time==0)
        {
            processes[first_process].process_state=terminated;
            processes[first_process].finish_time=time+1;
        }
        return processes[first_process].process_id;
    }
    else {
        int x = processes.size();
        int first_process = all_terminated(processes);
        for (int i = first_process + 1; i < x; i++) {
            if ((processes[i].reamaing_time < processes[first_process].reamaing_time) &&
                (processes[i].process_state != terminated)) {
                first_process = i;
            } else if ((processes[i].reamaing_time == processes[first_process].reamaing_time) &&
                       (processes[i].process_state != terminated)) {
                if (processes[i].process_id < processes[first_process].process_id)
                    first_process = i;
            }
        }
        if (processes[first_process].reamaing_time == processes[first_process].bursttime)
        {
            processes[first_process].process_state = running;
            processes[first_process].serve_time = time;
        }
        processes[first_process].reamaing_time--;
        if (processes[first_process].reamaing_time == 0) {
            processes[first_process].process_state = terminated;
            processes[first_process].finish_time = time + 1;
        }
        return processes[first_process].process_id;
    }
}
int Priority_Preemptive(vector<process> &processes,int time)
{
    if(all_terminated(processes)==-1)
    {
        return -1;
    }
    int x=processes.size();
    int first_process=all_terminated(processes);
    for(int i=first_process+1;i<x;i++)
    {
        if((processes[i].periority<processes[first_process].periority)&&(processes[i].process_state!=terminated))
        {
            first_process=i;
        }
        else if((processes[i].periority==processes[first_process].periority)&&(processes[i].process_state!=terminated))
        {
            if(processes[i].process_id<processes[first_process].process_id)
                first_process=i;
        }
    }
    if(processes[first_process].reamaing_time==processes[first_process].bursttime)
        processes[first_process].serve_time=time;
    processes[first_process].reamaing_time--;
    if(processes[first_process].reamaing_time==0)
    {
        processes[first_process].process_state=terminated;
        processes[first_process].finish_time=time+1;
    }
    return processes[first_process].process_id;
}

int Priority_Non_Preemptive(vector<process> &processes,int time)
{
    if(all_terminated(processes)==-1)
    {
        return -1;
    }
    if(process_running(processes)!=-1)
    {
        int first_process=process_running(processes);
        processes[first_process].reamaing_time--;
        if(processes[first_process].reamaing_time==0)
        {
            processes[first_process].process_state=terminated;
            processes[first_process].finish_time=time+1;
        }
        return processes[first_process].process_id;
    }
    else {
        int x = processes.size();
        int first_process = all_terminated(processes);
        for (int i = first_process + 1; i < x; i++) {
            if ((processes[i].periority < processes[first_process].periority) &&
                (processes[i].process_state != terminated)) {
                first_process = i;
            } else if ((processes[i].periority == processes[first_process].periority) &&
                       (processes[i].process_state != terminated)) {
                if (processes[i].process_id < processes[first_process].process_id)
                    first_process = i;
            }
        }
        if (processes[first_process].reamaing_time == processes[first_process].bursttime)
        {
            processes[first_process].process_state = running;
            processes[first_process].serve_time = time;
        }
        processes[first_process].reamaing_time--;
        if (processes[first_process].reamaing_time == 0) {
            processes[first_process].process_state = terminated;
            processes[first_process].finish_time = time + 1;
        }
        return processes[first_process].process_id;
    }
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->QuantumLabel->setEnabled(false);
    ui->QuantumLabel->hide();
    ui->QuantumSpinBox->setEnabled(false);
    ui->QuantumSpinBox->hide();
    ui->PreemptiveCheckBox->setEnabled(false);
     ui->PreemptiveCheckBox->setEnabled(false);
    ui->PreemptiveCheckBox->hide();
    ui->PriorityLabel->setEnabled(false);
    ui->PriorityLabel->hide();
    ui->PrioritySpinBox->setEnabled(false);
    ui->PrioritySpinBox->hide();
    ui->ProcessesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Chart = new ChartArea(this);
    Chart->setGeometry(40, 330, 700, 120);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Chart;
}


void MainWindow::on_SchedulerComboBox_currentIndexChanged(int index)
{
    switch(index) {
    case 0: //First Come First Serve
        ui->QuantumLabel->setEnabled(false);
        ui->QuantumLabel->hide();
        ui->QuantumSpinBox->setEnabled(false);
        ui->QuantumSpinBox->hide();
        ui->PreemptiveCheckBox->setEnabled(false);
        ui->PreemptiveCheckBox->hide();
        ui->PriorityLabel->setEnabled(false);
        ui->PriorityLabel->hide();
        ui->PrioritySpinBox->setEnabled(false);
        ui->PrioritySpinBox->hide();
        break;
    case 1: //Shortest Job First
        ui->QuantumLabel->setEnabled(false);
        ui->QuantumLabel->hide();
        ui->QuantumSpinBox->setEnabled(false);
        ui->QuantumSpinBox->hide();
        ui->PreemptiveCheckBox->setEnabled(true);
        ui->PreemptiveCheckBox->show();
        ui->PriorityLabel->setEnabled(false);
        ui->PriorityLabel->hide();
        ui->PrioritySpinBox->setEnabled(false);
        ui->PrioritySpinBox->hide();
        break;
    case 2: //Priority
        ui->QuantumLabel->setEnabled(false);
        ui->QuantumLabel->hide();
        ui->QuantumSpinBox->setEnabled(false);
        ui->QuantumSpinBox->hide();
        ui->PreemptiveCheckBox->setEnabled(true);
        ui->PreemptiveCheckBox->show();
        ui->PriorityLabel->setEnabled(true);
        ui->PriorityLabel->show();
        ui->PrioritySpinBox->setEnabled(true);
        ui->PrioritySpinBox->show();
        break;
    case 3: //Round Robin
        ui->QuantumLabel->setEnabled(true);
        ui->QuantumLabel->show();
        ui->QuantumSpinBox->setEnabled(true);
        ui->QuantumSpinBox->show();
        ui->PreemptiveCheckBox->setEnabled(false);
        ui->PreemptiveCheckBox->hide();
        ui->PriorityLabel->setEnabled(false);
        ui->PriorityLabel->hide();
        ui->PrioritySpinBox->setEnabled(false);
        ui->PrioritySpinBox->hide();
        break;
    }
}


void MainWindow::on_InesrtButton_clicked()
{
    ui->ProcessesTable->setRowCount(ui->ProcessesTable->rowCount()+1);
    ui->ProcessesTable->setItem(currentProcessID-1, 0, new QTableWidgetItem(QString::number(currentProcessID)));
    ui->ProcessesTable->setItem(currentProcessID-1, 1, new QTableWidgetItem(ui->BurstLengthSpinBox->text()));
    ui->ProcessesTable->setItem(currentProcessID-1, 2, new QTableWidgetItem(ui->ArrivalTimeSpinBox->text()));
    ui->ProcessesTable->setItem(currentProcessID-1, 3, new QTableWidgetItem(ui->PrioritySpinBox->text()));
    if (ui->SchedulerComboBox->currentIndex() == 2) ui->ProcessesTable->setItem(currentProcessID-1, 3, new QTableWidgetItem(ui->PrioritySpinBox->text()));
    processes.push_back({currentProcessID,ready, static_cast<unsigned int>(ui->BurstLengthSpinBox->value()), static_cast<unsigned int>(ui->BurstLengthSpinBox->value()),
                         static_cast<unsigned int>(ui->ArrivalTimeSpinBox->value()),

                         static_cast<unsigned int>(ui->PrioritySpinBox->value()),0,0});

    currentProcessID++;
}


void MainWindow::on_SubmitButton_clicked()
{


        // Clear the timeline data in the ChartArea object
        Chart->timeline.clear();
        GanntChart chart;
        GanntChartSection x ;
        if( ui->radioButton->isChecked())

        {


        int i=0 ;
        int flag =0;
        time_t seconds;
            time_t seconds2;
            time(&seconds);
            time(&seconds2);
          while(1)
            {
               while(seconds2<=seconds)
                {
                   time(&seconds2);
                }
                seconds=seconds2;
                 Chart->timeline.clear();
                switch(ui->SchedulerComboBox->currentIndex()) {
                case 0:
                  //  chart = FCFS(processes);
                   x={FCFS(processes,i),i,i+1};
                  if(x.process==-1){
                        flag=1;
                      break;
                  }
                  chart.push_back(x);
                    Chart->timeline = chart;


                    Chart->repaint();

                    break;
                case 1:
                     x={SJF_Non_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);
                    Chart->timeline = chart;


                    Chart->repaint();



                    //chart = SJF(processes, ui->PreemptiveCheckBox->isChecked());

                    break;
                case 2:
                   // chart = Priority(processes, ui->PreemptiveCheckBox->isChecked());

                    x={Priority_Non_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);
                    Chart->timeline = chart;


                    Chart->repaint();


                    break;
               // case 3:
                    //chart = RoundRobin(processes, ui->QuantumSpinBox->value());

                    //x={RoundRobin(processes,i),i,i+1};
                    //if(x.process==-1){
                      //  flag=1;
                     //   break;
                   // }
                   // chart.push_back(x);
                   // Chart->timeline = chart;


                   // Chart->repaint();
                 //   break;
                case 4:
                    //chart = altPriority(processes, ui->PreemptiveCheckBox->isChecked());

                    x={Priority_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);
                    Chart->timeline = chart;


                    Chart->repaint();

                   break;
                case 5:
                    //chart = altSJF(processes, ui->PreemptiveCheckBox->isChecked());
                    x={SJF_Non_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);
                    Chart->timeline = chart;


                    Chart->repaint();


                   break;
                }
                if(flag==1)
                    break ;
                i++;

           }
        }
        else
            {

            int i=0 ;
            int flag =0;
        Chart->timeline.clear();
            while(1)
            {


                switch(ui->SchedulerComboBox->currentIndex()) {
                case 0:
                    //  chart = FCFS(processes);
                    x={FCFS(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);


                    break;
                case 1:
                    x={SJF_Non_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);




                    //chart = SJF(processes, ui->PreemptiveCheckBox->isChecked());

                    break;
                case 2:
                    // chart = Priority(processes, ui->PreemptiveCheckBox->isChecked());

                    x={Priority_Non_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);



                    break;
                    // case 3:
                    //chart = RoundRobin(processes, ui->QuantumSpinBox->value());

                    //x={RoundRobin(processes,i),i,i+1};
                    //if(x.process==-1){
                    //  flag=1;
                    //   break;
                    // }
                    // chart.push_back(x);

                    //   break;
                case 4:
                    //chart = altPriority(processes, ui->PreemptiveCheckBox->isChecked());

                    x={Priority_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);


                    break;
                case 5:
                    //chart = altSJF(processes, ui->PreemptiveCheckBox->isChecked());
                    x={SJF_Non_Preemptive(processes,i),i,i+1};
                    if(x.process==-1){
                        flag=1;
                        break;
                    }
                    chart.push_back(x);



                    break;
                }
                if(flag==1)
                    break ;
                i++;

            }
            Chart->timeline = chart;


            Chart->repaint();

            }

        // Generate the new Gantt chart based on the selected scheduling algorithm


        // Update the timeline data in the ChartArea object


        // Repaint the ChartArea to update the Gantt chart


        // Calculate metrics and update UI
        metrics calculated = calculateMetrics(chart, processes);
        ui->AverageResponseTimeOutputLabel->setText(QString::number(calculated.averageResponseTime, 'f', 4));
        ui->MaximumResponseTimeOutputLabel->setText(QString::number(calculated.maximumResponseTime, 'f', 4));
        ui->AverageTurnArounTimeOutputLabel->setText(QString::number(calculated.averageTurnAroundTime, 'f', 4));
        ui->MaximumTurnArounTimeOutputLabel->setText(QString::number(calculated.maximumTurnAroundTime, 'f', 4));
        ui->AverageWaitingTimeOutputLabel->setText(QString::number(calculated.averageWaitingTime, 'f', 4));
        ui->MaximumWaitingTimeOutputLabel->setText(QString::number(calculated.maximumWaitingTime, 'f', 4));
    }




void MainWindow::on_RemoveButton_clicked()
{
    if (currentProcessID > 1){
        ui->ProcessesTable->setRowCount(ui->ProcessesTable->rowCount()-1);
        processes.pop_back();
        currentProcessID--;
    }
}
