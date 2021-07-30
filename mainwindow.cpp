#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Clippy)
{

    ui->setupUi(this);

    setCentralWidget(ui->listView);
    auto toolbar = ui->toolBar;
    removeToolBar(toolbar);
    addToolBar(Qt::RightToolBarArea, toolbar);
    toolbar->show();

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionnew_triggered()
{
  check_saved();
  m_list.clear();
  m_path.clear();
  m_changed=false;
  m_model.setStringList(m_list);

}


void MainWindow::on_actioncut_triggered()
{

    QClipboard *clipboard=QApplication::clipboard();
    int index = ui->listView->currentIndex().row();

    clipboard->setText(m_list.at(index));
    m_list.removeAt(index);
    m_model.setStringList(m_list);
    m_changed=true;

    ui->statusbar->showMessage("Copied",2000);
}


void MainWindow::on_actionopen_triggered()
{

    check_saved();
    QString tmp;

    tmp=QFileDialog::getOpenFileName(this, "Open File");
    if(tmp.isEmpty())
   {
     return;
   }
   m_path=tmp;
   m_list.clear();

   QFile file(m_path);

    if(!file.open(QIODevice::ReadOnly))

    {

        QMessageBox::critical(this, "Error",file.errorString());
    return;

    }

    //QDataStream stream(&file);
    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        m_list.append(stream.readLine());

    }

file.close();
m_changed=false;
m_model.setStringList(m_list);
ui->statusbar->showMessage("Opened",2000);

}


void MainWindow::on_actioncopy_page_triggered()

{

 QClipboard *clipboard=QApplication::clipboard();
    int index = ui->listView->currentIndex().row();

    clipboard->setText(m_list.at(index));

    ui->statusbar->showMessage("Copied",2000);
}

void MainWindow::on_actionpage_paste_triggered()
{
    timeout();
}

void MainWindow::on_actionsave_triggered()

{
    QFile file(m_path);
        if(m_path.isEmpty())
        {
            on_actionsave_As_triggered();
            return;
        }

        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,"Error",file.errorString());
            return;
        }

//here
        QTextStream stream(&file);
        foreach(QString line, m_list)
        {
            stream << line << "\r\n";
        }
        file.close();
        m_changed = false;
        ui->statusbar->showMessage("Saved",2000);
}


void MainWindow::on_actionsave_As_triggered()

{
    QString tmp = QFileDialog::getSaveFileName(this,"Save File");
       if(tmp.isEmpty()) return;

       m_path = tmp;
       on_actionsave_triggered();
}


void MainWindow::timeout()

{
    QClipboard *clipboard=QGuiApplication::clipboard();
    QString data = clipboard->text();

    if(data.compare(this->m_last))
    {
        m_last=data;
        qDebug()<< "done" <<m_last;

        if(!m_list.contains(m_last))
        {
            m_list.append(m_last);
            m_model.setStringList(m_list);
            ui->statusbar->showMessage("Added from the CLipboard",2000);
        }
    }

}

void MainWindow::on_actionstart_triggered()

{
    m_timer.start();
    ui->statusbar->showMessage("Listening to the clipboard", 2000);
}

void MainWindow::on_actionstop_triggered()
{
    m_timer.stop();
    ui->statusbar->showMessage("Manual mode", 2000);
}

void MainWindow::on_actiondelete_triggered()

{
    int index = ui->listView->currentIndex().row();
       m_list.removeAt(index);
       m_model.setStringList(m_list);
       m_changed = true;
       ui->statusbar->showMessage("Deleted", 2000);
}

void MainWindow::init()

{
    m_changed=false;
    m_path="";
    m_model.setStringList(m_list);
  ui->listView->setModel(&m_model);
  connect(& m_timer, &QTimer::timeout,this, &MainWindow::timeout);
  m_timer.setInterval(500);
  m_timer.start();

}

void MainWindow::check_saved()
{
    if(!m_changed) return;
        QMessageBox::StandardButton btn = QMessageBox::question(this,"Save Changes?","Would like to save your changes?");
        if(btn == QMessageBox::StandardButton::Yes) on_actionsave_triggered();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    check_saved();
    event->accept();

}


